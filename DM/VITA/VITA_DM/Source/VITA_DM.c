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
#include <stdbool.h>
#include <string.h>
#include "../Headers/VITA_DM.h"

DM_IoTvity_discover_Info_t iotvity_disc_info[100];
int32_t count = 0;

/*..........................................................................*/
uint32_t VITA_DM_Init(void) {
    DM_DeM_Init();
}
/*..........................................................................*/
void onFoundResource(Resource_info *node) {
    if(strcmp(node->name,"/oic/d")==0 || strcmp(node->name,"/oic/p") == 0
            || strcmp(node->name, "/oic/sec/doxm") == 0
            || strcmp(node->name, "/oic/sec/pstat") == 0) {
        return ;
    }
    printf("\n\n==========================================================================\n");
    printf("Resource name:\t%s\n", node->name);
    printf("Resource handle: %p\n", node->handle);
    printf("==========================================================================\n");
    /**********************modified E***************************/
    strcpy(iotvity_disc_info[count].name, node->name);
    strcpy(iotvity_disc_info[count].id, node->handle);
    iotvity_disc_info[count].signal = 1;
    /*printf("**************** data stored ******************\n");*/
    count++;
    return ;
}
/*..........................................................................*/
uint32_t VITA_DM_Discover(disc_ptr callback) {
    DM_DeM_Discovery(callback);
    return 0;
}
/*..........................................................................*/
int32_t VITA_DM_DSM_IotVity_Get_Data (const char *handle, json_object *obj) {
    printf("The json object created: %s\n", json_object_to_json_string(obj));
}
/*..........................................................................*/
int32_t VITA_DM_DSM_IotVity_Observe_Data (const char *handle, json_object *obj) {
    printf("The json object created: %s\n", json_object_to_json_string(obj));
}
/*..........................................................................*/
void DM_onGet(handle_t handle, json_object* rep_json) {
    printf("\t\t\t***resource attributes*** \n");
    printf("handle in app:%p\n", handle);
    VITA_DM_DSM_IotVity_Get_Data(handle, rep_json);
    return ;
}
/*..........................................................................*/
void DM_onObserve(handle_t handle,json_object* rep_json) {
    printf("\t\t\t***resource attributes*** \n");
    printf("handle in app:%p\n",handle);
    VITA_DM_DSM_IotVity_Observe_Data(handle, rep_json);
    return ;
}
void DM_onDelete(handle_t handle) {
    printf("ONDELETE called at app level\n");
    return ;
}

/*..........................................................................*/
void VITA_DM_Get(const char *handle, onGet_ptr callback) {
    DM_CM_Get(handle, callback);
}
/*..........................................................................*/
void VITA_DM_Put(const char *handle, json_object *obj) {
   // printf("VITA_DM_PUT\n");
    DM_CM_Put(handle, obj);

}
/*..........................................................................*/
void VITA_DM_Observe(const char *handle, onobserve_ptr callback, int32_t start_stop) {
    DM_CM_Observe(handle, callback, start_stop);
}
/*..........................................................................*/
void VITA_DM_Delete(const char *handle, onDelete_ptr callback) {
    DM_DeM_Delete(handle, callback);
    return ;
}

/*..........................................................................*/
void VITA_DM_Terminate(void) {
    DM_DeM_Terminate();
}

/*..........................................................................*/






































#define implement 0
#if implement
#include "VITA_DM.h"
#include "VITA_DM_INTERNAL.h"
#include "json_helper.h"
#include "helper.h"
#include <time.h>
#include <stdlib.h>
#include "DM_IoTvity_api.h"

/* ! URL Logic variables*/
char server_url[255] = {""};
char device_ID[255] = {""};
bool has_url = false;
bool has_device_ID = false;
char wifiScantimeStamp[35];
char btScantimeStamp[35];
char bleScantimeStamp[35];
DM_IoTvity_discover_Info_t iotvity_disc_info[100];
int32_t count = 0;
/*..........................................................................*/
#if 0
void onFoundResource(Resource_info1 *node) {
    if(strcmp(node->name,"/oic/d")==0 || strcmp(node->name,"/oic/p") == 0
            || strcmp(node->name, "/oic/sec/doxm") == 0
            || strcmp(node->name, "/oic/sec/pstat") == 0) {
        return 0;
    }
    printf("\n\n==========================================================================\n");
    printf("Resource name:\t%s\n", node->name);
    printf("Resource handle: %p\n", node->handle);
    printf("==========================================================================\n");
    /**********************modified E***************************/
    strcpy(iotvity_disc_info[count].name, node->name);
    strcpy(iotvity_disc_info[count].id, node->handle);
    iotvity_disc_info[count].signal = 1;
    /*printf("**************** data stored ******************\n");*/
    count++;
    return 0;
}
void DM_onGet(handle_t handle, json_object* rep_json) {
    printf("\t\t\t***resource attributes*** \n");
    printf("handle in app:%p\n", handle);
    VITA_DM_DSM_IotVity_Get_Data(handle, rep_json);
    return ;
}
void DM_onObserve(handle_t handle,json_object* rep_json){
    printf("\t\t\t***resource attributes*** \n");
    printf("handle in app:%p\n",handle);
    VITA_DM_DSM_IotVity_Observe_Data(handle, rep_json);
    return ;
}
#endif
/*************************************************************************************************************************
**************************************************************************************************************************
* NAME                  :   VITA_DM_Init_EXT(DM_Init_Info_t Init_info, char url[])
*
* DESCRIPTION           :   VITA_DM_Init api is used to pass init info i.e received Wifi & Bt params for CM, DSM, DEM, deviceID, sm_url from TL to DM layer
*
* INPUTS                :
*                           INPUT PARAMETERS:
*
*                                           NAME : Init_info 	TYPE : DM_Init_Info_t
*                                           DESC  : To get init info data
*
*                           OUTPUT PARAMETERS:
*
*                                           NAME : int 	TYPE : int
*                                           DESC  : to return a value
*
**************************************************************************************************************************
**************************************************************************************************************************/
#if 0
uint32_t VITA_DM_Init(void) {
    DM_DeM_Init();
}
#endif

uint32_t VITA_DM_Init_EXT(DM_Init_Info_t Init_info, char url[]) {
    DM_DeM_Init();
    if (VITA_DM_BT_Init() == 0) {
        VITA_DM_INIT_PostResponce(VITA_DM_INIT_SUCESS);
    }
    else {
        VITA_DM_INIT_PostResponce(VITA_DM_INIT_FAIL);
    }
    if(VITA_DM_WIFI_Init() == 0) {
        VITA_DM_INIT_PostResponce(VITA_DM_INIT_SUCESS);
    }
    else {
        VITA_DM_INIT_PostResponce(VITA_DM_INIT_FAIL);
    }
    if(VITA_DM_BLE_Init() == 0) {
        VITA_DM_INIT_PostResponce(VITA_DM_INIT_SUCESS);
    }
    else {
        VITA_DM_INIT_PostResponce(VITA_DM_INIT_FAIL);
    }
    if (strlen(url)) {
        has_url = true;
        strncpy(server_url, url, strlen(url));
        LOG_PRINT("len: %d\t URL:%s", (uint32_t)strlen(server_url), server_url);
    }
    else {
        LOG_PRINT("No URL provided");
    }
    if(Init_info.DeviceId){
        has_device_ID = true;
        strncpy(device_ID, Init_info.DeviceId, strlen(Init_info.DeviceId));
        LOG_PRINT("len: %d\t Dev ID:%s", (int)strlen(Init_info.DeviceId), device_ID);
    }
    return 0;
}
/*..........................................................................*/
uint32_t VITA_DM_Init_ext(DM_Init_Info_t Init_info, char url[])
{
    //    if(VITA_DM_BT_Init() == 0)
    //        VITA_DM_INIT_PostResponce(VITA_DM_INIT_SUCESS);
    //    else
    //        VITA_DM_INIT_PostResponce(VITA_DM_INIT_FAIL);

    //    if(VITA_DM_WIFI_Init() == 0)
    //        VITA_DM_INIT_PostResponce(VITA_DM_INIT_SUCESS);
    //    else
    //        VITA_DM_INIT_PostResponce(VITA_DM_INIT_FAIL);

    //    if(VITA_DM_BLE_Init() == 0)
    //        VITA_DM_INIT_PostResponce(VITA_DM_INIT_SUCESS);
    //    else
    //        VITA_DM_INIT_PostResponce(VITA_DM_INIT_FAIL);
    DM_DeM_Init();
    if (strlen(url)) {
        has_url = true;
        strncpy(server_url, url, strlen(url));
        LOG_PRINT("len: %d\t URL:%s", (int)strlen(server_url), server_url);
    }
    else {
        LOG_PRINT("No URL provided");
    }
    if (Init_info.DeviceId) {
        has_device_ID = true;
        strncpy(device_ID, Init_info.DeviceId, strlen(Init_info.DeviceId));
        LOG_PRINT("len: %d\t Dev ID:%s", (int)strlen(Init_info.DeviceId), device_ID);
    }
    return 0;
}

/*************************************************************************************************************************
 **************************************************************************************************************************
 * NAME                  :   VITA_DM_cleanup()
 *
 * DESCRIPTION           :   to free(memory) server_url value
 *
 * INPUTS                :
 *                           INPUT PARAMETERS:
 *
 *                                           NAME : nil 	TYPE :
 *                                           DESC  :
 *
 *                           OUTPUT PARAMETERS:
 *
 *                                           NAME : nil 	TYPE :
 *                                           DESC  :
 *
 **************************************************************************************************************************
 **************************************************************************************************************************/

void VITA_DM_cleanup() {
    return ;
}

/*************************************************************************************************************************
 **************************************************************************************************************************
 * NAME                  :   DM_GetSM_URL(char **url)
 *
 * DESCRIPTION           :   To Get server_url
 *
 * INPUTS                :
 *                           INPUT PARAMETERS:
 *
 *                                           NAME : nil  	TYPE :
 *                                           DESC  :
 *
 *                           OUTPUT PARAMETERS:
 *
 *                                           NAME : url 	TYPE : char
 *                                           DESC  : url parameter is returned with server url
 *
 *                                           NAME : int 	TYPE : int
 *                                           DESC  : to return a value
 **************************************************************************************************************************
 **************************************************************************************************************************/

uint32_t DM_GetSM_URL(int8_t **url) {
    if(has_url) {
        *url = server_url;
        LOG_PRINT("len: %d\t URL:%s", (uint32_t)strlen(server_url), server_url);
        return strlen(server_url);
    }
    return -1;
}

/*************************************************************************************************************************
 **************************************************************************************************************************
 * NAME                  :   DM_Get_Device_ID(char **deviceid)
 *
 * DESCRIPTION           :   To Get device_id
 *
 * INPUTS                :
 *                           INPUT PARAMETERS:
 *
 *                                           NAME : nil  	TYPE :
 *                                           DESC  :
 *
 *                           OUTPUT PARAMETERS:
 *
 *                                           NAME : deviceid 	TYPE : char
 *                                           DESC  : deviceid parameter is returned with  deviceid
 *
 *                                           NAME : int 	TYPE : int
 *                                           DESC  : to return a value
 **************************************************************************************************************************
 **************************************************************************************************************************/

uint32_t DM_Get_Device_ID(int8_t **deviceid) {
    if(has_device_ID) {
        *deviceid = device_ID;
        /*LOG_PRINT("len: %d\t Dev ID:%s", (int)strlen(device_ID), device_ID);*/
        return strlen(device_ID);
    }
    return -1;
}

/*************************************************************************************************************************
 **************************************************************************************************************************
 * NAME                  :   VITA_DM_Open(DM_Open_Info_t Open_info)
 *
 * DESCRIPTION           :
 *
 * INPUTS                :
 *                           INPUT PARAMETERS:
 *
 *                                           NAME : Open_info  	TYPE : DM_Open_Info_t
 *                                           DESC  :
 *
 *                           OUTPUT PARAMETERS:
 *
 *                                           NAME : int 	TYPE : int
 *                                           DESC  : to return a value
 **************************************************************************************************************************
 **************************************************************************************************************************/

uint32_t VITA_DM_Open(DM_Open_Info_t Open_info) {
    static uint32_t Handle=1;
    return Handle++;
}

/*************************************************************************************************************************
 **************************************************************************************************************************
 * NAME                  :   VITA_DM_Scan(int Handle, VITA_DM_ScanType_e scan_info)
 *
 * DESCRIPTION           :
 *
 * INPUTS                :
 *                           INPUT PARAMETERS:
 *
 *                                           NAME : scan_info  	TYPE : VITA_DM_ScanType_e
 *                                           DESC : to pass scan info data
 *
 *                                           NAME : Handle  	TYPE : int
 *                                           DESC :
 *
 *                           OUTPUT PARAMETERS:
 *
 *                                           NAME : int 	TYPE : int
 *                                           DESC : to return a value
 **************************************************************************************************************************
 **************************************************************************************************************************/
uint32_t VITA_DM_Scan(uint32_t Handle, DM_Scan_cmd_data scanData) {

    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long long millisecondsSinceEpoch =
            (unsigned long long)(tv.tv_sec) * 1000 +
            (unsigned long long)(tv.tv_usec) / 1000;
    char timeStamp[35];
    sprintf(timeStamp, "%llu", millisecondsSinceEpoch);
    if (scanData.deviceType == DEVICE_BLUETOOTH) {
        if (!VITA_DM_BT_Scan(scanData.scanType)) {
            strcpy(btScantimeStamp, timeStamp);
        }
    }
    else if(scanData.deviceType == DEVICE_WIFI) {
        if(!VITA_DM_WIFI_Scan(scanData.scanType)) {
            strcpy(wifiScantimeStamp, timeStamp);
        }
    }
    else if (scanData.deviceType == DEVICE_BLE) {
        if(!VITA_DM_BLE_Scan(scanData.scanType)) {
            strcpy(bleScantimeStamp, timeStamp);
        }
    }
    else if(scanData.deviceType == DEVICE_ALL) {
        if(!VITA_DM_BT_Scan(scanData.scanType)) {
            strcpy(btScantimeStamp, timeStamp);
        }
        if(!VITA_DM_WIFI_Scan(scanData.scanType)) {
            strcpy(wifiScantimeStamp, timeStamp);
        }
    }
    printf("BTTimestamp: %s\nBLETimeStamp: %s\nWIfiTimeStamp: %s\n\n",
                           btScantimeStamp, bleScantimeStamp, wifiScantimeStamp);

    return 0;
}
/*..........................................................................*/
#if 0
uint32_t VITA_DM_Discover(disc_ptr1 callback) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long long millisecondsSinceEpoch =
            (unsigned long long)(tv.tv_sec) * 1000 +
            (unsigned long long)(tv.tv_usec) / 1000;

    char timeStamp[35];
    sprintf(timeStamp, "%llu", millisecondsSinceEpoch);
    strcpy(wifiScantimeStamp, timeStamp);
    DM_IoTVity_Discovery(callback);

}
/*..........................................................................*/
void VITA_DM_Get(const char *handle, onGet_ptr callback) {
    DM_CM_Get(handle, callback);
}
/*..........................................................................*/
void VITA_DM_Put(const char *handle, json_object *obj) {
    printf("VITA_DM_PUT\n");
    DM_CM_Put(handle, obj);

}
/*..........................................................................*/
void VITA_DM_Observe(const char *handle, onobserve_ptr callback, int32_t start_stop) {
    DM_CM_Observe(handle, callback, start_stop);
}
#endif
/*..........................................................................*/
void VITA_DM_Abort(DM_Scan_cmd_data scanData) {
    if(scanData.deviceType == DEVICE_BLUETOOTH) {
        VITA_DM_BT_Abort();
    }
    else if(scanData.deviceType == DEVICE_WIFI) {
        VITA_DM_WIFI_Abort();
    }
    else if(scanData.deviceType == DEVICE_BLE) {
        VITA_DM_BLE_Abort();
    }
    else if(scanData.deviceType == DEVICE_ALL){
        VITA_DM_BT_Abort();
        VITA_DM_WIFI_Abort();
    }
}

/*************************************************************************************************************************
 **************************************************************************************************************************
 * NAME                  :   VITA_DM_BT_PostResponce(VITA_SCAN_Type scanType ,DM_BT_SCAN_RESPONCE_e bt_response)
 *
 * DESCRIPTION           :   To Send BT Scan Response to Smart App
 *
 * INPUTS                :
 *                           INPUT PARAMETERS:
 *
 *                                           NAME : scanType  	TYPE : VITA_DM_ScanType
 *                                           DESC : To indicate AUTO/MANUAL
 *
 *                                           NAME : bt_response  	TYPE : DM_BT_SCAN_RESPONCE_e
 *                                           DESC : enum for BT scan status i.e success/failure
 *
 *                           OUTPUT PARAMETERS:
 *
 *                                           NAME :  	TYPE :
 *                                           DESC :
 **************************************************************************************************************************
 **************************************************************************************************************************/

void VITA_DM_BT_PostResponce(VITA_SCAN_Type scanType, DM_BT_SCAN_RESPONCE_e bt_response) {
    VITA_DM_create_BT_response(scanType, bt_response);
}
/*..........................................................................*/
void VITA_DM_BLE_PostResponce(VITA_SCAN_Type scanType, DM_BLE_SCAN_RESPONCE_e ble_response) {
    VITA_DM_create_BLE_response(scanType, ble_response);
}
/*************************************************************************************************************************
 **************************************************************************************************************************
 * NAME                  :   VITA_DM_WiFi_PostResponce(VITA_SCAN_Type scanType ,DM_WIFI_SCAN_RESPONCE_e wifi_response)
 *
 * DESCRIPTION           :   To Send WiFi Scan Response to Smart App
 *
 * INPUTS                :
 *                           INPUT PARAMETERS:
 *
 *                                           NAME : scanType  	TYPE : VITA_SCAN_Type
 *                                           DESC : To indicate AUTO/MANUAL
 *
 *                                           NAME : bt_response  	TYPE : DM_WIFI_SCAN_RESPONCE_e
 *                                           DESC : enum for WiFi scan status i.e success/failure
 *
 *                           OUTPUT PARAMETERS:
 *
 *                                           NAME :  	TYPE :
 *                                           DESC :
 **************************************************************************************************************************
 **************************************************************************************************************************/

void VITA_DM_WiFi_PostResponce(VITA_SCAN_Type scanType, DM_WIFI_SCAN_RESPONCE_e wifi_response) {
    VITA_DM_create_WIFI_Response(scanType, wifi_response);
}
/*************************************************************************************************************************
 **************************************************************************************************************************
 * NAME                  :   VITA_DM_INIT_PostResponce (DM_INIT_RESPONCE_e init_response)
 *
 * DESCRIPTION           :   To Send INIT Response to Smart App
 *
 * INPUTS                :
 *                           INPUT PARAMETERS:
 *
 *                                           NAME : init_response  	TYPE : DM_INIT_RESPONCE_e
 *                                           DESC : To indicate AUTO/MANUAL
 *
 *                                           NAME : bt_response  	TYPE : DM_WIFI_SCAN_RESPONCE_e
 *                                           DESC : enum for init status response i.e success/failure
 *
 *                           OUTPUT PARAMETERS:
 *
 *                                           NAME :  	TYPE :
 *                                           DESC :
 **************************************************************************************************************************
 **************************************************************************************************************************/


void VITA_DM_INIT_PostResponce(DM_INIT_RESPONCE_e init_response) {
    VITA_DM_create_Init_response(init_response);
}
/*..........................................................................*/
char *VITA_DM_getTimeStamp(VITA_DM_DEVICETYPE_e scanType) {
    char timeStamp[35];
    if(scanType == DEVICE_BLUETOOTH) {
        return btScantimeStamp;
    }
    else if(scanType == DEVICE_WIFI) {
        return wifiScantimeStamp;
    }
    else if(scanType == DEVICE_BLE) {
        return bleScantimeStamp;
    }
    return timeStamp;
}
#endif
/*****************************************************************************
 * NOTES:
 *
 *
 *
 *
 */
