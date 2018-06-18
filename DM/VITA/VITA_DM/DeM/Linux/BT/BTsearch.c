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
#include "BTsearch.h"
#include "helper.h"
/* TODO: Implement the Class details of BT */
static int8_t *major_classes[] = {"Miscellaneous",
                                  "Computer",
                                  "Phone",
                                  "LAN Access",
                                  "Audio/Video",
                                  "Peripheral",
                                  "Imaging",
                                  "Uncategorized"};

int32_t bt_rsp_devices = 0;
/*************************************************************************************************************************
 **************************************************************************************************************************
 * NAME                  :   DM_Wifi_Scan(DM_WIFI_ScanResult_Info_t *resultData)
 *
 * DESCRIPTION           :   Linux Bluetooth Scan API which triggers the hci scan api and gets the result
 *
 * INPUTS                :
 *                           INPUT PARAMETERS:
 *
 *                                           NAME :   	TYPE :
 *                                           DESC :
 *
 *                           OUTPUT PARAMETERS:
 *
 *                                           NAME :  resultData 	TYPE : DM_WIFI_ScanResult_Info_t
 *                                           DESC :  returns bluetooth scan result data with, properties i.e name, mac addr etc
 *
 *                                           NAME : result  	TYPE : int
 *                                           DESC : buetooth scan results
 **************************************************************************************************************************
 **************************************************************************************************************************/

int32_t DM_BT_Scan(DM_BT_ScanResult_Info_t *resultData){
    inquiry_info *ii = NULL;
    int32_t max_rsp;
    int32_t dev_id;
    int32_t sock;
    int32_t len;
    int32_t flags;
    int32_t i;
    int8_t addr[19] = { 0 };
    int8_t name[248] = { 0 };
    dev_id = hci_get_route(NULL);
    sock = hci_open_dev(dev_id);
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        return -1;
    }
    len = 8;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
    bt_rsp_devices = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if (bt_rsp_devices < 0) {
        perror("hci_inquiry");
        free(ii);
        close(sock);
        return -1;
    }
    else if(bt_rsp_devices == 0) {
        LOG_PRINT("No devices found\n");
        return 0;
    }
    for (i = 0; i < bt_rsp_devices; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name),
                                 name, 0) < 0) {
            strcpy(name, "[unknown]");
        }
        memcpy(resultData[i].bt_name, name, strlen(name));
        memcpy(resultData[i].bt_addr, addr, strlen(addr));
        resultData[i].bt_class = (*(ii+i)->dev_class+0);
    }
    resultData[0].num_elements = bt_rsp_devices;
    free(ii);
    close(sock);
    return resultData[0].num_elements;
}
#endif
/*****************************************************************************
 * NOTES:
 *
 *
 *
 *
 */
