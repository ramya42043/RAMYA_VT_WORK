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
#ifndef VITA_DM_H
#define VITA_DM_H
#include<stdio.h>
#include<stdint.h>
#include<json/json.h>

#define MAX_NAME_SIZE 248
//#define IS_MQTT_ENABLED
typedef void * handle_t;
typedef void (*onGet_ptr)(handle_t, json_object*);
typedef void (*onPut_ptr)(handle_t, json_object*);
typedef void (*onobserve_ptr)(handle_t, json_object*);
typedef void (*onDelete_ptr)(handle_t);
typedef void* handle_t;

typedef struct {
    int8_t name[MAX_NAME_SIZE];
    int8_t id[50];
    int32_t signal;
}DM_IoTvity_discover_Info_t; //!BLUETOOTH SCAN DATA STRUCTURE

typedef struct
{
    char name[40];
    handle_t handle;
}Resource_info;

typedef void (*disc_ptr)(Resource_info*);

/*Prototypes
 *
 */
uint32_t VITA_DM_Init(void);
void onFoundResource(Resource_info*);
uint32_t VITA_DM_Discover(disc_ptr);
int32_t DM_DeM_Init(void);
int32_t DM_DeM_Discovery(disc_ptr);
/* PROTOTYPES
 *
 */
int32_t VITA_DM_DSM_IotVity_Get_Data (const char*, json_object*);
int32_t VITA_DM_DSM_IotVity_Observe_Data (const char*, json_object*);
void DM_onObserve(handle_t, json_object*);
void DM_onGet(handle_t, json_object*);
void VITA_DM_Get(const char*, onGet_ptr);
void VITA_DM_Put(const char *, json_object*);
void DM_DeM_Delete(const char*, onDelete_ptr);
void VITA_DM_Delete(const char*, onDelete_ptr);
void DM_onDelete(handle_t);

#define MODULE_IMPLEMENT 0
#if MODULE_IMPLEMENT
#ifdef __cplusplus
extern "C" {
#endif
#include <json-c/json.h>
#include <curl/curl.h>


//! For Bluetooth
#define BT_Param_Name "Name"
#define BT_Param_DeviceID "DeviceID"
#define BT_Param_Class "Class_Name"

//! For WIFI
#define WIFI_Param_Name "Name"
#define WIFI_Param_DeviceID "DeviceID"
#define WIFI_Param_Signal "Signal"
#define WIFI_Param_Frequency "Frequency"

//! For BLE
#define BLE_Param_Name "Name"
#define BLE_Param_DeviceID "DeviceID"
#define BLE_Param_Class "Class_Name"


#define MAX_SCAN_CMD_SIZE 50
#define DM_DEVICEID_SIZE 50
#define DM_SM_URL_SIZE 255
//#define TEST
typedef void* handle_t;
//typedef struct
//{
//    char name[40];
//    handle_t handle;
//}Resource_info;

//typedef void (*disc_ptr)(Resource_info*);
typedef void (*onGet_ptr)(handle_t,json_object*);
typedef void (*onPut_ptr)(handle_t,json_object*);
typedef void (*onobserve_ptr)(handle_t,json_object*);

typedef enum {
    DEVICE_BLUETOOTH = 1,
    DEVICE_WIFI,
    DEVICE_BLE,
    DEVICE_ALL
    //! Need to add if more devices supported is required
}VITA_DM_DEVICETYPE_e; //!Type of devices supported

typedef enum {
    AUTO = 1,
    MANUAL
}VITA_SCAN_Type; //!Scan Type Auto or Manual

typedef enum {
    VITA_DM_INIT_SUCESS,
    VITA_DM_INIT_FAIL,
}DM_INIT_RESPONCE_e; //! Type of INIT scan status

typedef enum {
    STATE_INIT = 1,
    STATE_READY,
    STATE_SCANNING_AUTO,
    STATE_SCANNING_MANUAL,
    STATE_SCANNING_ABORT
}Scanning_State_e;

//! BT Filter Block
typedef  enum {
    VITA_DM_BT_SCAN_SUCESS,
    VITA_DM_BT_SCAN_FAIL,
    VITA_DM_BT_SCAN_STORE_FAIL,
    VITA_DM_BT_SCAN_NO_DEVICE_FOUND,
    VITA_DM_BT_SCAN_ABORTED,
    VITA_DM_BT_SCAN_PROGRESS
}DM_BT_SCAN_RESPONCE_e; //! Type of BT scan status

typedef struct {

} DM_BT_DeM_Filter_t;

typedef struct {

} DM_BT_CM_Filter_t;

typedef struct {
    int bIncludeBtName;
    int bIncludeBtDeviceID;
    int bIncludeBtClass;
} DM_BT_DSM_Filter_t;
//! BT Filter Block

typedef struct {
    //DM_BT_DeM_Filter_t DM_BT_DeM_Filter;
    //DM_BT_CM_Filter_t  DM_BT_CM_Filter;
    DM_BT_DSM_Filter_t DM_BT_DSM_Filter;
}DM_BT_VITA_Filter_t;

//!WIFI Filter Block
typedef enum {
    VITA_DM_WIFI_SCAN_SUCESS,
    VITA_DM_WIFI_SCAN_FAIL,
    VITA_DM_WIFI_SCAN_STORE_FAIL,
    VITA_DM_WIFI_SCAN_NO_DEVICE_FOUND,
    VITA_DM_WIFI_SCAN_ABORTED,
    VITA_DM_WIFI_SCAN_PROGRESS
}DM_WIFI_SCAN_RESPONCE_e; //! Type of WIFI scan status

typedef struct {

}DM_WIFI_DeM_Filter_t;

typedef struct {

}DM_WIFI_CM_Filter_t;

typedef struct {
    int bIncludeWifiName;
    int bIncludeWifiSignal;
    int bIncludeWifiDeviceID;
    int bIncludeWifiFrequency;
}DM_WIFI_DSM_Filter_t;
//!WIFI Filter Block

typedef struct {
    //DM_WIFI_DeM_Filter_t DM_WIFI_DeM_Filter;
    //DM_WIFI_CM_Filter_t  DM_WIFI_CM_Filter;
    DM_WIFI_DSM_Filter_t DM_WIFI_DSM_Filter;
}DM_WIFI_VITA_Filter_t;



//! BLE Filter Block
typedef  enum {
    VITA_DM_BLE_SCAN_SUCESS,
    VITA_DM_BLE_SCAN_FAIL,
    VITA_DM_BLE_SCAN_STORE_FAIL,
    VITA_DM_BLE_SCAN_NO_DEVICE_FOUND,
    VITA_DM_BLE_SCAN_ABORTED,
    VITA_DM_BLE_SCAN_PROGRESS
}DM_BLE_SCAN_RESPONCE_e; //! Type of BLE scan status

typedef struct {

} DM_BLE_DeM_Filter_t;

typedef struct {

} DM_BLE_CM_Filter_t;

typedef struct {
    int bIncludeBleName;
    int bIncludeBleDeviceID;
    int bIncludeBleClass;
} DM_BLE_DSM_Filter_t;
//! BLE Filter Block

typedef struct {
    //DM_BT_DeM_Filter_t DM_BLE_DeM_Filter;
    //DM_BT_CM_Filter_t  DM_BLE_CM_Filter;
    DM_BLE_DSM_Filter_t DM_BLE_DSM_Filter;
}DM_BLE_VITA_Filter_t;


typedef struct {
    char DeviceId[DM_DEVICEID_SIZE];
    char SM_URL[DM_SM_URL_SIZE];
    DM_BT_VITA_Filter_t BT_VITA_Filter;
    DM_WIFI_VITA_Filter_t WIFI_VITA_Filter;
    DM_BLE_VITA_Filter_t BLE_VITA_Filter;

}DM_Init_Info_t;

typedef struct {
    char cmd[MAX_SCAN_CMD_SIZE];
    VITA_DM_DEVICETYPE_e deviceType;
    VITA_SCAN_Type scanType;
}DM_Scan_cmd_data;

typedef Scanning_State_e Scan_state_t;
typedef char* DM_Open_Info_t;

uint32_t VITA_DM_Init(void);
uint32_t VITA_DM_Init_EXT(DM_Init_Info_t Init_info, char url[]);
uint32_t VITA_DM_Open(DM_Open_Info_t Open_info);
uint32_t VITA_DM_Scan(uint32_t Handle, DM_Scan_cmd_data scanData);
void VITA_DM_Abort(DM_Scan_cmd_data scanData);
#ifdef IS_MQTT_ENABLED
void VITA_DM_SendResponse(char response[]);
#endif
char* VITA_DM_getTimeStamp(VITA_DM_DEVICETYPE_e scanType);

//!CURL Post data

struct curl_fetch_st {
    char *payload;
    size_t size;
};

size_t curl_callback (void *contents, size_t size, size_t nmemb, void *userp);
CURLcode curl_fetch_url(CURL *ch, const char *url, struct curl_fetch_st *fetch);
uint32_t VITA_DM_sendData(json_object *jsonStr, char *url);


//!IOTVITY
//void onFoundResource(Resource_info1 *);
//void DM_onGet(handle_t , json_object*);
//void DM_onObserve(handle_t, json_object* global_json);

uint32_t VITA_DM_Init_ext(DM_Init_Info_t Init_info, char url[]);
//uint32_t VITA_DM_Init(void);
uint32_t VITA_DM_Discover(disc_ptr);
//void onFoundResource(Resource_info*);
void DM_onObserve(handle_t, json_object*);
void DM_onGet(handle_t, json_object*);
void VITA_DM_Get(const char*, onGet_ptr);
void VITA_DM_Put(const char *, json_object*);




//!

#ifdef __cplusplus
}
#endif
#endif
#endif //VITA_DM_H
