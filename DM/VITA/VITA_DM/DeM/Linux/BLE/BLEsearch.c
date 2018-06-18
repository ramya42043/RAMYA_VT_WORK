/**********************************************************************************************
* VOTARYTECH SOFTTECH SOLUTIONS PVT. LTD. CONFIDENTIAL [2009]-[2016]
*  All Rights Reserved. *
* NOTICE: This file is part of {project}.
* All information contained herein is, and remains the property of Votary Softech Solutions Pvt. Ltd.
* and its suppliers,if any.
* Dissemination of this information or reproduction of this material  is strictly forbidden unless prior written permission is obtained
* from Votary Softech Solutions Pvt. Ltd.
.
Author:                                                Date:
Description:

Revision History
----------------------
Bug ID:                                             Author:                                                                Date:
ChangeID:                                           Author:                                                                Date:
************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#define implement 0
#if implement
#include "BLEsearch.h"
#include <stdlib.h>
#include <errno.h>
#include <curses.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <pthread.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>

#define HCI_STATE_NONE       0
#define HCI_STATE_OPEN       2
#define HCI_STATE_SCANNING   3
#define HCI_STATE_FILTERING  4
#define HCI_MAX_EVENT_SIZE   260
#define BLE_SCAN_TO_READ_DELAY 3
#define EIR_FLAGS                   0X01
#define EIR_NAME_SHORT              0x08
#define EIR_NAME_COMPLETE           0x09
#define EIR_MANUFACTURE_SPECIFIC    0xFF
#define MIN(x,y)    ((x)<(y)?(x):(y))

/********************************************
 * PROTOTYPES
 *
*/
int32_t DM_BLE_Scan(DM_BLE_ScanResult_Info_t *);

struct hci_state open_default_hci_device(void );

void start_hci_scan (struct hci_state );

int32_t get_advt_data (uint32_t , uint8_t *, int32_t );

int32_t get_device_name (uint8_t *, uint32_t , uint8_t *, uint8_t *,int8_t *);

uint8_t buf1[HCI_MAX_EVENT_SIZE] = { 0 };

/*.................................................................*/
int32_t DM_BLE_Scan(DM_BLE_ScanResult_Info_t *resultData) {
    uint32_t handler;
    uint8_t buf[HCI_MAX_EVENT_SIZE] = { 0 };
    int32_t len;
    int8_t rssi;
    int32_t error;
    int8_t name[100];
    int8_t addr[18];
    extern int32_t errno;
    int32_t ble_count = 0;
    struct hci_state open_default_hci_device();
    struct hci_state current_hci_state = open_default_hci_device();
    handler = current_hci_state.device_handle;
    start_hci_scan (current_hci_state);
    while (get_advt_data(handler, buf, HCI_MAX_EVENT_SIZE) != -1) {
        sleep(1);
        if (len > 0) {
            error = get_device_name (buf, len, name, addr,&rssi);
            if (error == 0) {
                memcpy(resultData[ble_count].ble_name, name, strlen(name));
                memcpy(resultData[ble_count].ble_addr, addr, strlen(addr));
                resultData[ble_count].ble_rssi = rssi;
                ble_count++;
            }
        }
    }
    if (hci_le_set_scan_enable (current_hci_state.device_handle,
                                0x00, 1, 1000) < 0) {
        current_hci_state.has_error = TRUE;
        printf("Failed to disable scan");
        return ;
    }
    if( hci_close_dev(current_hci_state.device_handle)<0) {
        current_hci_state.has_error = TRUE;
        printf("Failed to close");
        return 0;
    }
    resultData[0].num_elements = ble_count;
    return ble_count;
}

/*..................................................................*/
struct hci_state open_default_hci_device(void) {
    struct hci_state current_hci_state = { 0 };
    current_hci_state.device_id = hci_get_route (NULL);

    if ((current_hci_state.device_handle =
         hci_open_dev (current_hci_state.device_id)) < 0) {
        current_hci_state.has_error = TRUE;
        snprintf(current_hci_state.error_message,
                 sizeof (current_hci_state.error_message),
                 "Could not open device: %s", strerror (errno));
        return current_hci_state;
    }
    // Set fd non-blocking
    int32_t on = 1;
    if (ioctl (current_hci_state.device_handle, FIONBIO, (int8_t *) &on) < 0) {
        current_hci_state.has_error = TRUE;
        snprintf(current_hci_state.error_message,
                 sizeof (current_hci_state.error_message),
                 "Could set device to non-blocking: %s", strerror (errno));
        return current_hci_state;
    }
    
    if (ioctl(current_hci_state.device_handle, HCIDEVDOWN, 0) < 0) {
        perror("error in device down");
    }
    
    if (ioctl(current_hci_state.device_handle, HCIDEVUP, 0) < 0) {
        perror("error in device up");
    }
    
    current_hci_state.state = HCI_STATE_OPEN;
    
    return current_hci_state;
}
/*................................................................................*/
void start_hci_scan (struct hci_state current_hci_state) {
    if (hci_le_set_scan_parameters(current_hci_state.device_handle, 0x01,
                                   htobs (0x0640), htobs (0x0640),
                                   0x00, 0x00, 1000) < 0) {
        current_hci_state.has_error = TRUE;
        snprintf (current_hci_state.error_message,
                  sizeof (current_hci_state.error_message),
                  "Failed to set scan parameters: %s", strerror (errno));
        printf("error in return\n");
        return ;
    }
    
    if (hci_le_set_scan_enable (current_hci_state.device_handle,
                                0x01, 1, 1000) < 0) {
        current_hci_state.has_error = TRUE;
        snprintf (current_hci_state.error_message,
                  sizeof (current_hci_state.error_message),
                  "Failed to enable scan: %s", strerror (errno));
        return ;
    }
    current_hci_state.state = HCI_STATE_SCANNING;
    // Save the current HCI filter
    socklen_t olen = sizeof (current_hci_state.original_filter);
    if (getsockopt(current_hci_state.device_handle, SOL_HCI, HCI_FILTER,
                   &current_hci_state.original_filter, &olen) < 0) {
        current_hci_state.has_error = TRUE;
        snprintf (current_hci_state.error_message,
                  sizeof (current_hci_state.error_message),
                  "Could not get socket options: %s", strerror (errno));
        return ;
    }
    // Create and set the new filter
    struct hci_filter new_filter;
    hci_filter_clear (&new_filter);
    hci_filter_set_ptype (HCI_EVENT_PKT, &new_filter);
    hci_filter_set_event (EVT_LE_META_EVENT, &new_filter);
    if (setsockopt(current_hci_state.device_handle, SOL_HCI,
                   HCI_FILTER, &new_filter,sizeof (new_filter)) < 0) {
        current_hci_state.has_error = TRUE;
        snprintf (current_hci_state.error_message,
                  sizeof (current_hci_state.error_message),
                  "Could not set socket options: %s", strerror (errno));
        return ;
    }
    current_hci_state.state = HCI_STATE_FILTERING;
    sleep(BLE_SCAN_TO_READ_DELAY);
}
/*********************************************************************************/
int32_t get_advt_data (uint32_t handler, uint8_t *buf, int32_t buf_len) {
    int32_t len = 0;
    memset(buf,0,buf_len);
    while ((len = read (handler, buf, buf_len)) < 0) {
        return -1;
    }
    return len;
}
/*********************************************************************************/

int32_t get_device_name (uint8_t *buf, uint32_t len, uint8_t *name,
                         uint8_t *addr,int8_t *rssi) {
    hci_event_hdr *hdr = (void *) (buf + 1);
    evt_le_meta_event *meta = (void *) buf + (1 + HCI_EVENT_HDR_SIZE);
    le_advertising_info *info = (le_advertising_info *) (meta->data + 1);
    int32_t error = 1;
    int32_t current_index = 0;
    int32_t data_error = 0;
    uint8_t *data;
    data = malloc (100);
    len -= (1 + HCI_EVENT_HDR_SIZE);
    // Determine Range(RSSI)
    int8_t rssi1;
    rssi1 = info->data[info->length];
    switch (hdr->evt) {
        case EVT_CMD_STATUS: {
            printf("EVT_CMD_STATUS");
            break;
        }
        case EVT_CMD_COMPLETE: {
            printf("EVT_CMD_COMPLETE");
            break;
        }
        case EVT_REMOTE_NAME_REQ_COMPLETE: {
            printf("EVT_REMOTE_NAME_REQ_COMPLETE");
            break;
        }
        case EVT_LE_META_EVENT: {
            while (!data_error && current_index < info->length) {
                size_t data_len = info->data[current_index];
                if (data_len + 1 > info->length) {
                    data_error = 1;
                }
                else {
                    data = info->data + current_index + 1;
                    if (data[0] == EIR_NAME_SHORT || data[0] == EIR_NAME_COMPLETE) {
                        size_t name_len = data_len - 1;
                        memset (name, 0, name_len + 1);
                        memcpy (name, &data[1], name_len);
                        ba2str (&info->bdaddr, addr);
                        error = 0;
                    }
                    else {
                        ba2str(&(info->bdaddr), addr);
                        memset (name, 0, 7 + 1);
                        memcpy (name, "Unknown", 7);
                        error = 0;
                    }
                    *rssi = rssi1;
                    current_index += data_len + 1;
                }
            return error;
            }			//moving to next stucture within a packet
        break;
        }
        default:
            break;
    }
    return 0;
}
#endif
/*****************************************************************************
 * NOTES:
 *
 *
 *
 *
 */
