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
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <stdlib.h>
#include <stdio.h>
#include <json/json.h>


#include"json_helper.h"
#include "../raspberry_osio_client/raspberry_osio_client.h"
using namespace std;
RaspberryOSIOClient * client = 0;
void VITA_MQTT_PARSE_Data(char *str);
//#define IS_MQTT_ENABLED
#ifdef IS_MQTT_ENABLED
void VITA_DM_SendResponse(char *);
#endif


//#include "../../../../VITA_DM/DeM/DM_DeM.h"
//#include "../../../../VITA_DM/CM/DM_CM.h"
//#include "../../../../VITA_DM/DSM/DM_DSM.h"
#define implement 0
#if implement
#include "raspberry_osio_client.h"
#include "VITA_DM.h"
//#include "../../../VITA_DM/DeM/DM_DeM.h"
//#include "../../../VITA_DM/CM/DM_CM.h"
#include "../../../VITA_DM/DeM/Headers/VITA_DM_DeM.h"
#include "json_helper.h"
//#include "VITA_DM_DSM.h"

using namespace std;
RaspberryOSIOClient * client = 0;
#ifdef IS_MQTT_ENABLED
void VITA_DM_SendResponse(char );
#endif

/*..........................................................................*/
// !Handler for sending response
#ifdef IS_MQTT_ENABLED
void VITA_DM_SendResponse(char response[]) {
    client->publish("VITA/Store_Status",response);
}
#endif
/*..........................................................................*/
size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct curl_fetch_st *p = (struct curl_fetch_st *) userp;
    p->payload = (char *) realloc(p->payload, p->size + realsize + 1);
    if (p->payload == NULL) {
        fprintf(stderr, "ERROR: Failed to expand buffer in curl_callback\n");
        free(p->payload);
        return -1;
    }
    memcpy(&(p->payload[p->size]), contents, realsize);
    p->size += realsize;
    p->payload[p->size] = 0;
    return realsize;
}
/*..........................................................................*/
CURLcode curl_fetch_url(CURL *ch,
                        const char *url,
                        struct curl_fetch_st *fetch) {
    CURLcode rcode;
    fetch->payload = (char *) calloc(1, sizeof(fetch->payload));
    if (fetch->payload == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate payload in curl_fetch_url\n");
        return CURLE_FAILED_INIT;
    }
    fetch->size = 0;
    curl_easy_setopt(ch, CURLOPT_URL, url);
    curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, curl_callback);
    curl_easy_setopt(ch, CURLOPT_WRITEDATA, (void *) fetch);
    curl_easy_setopt(ch, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(ch, CURLOPT_TIMEOUT, 5);
    curl_easy_setopt(ch, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(ch, CURLOPT_MAXREDIRS, 1);
    rcode = curl_easy_perform(ch);
    return rcode;
}

/*************************************************************************************************************************
 **************************************************************************************************************************
 * NAME                  :   VITA_DM_sendData(json_object *jsonStr,char *url)
 *
 * DESCRIPTION           :   send wifi/bluetooth scan results json obj to SM
 *
 * INPUTS                :
 *                           INPUT PARAMETERS:
 *
 *                                           NAME : jsonStr 	TYPE : json_object
 *                                           DESC : contains wifi/bluetooth scan results of json object
 *
 *                           OUTPUT PARAMETERS:
 *
 *                                           NAME : result  	TYPE : int
 *                                           DESC : returns send operation results
 *
 **************************************************************************************************************************
 **************************************************************************************************************************/

uint32_t VITA_DM_sendData(json_object *jsonStr,char *url)
{

    CURL *ch;
    CURLcode rcode;
    struct curl_fetch_st curl_fetch;
    struct curl_fetch_st *cf = &curl_fetch;
    struct curl_slist *headers = NULL;
    json_object *json;
    enum json_tokener_error jerr = json_tokener_success;
    printf("URL %s\n\n",url);
    if ((ch = curl_easy_init()) == NULL) {
        fprintf(stderr, "ERROR: Failed to create curl handle in fetch_session\n");
        return 1;
    }
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(ch, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(ch, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(ch, CURLOPT_POSTFIELDS, json_object_to_json_string(jsonStr));
    /* fetch page and capture return code */
    rcode = curl_fetch_url(ch, url, cf);
    curl_easy_cleanup(ch);
    curl_slist_free_all(headers);
    json_object_put(jsonStr);
    if (rcode != CURLE_OK || cf->size < 1) {
        fprintf(stderr, "ERROR: Failed to fetch url (%s) - curl said: %s\n",
                url, curl_easy_strerror(rcode));
        return 2;
    }
    /* check payload */
    if (cf->payload != NULL) {
        jsonStr = json_tokener_parse_verbose(cf->payload, &jerr);
        free(cf->payload);
    }
    else {
        fprintf(stderr, "ERROR: Failed to populate payload\n");
        free(cf->payload);
        return 3;
    }
    /* check error */
    if (jerr != json_tokener_success) {
        fprintf(stderr, "ERROR: Failed to parse json string\n");
        json_object_put(jsonStr);
        return 4;
    }
    /* !data post operation*/
    printf("Parsed JSON: %s\n", json_object_to_json_string(jsonStr));
    /* exit */
    return 0;
}
/*..........................................................................*/
#endif
//!Handler for incoming messages
void onMessage(char* topic, char* payload, unsigned int length) {
    char* clearMessage = new char[length + 1];
    memset(clearMessage, 0, length + 1);
    memcpy(clearMessage, payload, length);
    std::cout << "Topic: " << topic << ", message: " << clearMessage << std::endl;
    //VITA_PARSE_Data(clearMessage);
    VITA_MQTT_PARSE_Data(clearMessage);

}
#ifdef IS_MQTT_ENABLED
void VITA_DM_SendResponse(char response[],int type) {
    printf("Received data %s\n",response);

    if(type == 1)
    {
        client->publish("VITA_DM/foundresource",response);
    }
    else if(type == 2)
    {
        client->publish("VITA_DM/getinfo",response);
    }
    else if(type == 3)
    {
        client->publish("VITA_DM/observeinfo",response);
    }
    else
    {
        printf("un expected type\n");
    }
}
#endif
/*..........................................................................*/
#if 0
int32_t main(void) {
    char *str = "{\"power\":88}";
    char str1[100] = {'\0'};
    json_object *jobj = json_tokener_parse(str);
    VITA_DM_Init();
#if 1
    VITA_DM_Discover(onFoundResource);
    printf("etner: ");
    scanf("%s",str1);
    VITA_DM_Get(str1, DM_onGet);
    VITA_DM_Put(str1, jobj);
    VITA_DM_Get(str1, DM_onGet);
#endif
    while(1);
    return 0;
}
#endif
/*********ramya*******/
int32_t main()
{
    client = new RaspberryOSIOClient("gizz", "88", "7E4ZHOQJ", onMessage);
    cout << "\n VITA Hellow Devices started. Waiting for commands..!" << endl;
    // Subscribe for topic.
    bool result = client->subscribe("VITA/Scan_Status96");
    // Main communication loop to process messages.
    do
    {
        // Save loop iteration state (TRUE if all ok).
        result = client->loop();
        // Just show that we are alive.
        cout << ".  ";
        // Wait 1 second.
        sleep(1);
    }while(result == true); // Break if loop returned FALSE.
    result = client->publish("VITA/Store_Status", "Stored");
    delete client;
    cout << "Bye!" << endl;
    return 0;
}

/*****************************************************************************
 * NOTES:
 *
 *
 *
 *
 */
