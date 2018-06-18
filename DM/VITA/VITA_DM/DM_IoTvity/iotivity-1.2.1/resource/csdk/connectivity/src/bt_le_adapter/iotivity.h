#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <limits.h>
#include <errno.h>
#include <pthread.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/l2cap.h>

struct BLE_ADDRESS_FILTER {
    int8_t address[100][18];
}ble_address_filter;
enum connection_type_status {
    GET_STATE = 1,
    PUT_STATE = 2,
    OBSERVER_STATE = 3,
    CANCEL_OBSERVE_STATE = 4,
    DELETE_STATE = 5,
    DISCONNECTED_STATE = 6
}connection_status;
typedef struct BLE_FILE_DESCRIPTOR {
    int32_t fd;
    int8_t address[18];
    int32_t state;//0 for start_observe 1 for cancel_observe 1 is the default
}BLE_DEVICES;
#define BT_ATT_OP_MTU_REQ			0x02
#define BT_ATT_OP_WRITE_REQ			0x12
#define ATT_CID     					4


/**************************************************************************
 * PROTOTYPES
 */
int32_t FILTER_ADDRESS(int8_t *);
int8_t ADD_ADDRESS(int8_t *);
CAResult_t CALEAdapterClientReceivedDataEX(const int8_t *,
                                           const uint8_t *,
                                           uint32_t ,
                                           uint32_t *);
void Disable_Connection_Each_Device(int8_t *);
void VITA_WRITE_REQUEST(int32_t ,
                        uint8_t *,
                        uint8_t );
void VITA_WRITE_REQUEST_ADDRESS(int32_t ,
                                uint8_t *,
                                uint8_t ,
                                char *);
int32_t CONNECT_IOT_DM(int8_t* );
void add_to_ble_structure(int32_t FD, int8_t * );
void enable_notification(int32_t );
void mtu_request(int32_t );
void init(int8_t* );
void *read_data(void *);
static int32_t l2cap_le_att_connect(bdaddr_t *,
                                    bdaddr_t *,
                                    uint8_t ,
                                    int32_t );
int32_t update_status(int32_t );
bool check_for_ble_status_flag(void);
