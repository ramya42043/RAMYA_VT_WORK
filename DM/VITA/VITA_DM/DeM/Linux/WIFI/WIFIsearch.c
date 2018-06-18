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
#include <string.h>
#define implement 0
#if implement
#include <iwlib.h>  //!Header for IWLIB interface
#include "WIFIsearch.h"
#include "helper.h"
/*************************************************************************************************************************
 **************************************************************************************************************************
 * NAME                  :   DM_Wifi_Scan(DM_WIFI_ScanResult_Info_t *resultData)
 *
 * DESCRIPTION           :   Linux Wifi Scan API which triggers the iwlib scan api and gets the result
 *
 * INPUTS                :
 *                           INPUT PARAMETERS:
 *
 *                                           NAME :   	TYPE :
 *                                           DESC :
 *
 *                                           NAME :   	TYPE :
 *                                           DESC :
 *
 *                           OUTPUT PARAMETERS:
 *
 *                                           NAME :  resultData 	TYPE : DM_WIFI_ScanResult_Info_t
 *                                           DESC :  returns wifi scan result data with, properties i.e name, mac addr, ssid etc
 **************************************************************************************************************************
 **************************************************************************************************************************/
int32_t DM_Wifi_Scan(DM_WIFI_ScanResult_Info_t *resultData) {
    wireless_scan_head head;
    wireless_scan *result;
    iwrange range;
    uint8_t *mac = NULL;
    int32_t index = 0;	int sock;
    /* Open socket to kernel */
    sock = iw_sockets_open();
    if(sock <= 0) {
        return -1;
    }
    if (iw_get_range_info(sock, "wlan0", &range) < 0) {
        LOG_PRINT("Error during iw_get_range_info. Aborting.\n");
        return -1;
    }
    /* Perform the scan */
    if (iw_scan(sock, "wlan0", range.we_version_compiled, &head) < 0) {
        LOG_PRINT("Error during iw_scan. Aborting.\n");
        return -1;
    } 
    /* Traverse the results */
    result = head.result;
    while (NULL != result) {
        if ((result->b.essid) == NULL) {
            memcpy(resultData[index].wifi_device_names,
                   "[unknown]",
                   strlen("[unknown]"));
        }
        else {
            memcpy(resultData[index].wifi_device_names,
                   result->b.essid,
                   strlen(result->b.essid));
        }
        /*typecasting the value to signed int, so that the result is in dBm*/
        resultData[index].strength = (int8_t)result->stats.qual.level;
        mac = (unsigned char *)result->ap_addr.sa_data;
        snprintf(resultData[index].macAddr, 30,
                 "%02x:%02x:%02x:%02x:%02x:%02x",
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        /*Truncating of float value and limit 3 digits*/
        sprintf(resultData[index].frequency, "%0.3f",
                (result->b.freq)/1000000000);
        //!Debug the search results
        /*LOG_PRINT("[%d]Name: %s\n", index, resultData[index].wifi_device_names);
        LOG_PRINT("[%d]Strength: %d\n", index, resultData[index].strength);
        LOG_PRINT("[%d]MAC: %s\n", index, resultData[index].macAddr);
        LOG_PRINT("[%d]Frequency: %s\n", index, resultData[index].frequency);
        display mac address
        LOG_PRINT("Mac : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n" ,
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);*/
        index++;  
        result = result->next;
    }  
    (resultData+0)->num_elements = index;  
    return index;
}
#endif
/*****************************************************************************
 * NOTES:
 *
 *
 *
 *
 */
