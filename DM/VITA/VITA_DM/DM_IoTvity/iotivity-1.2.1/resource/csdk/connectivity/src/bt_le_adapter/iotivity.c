#include "iotivity.h"
int32_t count_ble = 0;
BLE_DEVICES ble_devices[10];
BLE_DEVICES * ble_pointer = ble_devices;
int32_t ble_address_count = 0;//for IOT and NON-IOT devices count
int32_t connect_status=0;
int32_t fd;
pthread_t tid;
static bool verbose = true;
extern int32_t observe_flag;
enum observe_status{
    START_OBSERVE = 0,
    CANCEL_OBSERVE =1,
    DEFAULT = 2
};
/*..........................................................................*/
void terminateListofIOTDevices(void) {
    ble_address_count = 0;
    return ;
}
/*..........................................................................*/
int32_t FILTER_ADDRESS(int8_t *ADDRESS) {
    int32_t i = 0;
    for (i = 0; i < ble_address_count; i++) {
        if (strcasecmp(ble_address_filter.address[i], ADDRESS) == 0) {
            return 0;
        }
    }
    return 1;
}
/*..........................................................................*/
int8_t ADD_ADDRESS(int8_t *ADDRESS) {
    int32_t i=0;
    for (i = 0; i < ble_address_count; i++) {
        if (strcasecmp(ble_address_filter.address[i], ADDRESS) == 0) {
            return 1;//for failure
        }
    }
    memcpy(ble_address_filter.address[i],ADDRESS,18);
    //memcpy(ble_address_filter.address[ble_address_count],ADDRESS,18);
    ble_address_count++;
    return 0;//for success
}
/*..........................................................................*/
//*************Disable connection for one****************
void Disable_Connection_Each_Device(int8_t *ADDRESS){
    int32_t i = 0;
    //printf("%s Address %s\n", __func__, ADDRESS);
    for (i =0; i < count_ble; i++) {
        if (strcasecmp(ADDRESS, ble_devices[i].address) == 0) {
            close(ble_devices[i].fd);
            ble_devices[i].fd = -1;
            //ble_devices[i].state = DISCONNECTED_STATE;
            sleep(1);
        }
    }
    return ;
}
//*************Disable connection for one****************
/*..........................................................................*/
void VITA_WRITE_REQUEST(int32_t file_descriptor,
                        uint8_t *data,
                        uint8_t length) {
    uint8_t len;
    int32_t i = 0;
    //printf("%s\n", __func__);
    len = write( file_descriptor, data, length );
    int8_t address[18];
    for (i = 0; i < count_ble; i++) {
        if (file_descriptor == ble_devices[i].fd) {
            memcpy(address, ble_devices[i].address, 18);
            break;
        }
    }
    if (len != length) {
        printf(" Write Failure length = %d\n", len);
        CONNECT_IOT_DM(address);
        for (i = 0; i < count_ble; i++) {
            if (strcmp(address, ble_devices[i].address)==0) {
                file_descriptor = ble_devices[i].fd;
                len = write(file_descriptor, data, length );
                break;
            }
        }
    }
    sleep(1);
    return;
}
/*..........................................................................*/
void VITA_WRITE_REQUEST_ADDRESS(int32_t file_descriptor,
                                uint8_t *data,
                                uint8_t length,
                                char *ADDRESS) {
    uint8_t len;
    int32_t i = 0;
    if (file_descriptor == -1) {
        file_descriptor = CONNECT_IOT_DM(ADDRESS);
//        if (CONNECT_IOT_DM(ADDRESS)) {
//            for (i = 0; i<count_ble; i++) {
//                if (strcasecmp(ble_devices[i].address,ADDRESS) == 0) {
//                    file_descriptor = ble_devices[i].fd;
//                    printf("Updated file descriptor\n");
//                    break;
//                }
//            }
//        }
    }
    len = write(file_descriptor, data, length);
    //printf("write length %d\n",len);
    if (len != length) {
        //printf(" Write Failure\n");
        //printf("fd %d\n", file_descriptor);
        file_descriptor = CONNECT_IOT_DM(ADDRESS);
        len = write(file_descriptor, data, length );
//        for (i = 0; i < count_ble; i++) {
//            if (strcmp(ADDRESS, ble_devices[i].address) == 0) {
//                file_descriptor = ble_devices[i].fd;
//                printf("fd %d \n", file_descriptor);
//                len = write(file_descriptor, data, length );
//                break;
//            }
//        }
    }
    sleep(1);
    return;
}
/*..........................................................................*/
bool check_for_ble_status_flag(void) {
    if(connect_status == 1) {
        return true;
    }
    else {
        return false;
    }
}
/*..........................................................................*/
int32_t update_status(int32_t value) {
    connect_status = value;
}
/*..........................................................................*/
static int32_t l2cap_le_att_connect(bdaddr_t *src,
                                    bdaddr_t *dst,
                                    uint8_t dst_type,
                                    int32_t sec) {
    int32_t sock;
    struct sockaddr_l2 srcaddr, dstaddr;
    struct bt_security btsec;
    if (verbose) {
        int8_t srcaddr_str[18], dstaddr_str[18];
        ba2str(src, srcaddr_str);
        ba2str(dst, dstaddr_str);
    }
    sock = socket(PF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
    if (sock < 0) {
        perror("Failed to create L2CAP socket");
        return -1;
    }
    /* Set up source address */
    memset(&srcaddr, 0, sizeof(srcaddr));
    srcaddr.l2_family = AF_BLUETOOTH;
    srcaddr.l2_cid = htobs(ATT_CID);
    srcaddr.l2_bdaddr_type = 0;
    bacpy(&srcaddr.l2_bdaddr, src);
    if (bind(sock, (struct sockaddr *)&srcaddr, sizeof(srcaddr)) < 0) {
        perror("Failed to bind L2CAP socket");
        close(sock);
        return -1;
    }
    /* Set the security level */
    memset(&btsec, 0, sizeof(btsec));
    btsec.level = sec;
    if (setsockopt(sock, SOL_BLUETOOTH, BT_SECURITY, &btsec,
                   sizeof(btsec)) != 0) {
        fprintf(stderr, "Failed to set L2CAP security level\n");
        close(sock);
        return -1;
    }
    /* Set up destination address */
    memset(&dstaddr, 0, sizeof(dstaddr));
    dstaddr.l2_family = AF_BLUETOOTH;
    dstaddr.l2_cid = htobs(ATT_CID);
    dstaddr.l2_bdaddr_type = dst_type;
    bacpy(&dstaddr.l2_bdaddr, dst);
    printf("Connecting to device...");
    if (connect(sock, (struct sockaddr *) &dstaddr, sizeof(dstaddr)) < 0) {
        //perror(" Failed to connect");
        close(sock);
        return -1;
    }
    printf("Done\n");
    return sock;
}
/*..........................................................................*/
void check_for_connection_status(int8_t * address) {
    int32_t i = 0;
    for (i = 0; i < count_ble; i++) {
        if (strcasecmp(address, ble_pointer[i].address) == 0) {
            if (ble_devices[i].state == DISCONNECTED_STATE)
                sleep(2);
        }
    }
    return ;
}

/*..........................................................................*/
void *read_data(void *address_original) {
    uint8_t rpdu[512];
    int32_t len = 0,temp;
    int8_t address[18];
    memcpy(address, (int8_t*)address_original,18);
    int32_t i = 0,fd;
    int32_t state = 2;
    while(1) {
        sleep(2);
        state = 2;
        for(i = 0; i < count_ble; i++) {
            if(strcasecmp(address, ble_devices[i].address) == 0 ) {
                fd = ble_devices[i].fd;
                state = ble_devices[i].state;
            }
        }
        memset(rpdu, 0, sizeof(rpdu));
//        printf("state %d fd %d\n", state, fd);
        len = read(fd, rpdu, 512);
        if(len != -1 && state != 1) {
//            printf("length %d \n");
            if(state == 2 || state == 0) {
                if(rpdu[0] == 0x1B) {
                    CALEAdapterClientReceivedDataEX(address, (const uint8_t *)rpdu+3, len-3, &temp);
                    printf("Packet Up....\n");
                    //check_for_connection_status(address);
                }//wpdu
                if(rpdu[0] == 0x13) {
                    printf("Response ok\n");
                }
            }
        }//len
        else {
            //if read task fails in observation state, then maintain connection
            if (state == START_OBSERVE) {
//                printf("In Start observe\n");
                if (fd == -1) {
                    sleep(1);
                    CONNECT_IOT_DM(address);
                }
            }
            else if (state == CANCEL_OBSERVE) {
//                printf("In Cancel observe\n");
                sleep(4);
                add_to_ble_structure_state(DEFAULT, address);
                ///Nothing
            }
            else if (state == DEFAULT) {
                //nothing
            }

        }
        //printf("rpdu = %.4x\n",rpdu[0]);
    }//while
    return ;
}
/*..........................................................................*/
void init(int8_t* address) {
    int32_t error;
    error = pthread_create(&tid, NULL, read_data, (void *)address);
    if(error != 0) {
        printf("thread creation failed\n");
    }
    return;
}
/*..........................................................................*/
void mtu_request(int32_t fd) {
    uint8_t wpdu[5];
    uint8_t rpdu[5];
    uint32_t size=0;
    wpdu[0] = BT_ATT_OP_MTU_REQ;
    wpdu[1] = 0x00;
    wpdu[2] = 0x01;
    size = write(fd, wpdu, 3);
    sleep(1);
    size = read(fd, rpdu, 3);
    return ;
}
/*..........................................................................*/
void enable_notification(int32_t fd) {
    uint8_t wpdu[10];
    uint8_t len = 0;
    memset(wpdu, '\0', 10);
    wpdu[0] = BT_ATT_OP_WRITE_REQ;
    wpdu[1] = 0x10;
    wpdu[2] = 0x00;
    wpdu[3] = 0x01;
    wpdu[4] = 0x00;
    //VITA_WRITE_REQUEST(fd, wpdu, 5);
    len = write( fd, wpdu, 5 );
    //sleep(1);
    return ;
}
/*..........................................................................*/
void add_to_ble_structure_state(int32_t state, int8_t * address) {
    int32_t i = 0;
    for(i = 0 ; i < count_ble ; i++ ) {
        if(strcasecmp(ble_devices[i].address, address) == 0) {
            ble_devices[i].state = state;
            return;
        }
    }
}

/*..........................................................................*/
void add_to_ble_structure(int32_t FD, int8_t * ADDRESS) {
    int32_t i = 0;
    for(i = 0 ; i < count_ble ; i++ ) {
        if(strcasecmp(ble_devices[i].address, ADDRESS) == 0) {
            ble_devices[i].fd = FD;
            return;
        }
    }
    ble_devices[count_ble].fd = FD;
    memcpy(ble_devices[count_ble].address,ADDRESS,18);
    ble_devices[count_ble].state = 2;
    count_ble++;
    init(ADDRESS);
    return ;
}
/*..........................................................................*/
int32_t CONNECT_IOT_DM(int8_t* dst_address) {
    int32_t count_try=0;
    int32_t sec = BT_SECURITY_LOW;
    uint8_t dst_type = BDADDR_LE_PUBLIC;
    bdaddr_t src_addr, dst_addr;
    int32_t dev_id = -1;
    if (str2ba(dst_address, &dst_addr) < 0) {
        perror("Invalid remote address:\n");
        return false;
    }
    if (dev_id == -1) {
        bacpy(&src_addr, BDADDR_ANY);
    }
    else if (hci_devba(dev_id, &src_addr) < 0) {
        perror("Adapter not available");
        return false;
    }
        fd = l2cap_le_att_connect(&src_addr, &dst_addr, dst_type, sec);
        if(fd < 0) {
            return false;
        }
    //mtu_request(fd);

    enable_notification(fd);
    add_to_ble_structure(fd, dst_address);
    return fd;
}
/*..........................................................................*/
CAResult_t CALEAdapterClientReceivedDataEX(const int8_t *remoteAddress,
                                           const uint8_t *data,
                                           uint32_t dataLength,
                                           uint32_t *sentLength) {
    OIC_LOG(DEBUG, CALEADAPTER_TAG, "IN");
    //Input validation
    VERIFY_NON_NULL(data, CALEADAPTER_TAG, "Data is null");
    VERIFY_NON_NULL(sentLength, CALEADAPTER_TAG, "Sent data length holder is null");
#ifndef SINGLE_THREAD
    VERIFY_NON_NULL_RET(g_bleReceiverQueue, CALEADAPTER_TAG,
                        "g_bleReceiverQueue",
                        CA_STATUS_FAILED);

    //Add message to data queue
    CAEndpoint_t *remoteEndpoint = CACreateEndpointObject(CA_DEFAULT_FLAGS,
                                                          CA_ADAPTER_GATT_BTLE,
                                                          remoteAddress, 0);
    if (NULL == remoteEndpoint) {
        OIC_LOG(ERROR, CALEADAPTER_TAG, "Failed to create remote endpoint !");
        return CA_STATUS_FAILED;
    }
    OIC_LOG_V(DEBUG, CALEADAPTER_TAG, "Data received from LE layer [%u]", dataLength);
    // Create bleData to add to queue
    CALEData_t *bleData = CACreateLEData(remoteEndpoint, data,
                                         dataLength, g_bleClientSenderInfo);
    if (!bleData) {
        OIC_LOG(ERROR, CALEADAPTER_TAG, "Failed to create bledata!");
        CAFreeEndpoint(remoteEndpoint);
        return CA_MEMORY_ALLOC_FAILED;
    }
    CAFreeEndpoint(remoteEndpoint);
    // Add message to receiver queue
    CAQueueingThreadAddData(g_bleReceiverQueue, bleData, sizeof(CALEData_t));
    *sentLength = dataLength;
#endif
    OIC_LOG(DEBUG, CALEADAPTER_TAG, "OUT");
    return CA_STATUS_OK;
}
//****************VITA_DM_BLE_IMPLEMENTATION END*************





