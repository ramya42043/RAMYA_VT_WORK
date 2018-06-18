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
#ifndef VITA_DM_INTERNAL_H
#define VITA_DM_INTERNAL_H

#include <stdbool.h>
#include <stdint.h>

#include "VITA_DM.h"

#ifdef __cplusplus
extern "C" {
#endif

//!Declarations for DM Module
#define MAX_NAME_SIZE 248
#define MAX_ADDR_SIZE 19
#define MAX_SCAN_ELEMENTS 100
#define TIMEOUT 10 //!MAXIMUM retries for a particular scan

#define BLE_TIMEOUT 4 //!MAXIMUM retries for a BLE scan


typedef struct {
    int8_t bt_name[MAX_NAME_SIZE];
    int8_t bt_addr[MAX_ADDR_SIZE];
    uint32_t num_elements;
    uint32_t bt_class;
}DM_BT_ScanResult_Info_t; //!BLUETOOTH SCAN DATA STRUCTURE

typedef struct {
    uint32_t num_elements;
    uint32_t strength;
    int8_t frequency[10];
    int8_t wifi_device_names[MAX_NAME_SIZE];
    int8_t macAddr[MAX_ADDR_SIZE];
}DM_WIFI_ScanResult_Info_t; //!WIFI SCAN DATA STRUCTURE

typedef struct {
    int8_t ble_name[MAX_NAME_SIZE];
    int8_t ble_addr[MAX_ADDR_SIZE];
    uint32_t num_elements;
    int8_t ble_rssi;
}DM_BLE_ScanResult_Info_t; //!BLE SCAN DATA STRUCTURE


//!BT Block
int32_t VITA_DM_BT_Init(void);
int32_t VITA_DM_BT_Scan(VITA_SCAN_Type scanType);
void VITA_DM_BT_Abort(void);
void *BT_Scan_Task(void *input);
void VITA_DM_BT_PostResponce(VITA_SCAN_Type scanType, DM_BT_SCAN_RESPONCE_e bt_response);
//!BT Block

//!WIFI Block
int32_t VITA_DM_WIFI_Init();
int32_t VITA_DM_WIFI_Scan(VITA_SCAN_Type scanType);
void VITA_DM_WIFI_Abort(void);
void *WIFI_Scan_Task(void *input);
void VITA_DM_WiFi_PostResponce(VITA_SCAN_Type scanType, DM_WIFI_SCAN_RESPONCE_e wifi_response);
//!WIFI Block

//!BLE Block
int32_t VITA_DM_BLE_Init(void);
int32_t VITA_DM_BLE_Scan(VITA_SCAN_Type scanType);
void VITA_DM_BLE_Abort(void);
void *BLE_Scan_Task(void *input);
void VITA_DM_BLE_PostResponce(VITA_SCAN_Type scanType, DM_BLE_SCAN_RESPONCE_e bt_response);
//!BLE Block



void VITA_DM_INIT_PostResponce(DM_INIT_RESPONCE_e init_response);

VITA_SCAN_Type VITA_DM_getScanParameters(void);
//void VITA_DM_SetScanParameters(DM_Scan_cmd_data scanData);

//bool DM_GetAbortStatus(void);
//bool DM_SetAbortStatus(bool value);
uint32_t DM_GetSM_URL(int8_t **url);
uint32_t DM_Get_Device_ID(int8_t **deviceid);
void VITA_DM_cleanup();
DM_WIFI_DSM_Filter_t DM_get_wifi_filter(void);
DM_BT_DSM_Filter_t DM_get_bt_filter(void);
DM_BLE_DSM_Filter_t DM_get_ble_filter(void);


//!IOTVITY BLOCK
typedef struct {
    int8_t name[MAX_NAME_SIZE];
    int8_t id[50];
    int32_t signal;
}DM_IoTvity_discover_Info_t; //!BLUETOOTH SCAN DATA STRUCTURE

//!

#ifdef __cplusplus
}
#endif

#endif //VITA_DM_H
