/***************************************************************************
 ***************************************************************************
 * NAME           :   noniotivity.h
 *
 * DESCRIPTION    :   Function Prototypes
 *
 * LICENSE        :
 *
 * Copyright 2017 VotaryTech All Rights Reserved.
 *
 ***************************************************************************
 ***************************************************************************/

#include "../../../api/cacommon.h"

#define ATT_CID 4
#define BT_ATT_OP_ERROR_RSP                 0x01
#define BT_ATT_OP_MTU_REQ                   0x02
#define BT_ATT_OP_FIND_INFO_REQ             0x04
#define BT_ATT_OP_READ_BY_GRP_TYPE_REQ		0x10
#define BT_ATT_OP_FIND_INFO_RSP             0x05
#define BT_ATT_OP_READ_REQ                  0x0a
#define BT_ATT_OP_WRITE_REQ                 0x12
#define BT_ATT_OP_WRITE_RSP                 0x13
#define ATT_OP_HANDLE_NOTIFY		        0x1B


/*
 * GATT Characteristic Property bit field
 * Reference: Core SPEC 4.1 page 2183 (Table 3.5: Characteristic Properties
 * bit field) defines how the Characteristic Value can be used, or how the
 * characteristic descriptors (see Section 3.3.3 - page 2184) can be accessed.
 * In the core spec, regular properties are included in the characteristic
 * declaration, and the extended properties are defined as descriptor.
 */

#define GATT_CHR_PROP_BROADCAST				0x01
#define GATT_CHR_PROP_READ				    0x02
#define GATT_CHR_PROP_WRITE_WITHOUT_RESP    0x04
#define GATT_CHR_PROP_WRITE				    0x08
#define GATT_CHR_PROP_NOTIFY				0x10
#define GATT_CHR_PROP_INDICATE				0x20
#define GATT_CHR_PROP_AUTH				    0x40
#define GATT_CHR_PROP_EXT_PROP				0x80

/* Client Characteristic Configuration bit field */
#define GATT_CLIENT_CHARAC_CFG_NOTIF_BIT	0x0001
#define GATT_CLIENT_CHARAC_CFG_IND_BIT		0x0002


#define MAX_SIZE                            200
#define MAX_BLE_DEVICES                     100 /////////NON-IOTIVITY Devices Maximum number of device
#define MAX_URI_NAME                        50
#define MAX_DEVICE_NAME                     50
#define MAX_JSON_KEY                        50
#define MAX_JSON_VALUE                      512
#define MAX_MAC_ID                          50
#define CHAR_TABLE_LENGTH                   200

#define PRLOG(...) \
    printf(__VA_ARGS__); print_prompt();

typedef struct
{
    uint16_t uuid;
    const char *str;
} uuid_table_t;

typedef struct information
{
    unsigned char type[16];
    unsigned char value[512];
    uint16_t handle;
    uint16_t type_uuid;
} info;

typedef unsigned short int uint16_t;
typedef unsigned char 	uint8_t;

typedef enum{
    DISCOVERED
}Device_State;

typedef struct
{
    char type[16];
    char value[512];
    uint16_t handle;
} Characteristic_Table_t;

typedef struct
{
    unsigned char ucURI[MAX_URI_NAME];
    unsigned char ucDeviceName[MAX_DEVICE_NAME];
    unsigned char ucMacId[MAX_MAC_ID];
    key_value_pair_t1 *pJSON;  //key_value_pair_t
    Characteristic_Table_t GattTable[CHAR_TABLE_LENGTH];
    unsigned char GattTableIndex;
    Device_State eState;
}BLE_DeviceInfo_t;

typedef struct
{
    unsigned char ucNumOfDevices;
    BLE_DeviceInfo_t BLE_DeviceInfo[MAX_BLE_DEVICES];
}BLE_Device_InfoTable_t;

void terminateListofDevices(void);
