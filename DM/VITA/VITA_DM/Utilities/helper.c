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
/*
 * Generic helper for DM Module
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <string.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netdb.h>
#include <time.h>

#define implement 0
#if implement
#include "helper.h"
int8_t *macaddr;
FILE *fp ;
static int32_t SESSION_TRACKER; /*Keeps track of session*/
int8_t *buf;
/*..........................................................................*/
int8_t *VITA_helper_macaddr(VITA_DM_DEVICETYPE_e deviceType) {
    printf("<%s:%d>START\n", __func__, __LINE__);
    macaddr = malloc(30);
    uint8_t *mac;
    int32_t fd, ctl;
    struct ifreq ifr;
    int8_t * wifi_iface = "wlan0";
    if(deviceType == DEVICE_BLUETOOTH) {
        struct hci_dev_info di;
        int8_t addr[18];
        if((ctl = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HCI)) < 0) {
            perror("Can't open HCI socket. \n");
            return NULL;
        }
        if(ioctl(ctl, HCIGETDEVINFO, (void*) &di)) {
            printf("<%s:%d>\n", __func__, __LINE__);
            return NULL;
        }
        ba2str(&di.bdaddr, addr);
        printf("BT ADDRESS:\n\t%s\t%s\n", di.name, addr);
        memcpy(macaddr, addr, strlen(addr));
    }
    else if(deviceType == DEVICE_WIFI) {
        fd = socket(AF_INET, SOCK_DGRAM, 0);
        ifr.ifr_addr.sa_family = AF_INET;
        strncpy(ifr.ifr_name , wifi_iface , IFNAMSIZ-1);
        ioctl(fd, SIOCGIFHWADDR, &ifr);
        close(fd);
        mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;
        snprintf(macaddr, 20, "%02x:%02x:%02x:%02x:%02x:%02x",
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        printf("WIFI MAC ADDRESS: %s\n", macaddr);
    }
    printf("<%s:%d>END\n", __func__, __LINE__);
    return macaddr;
}
/*..........................................................................*/
const int8_t *parseResponseObj(json_object *json) {
    json_object *returnObj;
    if (json_object_object_get_ex(json, "StatusCode", &returnObj)) {
        if(returnObj != NULL) {
            return json_object_to_json_string(returnObj);
        }
    }
    return NULL;
}
/*..........................................................................*/
void checkInternetConnection(void) {
    int8_t *hostname;
    struct hostent *hostinfo;
    hostname = "google.com";
    hostinfo = gethostbyname(hostname);
    if (hostinfo == NULL) {
        printf("-> no connection!\n");
    }
    else {
        printf("-> connection established!\n");
    }
    return ;
}
/*..........................................................................*/
/*
 * - Adding support for time logging in Utilities
 * - Test call
 * - Time stamp
 * - Logging
 */
/* ! Test Call*/
void test_log(void) {
    int32_t x = 199, i = 0;
    int8_t *s = "Bitter Truth";
    while(i < 5) {
        LOG_PRINT("Hello World ");
        LOG_PRINT("Zing is back !!! %s %d", s, x++);
        i++;
    }
    return ;
}
/*..........................................................................*/
/* ! Time Stamp*/
int8_t* print_time(void) {
    int32_t size = 0;
    time_t t;
    t = time(NULL); /* get current calendar time */
    int8_t *timestr = asctime(localtime(&t));
    timestr[strlen(timestr) - 1] = 0;  /*Getting rid of \n */
    size = strlen(timestr)+ 1 + 2; /*Additional +2 for square braces*/
    buf = (int8_t*)malloc(size);
    memset(buf, 0x0, size);
    snprintf(buf,size,"[%s]", timestr);
    return buf;
}
/*..........................................................................*/
//! Logging
void log_print(int8_t* filename, int32_t line, int8_t *fmt,...) {
    va_list list;
    int8_t *p, *r;
    int32_t e;
    /*if(SESSION_TRACKER > 0)
      fp = fopen("log.txt","a+");
    else
      fp = fopen("log.txt","w");*/
    fprintf(stdout,"%s ",print_time());
    fprintf(stdout,"<%s:%d> ",filename, line);
    va_start(list, fmt);
    for (p = fmt; *p; ++p) {
        if ( *p != '%' ) {/*If simple string*/
            fputc( *p,stdout );
        }
        else {
            switch (*++p) {
            /* string */
                case 's': {
                    r = va_arg(list, char *);
                    fprintf(stdout,"%s", r);
                    continue;
                }
                /* integer */
                case 'd': {
                    e = va_arg(list, int);
                    fprintf(stdout, "%d", e);
                    continue;
                }
                default:
                    fputc(*p, stdout);
            }
        }
    }
    va_end( list );
    fputc('\n', stdout );
    SESSION_TRACKER++;
    //fclose(fp);
}
#endif
/*****************************************************************************
 * NOTES:
 *
 *
 *
 *
 */
