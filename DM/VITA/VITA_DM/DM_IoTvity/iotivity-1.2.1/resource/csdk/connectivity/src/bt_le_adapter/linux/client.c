/******************************************************************
 *
 * Copyright 2015 Intel Corporation All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

#include "client.h"
#include "recv.h"
#include "context.h"
#include "bluez.h"
#include "utils.h"

#include "cagattservice.h"
#include "logger.h"
#include "oic_malloc.h"
#include "oic_string.h"

#include <gio/gio.h>

#include <strings.h>
#include <assert.h>


// Logging tag.
static char const TAG[] = "BLE_CLIENT";

typedef struct _CAGattClientContext
{
    /**
     * Bluetooth MAC address to GATT characteristic map.
     *
     * Hash table that maps Bluetooth MAC address to a OIC Transport
     * Profile GATT characteristic.  The key is a string containing
     * the LE peripheral Bluetooth adapter MAC address.   The value is
     * an interface proxy (@c GDBusProxy) to an
     * @c org.bluez.GattCharacteristic1 object, i.e. OIC Transport
     * Profile GATT request characteristic.
     */
    GHashTable * characteristic_map;

    /**
     * Response characteristic object path to Bluetooth MAC address map.
     *
     * Hash table that maps OIC Transport Profile GATT response
     * characteristic D-Bus object path to Bluetooth MAC address.  The
     * key is the D-Bus object path.  The value is the LE peripheral
     * Bluetooth adapter MAC address.
     *
     * @note This map exists to avoid having to create a hierarchy of
     *       GLib D-Bus proxies to the client side BlueZ GATT response
     *       Characteristic, its corresponding GATT Service, and the
     *       Device object within that Service, along with the
     *       resulting D-Bus calls, simply so that we obtain the MAC
     *       address of the remote (peripheral) LE device.  We
     *       unfortunately need the MAC address since the
     *       shared/common caleadapter code requires it.
     */
    GHashTable * address_map;

    /// Mutex used to synchronize access to context fields.
    ca_mutex lock;

} CAGattClientContext;

static CAGattClientContext g_context = {
    .lock = NULL
};

// ---------------------------------------------------------------------
//                      GATT Response Receive
// ---------------------------------------------------------------------
static void CAGattClientOnCharacteristicPropertiesChanged(
    GDBusProxy * characteristic,
    GVariant * changed_properties,
    GStrv invalidated_properties,
    gpointer user_data)
{
    /*
      This handler is trigged in a GATT client when receiving data
      sent by a GATT server through a notification, e.g. such as when
      a GATT server sent a response.
    */

    (void) invalidated_properties;

    if (g_variant_n_children(changed_properties) < 1)
    {
        /*
          No changed properties, only invalidated ones which we don't
          care about.
        */
        return;
    }

    CALEContext * const context = user_data;
    char const * const object_path =
        g_dbus_proxy_get_object_path(characteristic);

    ca_mutex_lock(g_context.lock);

    char * const address =
        g_hash_table_lookup(g_context.address_map, object_path);

    /*
      Address lookup could fail if a property changed on a GATT
      characteristic that isn't an OIC Transport Profile GATT response
      characteristic.  This isn't necessarily a problem since it's
      possible other unrelated GATT charactertistics with changed
      properties are exposed by BlueZ on the D-Bus system bus.
    */
    if (address != NULL)
    {
        CAGattRecvInfo info =
            {
                .peer               = address,
                .on_packet_received = context->on_client_received_data,
                .context            = context
            };

        GVariant * const value =
            g_variant_lookup_value(changed_properties, "Value", NULL);

        if (value != NULL)
        {
            // GLib maps an octet to a guchar, which is of size 1.
            gsize length = 0;
            gconstpointer const data =
                g_variant_get_fixed_array(value, &length, 1);

            (void) CAGattRecv(&info, data, length);

            g_variant_unref(value);
        }
    }

    ca_mutex_unlock(g_context.lock);
}

// ---------------------------------------------------------------------
//                        GATT Client Set-up
// ---------------------------------------------------------------------
static bool CAGattClientMapInsert(GHashTable * map,
                                  gpointer key,
                                  gpointer value)
{
    bool const insert = !g_hash_table_contains(map, key);

    if (insert)
    {
        g_hash_table_insert(map, key, value);
    }

    return insert;
}

static bool CAGattClientSetupCharacteristics(
    GDBusProxy * service,
    char const * address,
    GHashTable * characteristic_map,
    GHashTable * address_map,
    CALEContext * context)
{
    bool success = true;

    GVariant * const characteristics_prop =
        g_dbus_proxy_get_cached_property(service, "Characteristics");

    gsize length = 0;
    gchar const ** const characteristic_paths =
        g_variant_get_objv(characteristics_prop, &length);

#ifdef TB_LOG
    if (length == 0)
    {
        OIC_LOG(ERROR,
                TAG,
                "Server side OIC GATT Service has no characteristics");
    }
#endif

    /*
      Create a proxies to the org.bluez.GattCharacteristic1 D-Bus
      objects that will later be used to send requests and receive
      responses on the client side.
    */
    gchar const * const * const end = characteristic_paths + length;
    for (gchar const * const * path = characteristic_paths;
         path != end && success;
         ++path)
    {
        // Find the request characteristic.
        GError * error = NULL;

        GDBusProxy * const characteristic =
            g_dbus_proxy_new_sync(context->connection,
                                  G_DBUS_PROXY_FLAGS_NONE,
                                  NULL, // GDBusInterfaceInfo
                                  BLUEZ_NAME,
                                  *path,
                                  BLUEZ_GATT_CHARACTERISTIC_INTERFACE,
                                  NULL, // GCancellable
                                  &error);

        if (characteristic == NULL)
        {
            OIC_LOG_V(ERROR,
                      TAG,
                      "Unable to obtain proxy to GATT characteristic: %s",
                      error->message);

            g_error_free(error);

            success = false;

            break;
        }

        GVariant * const uuid_prop =
            g_dbus_proxy_get_cached_property(characteristic, "UUID");

        char const * const uuid =
            g_variant_get_string(uuid_prop, NULL);

        if (strcasecmp(uuid, CA_GATT_REQUEST_CHRC_UUID) == 0)
        {
            char     * const addr = OICStrdup(address);
            gpointer * const chrc = g_object_ref(characteristic);

            // Map LE (MAC) address to request characteristic.
            if (!CAGattClientMapInsert(characteristic_map, addr, chrc))
            {
                OIC_LOG_V(WARNING,
                          TAG,
                          "Possible duplicate OIC GATT "
                          "request characteristic proxy detected.");

                g_object_unref(chrc);
                OICFree(addr);
            }
        }
        else if (strcasecmp(uuid, CA_GATT_RESPONSE_CHRC_UUID) == 0)
        {
            char * const p    = OICStrdup(*path);
            char * const addr = OICStrdup(address);

            // Map GATT service D-Bus object path to client address.
            if (!CAGattClientMapInsert(address_map, p, addr))
            {
                OIC_LOG_V(WARNING,
                          TAG,
                          "Unable to register duplicate "
                          "peripheral MAC address");

                success = false;

                OICFree(addr);
                OICFree(p);
            }
            else
            {
                /*
                  Detect changes in GATT characteristic properties.
                  This is only relevant to OIC response
                  characteristics since only their "Value" property
                  will ever change.
                */
                g_signal_connect(
                    characteristic,
                    "g-properties-changed",
                    G_CALLBACK(CAGattClientOnCharacteristicPropertiesChanged),
                    context);

                // Enable notifications.
                GVariant * const ret =
                    g_dbus_proxy_call_sync(
                        characteristic,
                        "StartNotify",
                        NULL,  // parameters
                        G_DBUS_CALL_FLAGS_NONE,
                        -1,    // timeout (default == -1),
                        NULL,  // cancellable
                        &error);

                if (ret == NULL)
                {
                    OIC_LOG_V(ERROR,
                              TAG,
                              "Failed to enable GATT notifications: %s",
                              error->message);

                    g_error_free(error);
                    g_hash_table_remove(address_map, address);
                    success = false;
                }
                else
                {
                    g_variant_unref(ret);
                }
            }
        }
#ifdef TB_LOG
        else
        {
            OIC_LOG_V(WARNING,
                      TAG,
                      "Unrecognized characteristic UUID "
                      "in OIC GATT service: %s",
                      uuid);
        }
#endif

        g_variant_unref(uuid_prop);
        g_object_unref(characteristic);
    }

    g_free(characteristic_paths);
    g_variant_unref(characteristics_prop);

    return success;
}

static bool CAGattClientSetupService(
    GDBusProxy * device,
    GHashTable * characteristic_map,
    GHashTable * address_map,
    GVariant   * services_prop,
    CALEContext * context)
{
    bool success = true;

    GVariant * const address_prop =
        g_dbus_proxy_get_cached_property(device, "Address");

    char const * const address =
        g_variant_get_string(address_prop, NULL);

    /*
      Create a proxies to the org.bluez.GattService1 D-Bus objects
      that implement the OIC Transport Profile on the client side.

      The services_prop argument will be non-NULL if changes to the
      org.bluez.Device1.GattServices property were detected
      asynchronously through the PropertiesChanged signal.
    */
    if (services_prop != NULL)
    {
        /*
          The caller owns the variant so hold on to a reference since
          we assume ownership in this function.
        */
        g_variant_ref(services_prop);
    }
    else
    {
        // Check if GATT services have already been discovered.
        services_prop =
            g_dbus_proxy_get_cached_property(device, "GattServices");
    }

    gsize length = 0;
    char const ** const service_paths =
        services_prop != NULL
        ? g_variant_get_objv(services_prop, &length)
        : NULL;

#ifdef TB_LOG
    if (length == 0)
    {
        // GATT services may not yet have been discovered.
        OIC_LOG_V(INFO,
                  TAG,
                  "GATT services not yet discovered "
                  "on LE peripheral: %s\n",
                  address);
    }
#endif

    gchar const * const * const end = service_paths + length;
    for (gchar const * const * path = service_paths;
         path != end && success;
         ++path)
    {
        // Find the OIC Transport Profile GATT service.
        GError * error = NULL;

        GDBusProxy * const service =
            g_dbus_proxy_new_sync(context->connection,
                                  G_DBUS_PROXY_FLAGS_NONE,
                                  NULL, // GDBusInterfaceInfo
                                  BLUEZ_NAME,
                                  *path,
                                  BLUEZ_GATT_SERVICE_INTERFACE,
                                  NULL, // GCancellable
                                  &error);

        if (service == NULL)
        {
            OIC_LOG_V(ERROR,
                      TAG,
                      "Unable to obtain proxy to GATT service: %s",
                      error->message);

            g_error_free(error);

            success = false;

            break;
        }

        GVariant * const uuid_prop =
            g_dbus_proxy_get_cached_property(service, "UUID");

        char const * const uuid =
            g_variant_get_string(uuid_prop, NULL);

        if (strcasecmp(uuid, CA_GATT_SERVICE_UUID) == 0)
        {
            success = CAGattClientSetupCharacteristics(service,
                                                       address,
                                                       characteristic_map,
                                                       address_map,
                                                       context);

#ifdef TB_LOG
            if (!success)
            {
                OIC_LOG_V(ERROR,
                          TAG,
                          "Characteristic set up for "
                          "GATT service at %s failed.",
                          address);
            }
#endif  // TB_LOG
        }

        g_variant_unref(uuid_prop);
        g_object_unref(service);
    }

    if (services_prop != NULL)
    {
        g_variant_unref(services_prop);
    }

    g_variant_unref(address_prop);

    return success;
}

static void CAGattClientOnDevicePropertiesChanged(
    GDBusProxy * device,
    GVariant * changed_properties,
    GStrv invalidated_properties,
    gpointer user_data)
{
    /*
      This handler is trigged in a GATT client when org.bluez.Device1
      properties have changed.
    */

    (void) invalidated_properties;

    /*
      Retrieve the org.bluez.Device1.GattServices property from the
      changed_properties dictionary parameter (index 1).
    */
    GVariant * const services_prop =
        g_variant_lookup_value(changed_properties, "GattServices", NULL);

    if (services_prop != NULL)
    {
        CALEContext * const context = user_data;

        ca_mutex_lock(g_context.lock);

        CAGattClientSetupService(device,
                                 g_context.characteristic_map,
                                 g_context.address_map,
                                 services_prop,
                                 context);

        ca_mutex_unlock(g_context.lock);

        g_variant_unref(services_prop);
    }
}

CAResult_t CAGattClientInitialize(CALEContext * context)
{
    g_context.lock = ca_mutex_new();

    /*
      Map Bluetooth MAC address to OIC Transport Profile
      request characteristics.
    */
    GHashTable * const characteristic_map =
        g_hash_table_new_full(g_str_hash,
                              g_str_equal,
                              OICFree,
                              g_object_unref);

    /*
      Map OIC Transport Profile response characteristic D-Bus object
      path to Bluetooth MAC address.
    */
    GHashTable * const address_map =
        g_hash_table_new_full(g_str_hash,
                              g_str_equal,
                              OICFree,
                              OICFree);

    ca_mutex_lock(context->lock);

    for (GList * l = context->devices; l != NULL; l = l->next)
    {
        GDBusProxy * const device = G_DBUS_PROXY(l->data);

        /*
          Detect changes in BlueZ Device properties.  This is
          predominantly used to detect GATT services that were
          discovered asynchronously.
        */
        g_signal_connect(
            device,
            "g-properties-changed",
            G_CALLBACK(CAGattClientOnDevicePropertiesChanged),
            context);

        CAGattClientSetupService(device,
                                 characteristic_map,
                                 address_map,
                                 NULL,
                                 context);
    }

    ca_mutex_unlock(context->lock);

    ca_mutex_lock(g_context.lock);

    g_context.characteristic_map = characteristic_map;
    g_context.address_map = address_map;

    ca_mutex_unlock(g_context.lock);

    return CA_STATUS_OK;
}

void CAGattClientDestroy()
{
    if (g_context.lock == NULL)
    {
        return;  // Initialization did not complete.
    }

    ca_mutex_lock(g_context.lock);

    if (g_context.characteristic_map != NULL)
    {
        g_hash_table_unref(g_context.characteristic_map);
        g_context.characteristic_map = NULL;
    }

    if (g_context.address_map != NULL)
    {
        g_hash_table_unref(g_context.address_map);
        g_context.address_map = NULL;
    }

    ca_mutex_unlock(g_context.lock);

    ca_mutex_free(g_context.lock);
    g_context.lock = NULL;

    /*
      We don't explicitly stop notifications on the response
      characteristic since they should be stopped upon server side
      disconnection.
     */
}

// ---------------------------------------------------------------------
//                      GATT Request Data Send
// ---------------------------------------------------------------------

typedef struct BLE_FILE_DESCRIPTOR
{
    int fd;
    char address[18];
}BLE_DEVICES;

extern int count_ble;
extern BLE_DEVICES *ble_pointer;
extern void VITA_WRITE_REQUEST(int fd,uint8_t * data,uint8_t length);

static CAResult_t CAGattClientSendDataImpl(GDBusProxy * characteristic,
                                           uint8_t const * data,
                                           size_t length,
                                           CALEContext * context)
{
    //assert(characteristic != NULL);
    assert(data != NULL);
    assert(context != NULL);
    unsigned char wpdu[512];
    wpdu[0] = 0x12;// BT_ATT_OP_WRITE_REQ;
    wpdu[1]=0x0c;
    wpdu[2]=0x00;
    memcpy(wpdu+3, data, length);
    for(int i = 0; i < count_ble; i++)
    {
        if(ble_pointer[i].fd == -1) {
            CONNECT_IOT_DM(ble_pointer[i].address);
        }
        //printf("%s\n", __func__);
        VITA_WRITE_REQUEST_ADDRESS(ble_pointer[i].fd, wpdu, length+3, ble_pointer[i].address);
    }
    return CA_STATUS_OK;
}

CAResult_t CAGattClientSendData(char const * address,
                                uint8_t const * data,
                                size_t length,
                                CALEContext * context)
{

    assert(context != NULL);
    //printf("CAGattClientSendData===========to one address %s\n\n",address);
    unsigned char wpdu[512];
    wpdu[0] = 0x12;// BT_ATT_OP_WRITE_REQ;
    wpdu[1] = 0x0c;
    wpdu[2] = 0x00;
    memcpy(wpdu+3,data,length);
    for(int i = 0; i < count_ble; i++)
    {
       if(strcmp(address, ble_pointer[i].address) == 0)
        {
           if(ble_pointer[i].fd == -1) {
               CONNECT_IOT_DM(address);
           }
           //printf("\nfd==%d\n",ble_pointer[i].fd);
           //printf("%s\n", __func__);
           VITA_WRITE_REQUEST_ADDRESS(ble_pointer[i].fd, wpdu, length+3, address);
           break;
        }
    }
    return CA_STATUS_OK;
}

CAResult_t CAGattClientSendDataToAll(uint8_t const * data,
                                     size_t length,
                                     CALEContext * context)
{
    assert(context != NULL);

    CAResult_t result = CA_STATUS_FAILED;
    result = CAGattClientSendDataImpl(NULL,
                                      data,
                                      length,
                                      context);

    return result;

}
