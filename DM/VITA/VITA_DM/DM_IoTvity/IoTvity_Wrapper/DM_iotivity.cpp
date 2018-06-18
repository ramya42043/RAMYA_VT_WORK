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
#include "DM_iotivity.h"
#include <mutex>
#include <condition_variable>
#include "iotivity_config.h"
#include <string>
#include <map>
#include <cstdlib>
#include <mutex>
#include "OCPlatform.h"
#include "OCApi.h"
#include <iostream>
#include <OCRepresentation.h>
#include <memory>
#include <vector>
using namespace std;
using namespace OC;

typedef struct RESOURCE {
    char uri[30];
    onGet_ptr onget_instance;
    onPut_ptr onput_instance;
    onobserve_ptr onobserve_instance;
    onDelete_ptr onDelete_instance;
    device_status_t status;
    std::shared_ptr<OCResource> DM_Resource;
    struct RESOURCE *next;
}Resource_list;

std::mutex dm_blocker;
Resource_list *resource_head = NULL;
disc_ptr global_call_back;

std::mutex DM_LOCK_new;
std::condition_variable dm_cv;
std::unique_lock<std::mutex>dm_lock_new(DM_LOCK_new);

string type_detection = "oic/res";	/* fixed URI to found resources based on the resource type */

static ObserveType OBSERVE_TYPE_TO_USE = ObserveType::Observe;
onobserve_ptr global_on_call_back =NULL;
handle_t obs_h;
handle_t h;
handle_t forCallback;
handle_t callBack_handle;
OCStackResult check_delete;

/* ****************************************************
 * PROTOTYPES
 *
 */
typedef void (*onDelete_ptr)(handle_t);

void DM_Delete(handle_t, onDelete_ptr);

int32_t dm_init(int32_t );

void found_resource(std::shared_ptr<OCResource> );

void DM_Discovery(disc_ptr);

void on_Get(const HeaderOptions& , const OCRepresentation& , const int32_t );

void DM_Get(handle_t , onGet_ptr );

void onPut(const HeaderOptions& , const OCRepresentation& , const int );

void DM_Put(handle_t ,json_object* );

void onObserve(const HeaderOptions& , const OCRepresentation& ,const int& , const int& );

void DM_observe(handle_t , onobserve_ptr, int32_t);

void DM_Terminate(void);

void terminateListofDevices(void);

//............................................................................
int32_t dm_init(int32_t mode_type) {
    try {
        ModeType mode_new;
        if(mode_type == 0) {
            mode_new = OC::ModeType::Server;
        }
        else if(mode_type == 1) {
            mode_new = OC::ModeType::Client;
        }
        else if(mode_type == 2) {
            mode_new = OC::ModeType::Both;
        }
        PlatformConfig cfg {OC::ServiceType::InProc, mode_new, "0.0.0.0", 0,
                    OC::QualityOfService::HighQos};
        OCPlatform::Configure(cfg);
        std::cout<<"client is intialized with mode type as client"<<std::endl;
        return 0;
    }
    catch(OCException& e) {
        oclog()<<"Exception in main: "<<e.what();
        return 1;
    }
    return 0;
}//dm_init function

//.............................discover api...................................
void found_resource(std::shared_ptr<OCResource> resource) {
    std::string resourceURI;
    std::string resourceID;

    Resource_list *temp = NULL;
    Resource_list *local = NULL;
    dm_blocker.lock();
    if (resource) {
        resourceURI = resource->uri();
        if(resourceURI.compare("/oic/d")==0
                ||resourceURI.compare("/oic/p")==0
                ||resourceURI.compare("/oic/sec/doxm")==0
                ||resourceURI.compare("/oic/sec/pstat")==0){
            //printf("********* if condition URI NAME IS----%s---------->\n",resourceURI.c_str());
            dm_blocker.unlock();
            return;
        }
        resourceID = string(resource->sid());
        temp = resource_head;

        local = (Resource_list *)malloc(sizeof(Resource_list));
        memset(local, 0, sizeof(Resource_list));
        if(local == NULL)
        {
            printf("Failed to allocate memory\n");
            return;
         }
        strcpy(reinterpret_cast<char *>(local->uri), (resource->uri()).c_str());
        local->onget_instance = NULL;
        local->onput_instance = NULL;
        local->onobserve_instance = NULL;
        local->DM_Resource = resource;
        if (resource_head == NULL) {
            local->next = resource_head;
            resource_head = local;
        }
        else {
            local->next = NULL;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = local;
        }
        Resource_info *local_info = (Resource_info*)malloc(sizeof(Resource_info));
        void* conv = reinterpret_cast<void*>(local);
        local_info->handle = conv;
        strcpy(reinterpret_cast<char *>(local_info->name), (resource->uri()).c_str());
        global_call_back(local_info);
    }
    dm_blocker.unlock();
    return ;
}//found_resource
//............................................................................
void DM_Discovery(disc_ptr call_back) {

//    Resource_list * delete_temp = NULL;
//    while (resource_head != NULL)
//    {
//        delete_temp = resource_head;
//        delete_temp->DM_Resource.reset();
//        resource_head = resource_head->next;
//        free(delete_temp);
//    }

//    resource_head = NULL;
    global_call_back = call_back;
    std::ostringstream requestURI;
    requestURI << OC_RSRVD_WELL_KNOWN_URI;
    std::cout<<"Discovering Resources:"<<std::endl;
    OCPlatform::findResource("", requestURI.str(), CT_DEFAULT , &found_resource);
    std::cout <<"Waiting" << std::endl;
    dm_cv.wait_for(dm_lock_new, chrono::seconds(1));
    return ;
}///DM_Discovery

//........conversion from OCRepresentation to Json format....................
//............................................................................

void on_Get(const HeaderOptions& /*headerOptions*/,
            const OCRepresentation& rep,
            const int32_t eCode) {
    int32_t j = 0;
    json_object *local_json = json_object_new_object();
    map<std::string, AttributeValue> div;
    div = rep.getValues();
    std::string temp1,temp2;

    try {
        for (map<std::string, AttributeValue>::iterator i = div.begin();
             i != div.end(); i++) {
            temp1 = string(i->first);
            temp2 = (rep.getValueToString(temp1));
            if ((i->second).type() == typeid(int)) {
                json_object_object_add(local_json,
                                       temp1.c_str(),
                                       json_object_new_int(atoi(temp2.c_str())));
            }
            else if ((i->second).type() == typeid(string)) {
                json_object_object_add(local_json,
                                       temp1.c_str(),
                                       json_object_new_string(temp2.c_str()));
            }
            else if ((i->second).type() == typeid(bool)) {
                if (strcmp(temp2.c_str(),"true") == 0) {
                    j = 1;
                }
                else if(strcmp(temp2.c_str(),"false") == 0) {
                    j = 0;
                }
                json_object_object_add(local_json, temp1.c_str(),
                                       json_object_new_boolean(j));
            }
            else {
                //cout << "no value" << endl;
            }
            //cout << "Key: " << temp1 <<'\t'<< "Value :"<<temp2 <<endl;
        }//for
        reinterpret_cast<Resource_list*>(forCallback)->onget_instance(forCallback,local_json);
    }//try
    catch(std::exception& e) {
        cout << "Exception: " << e.what() << " in on_Get failed"<<endl;
    }
    return ;
}//on_Get

//............................................................................
void DM_Get(handle_t h, onGet_ptr call_back) {
    try {
        QueryParamsMap test;
        forCallback = h;
        reinterpret_cast<Resource_list*>(h)->onget_instance = call_back;
        reinterpret_cast<Resource_list*>(h)->status = GET_STATE;
        reinterpret_cast<Resource_list*>(h)->DM_Resource->get(test, &on_Get);
    }
    catch(std::exception& e) {
        cout << "Exception: " << e.what() << " in DM_get found failed" <<endl;
    }
    return ;
}//DM_Get

//////////////////////put/////////////////////////////////////////////
//............................................................................
void onPut(const HeaderOptions& /*headerOptions*/,
           const OCRepresentation& rep, const int32_t eCode) {
    return;
}//onPut
//............................................................................
void DM_Put(handle_t h, json_object* in_data) {
    try {
        QueryParamsMap test;
        OCRepresentation rep;
        string good;
        json_object_object_foreach(in_data, key, val) {
            switch(json_object_get_type(val)) {
            case json_type_int: {
                rep.setValue(key, json_object_get_int(val));
                break;
            }
            case json_type_string: {
                good = string(json_object_get_string(val));
                rep.setValue(key, good);
                break;
            }
            case json_type_boolean: {
                rep.setValue(key, json_object_get_boolean(val));
                break;
            }
            case json_type_double: {
                // cout << "double value:" << endl;
                break;
            }
            case json_type_object: {
                // cout << "object value" << endl;
                break;
            }
            case json_type_array: {
                // cout << "array value" << endl;
                break;
            }
            case json_type_null: {
                // cout << "Null value" << endl;
                break;
            }
            }
        }
        reinterpret_cast<Resource_list*>(h)->DM_Resource->put(rep,
                                                              test,
                                                              &onPut);
        reinterpret_cast<Resource_list*>(h)->status = PUT_STATE;
    }
    catch(std::exception& e) {
        cout << "Exception: " << e.what() << " in Put failed" <<endl;
    }
    return ;
}//DM_Put
//............................................................................
void onObserve(const HeaderOptions& /*headerOptions*/,
               const OCRepresentation& rep, const int32_t& eCode,
               const int32_t& sequenceNumber) {
    try {
        int32_t j = 0;
        json_object *local_json2 = json_object_new_object();
        Resource_list duplicate_list2;
        map<std::string, AttributeValue> div;
        div = rep.getValues();
        std::string temp1;
        std::string temp2;
        for (map<std::string, AttributeValue>::iterator i = div.begin();
             i != div.end(); i++, j++) {
            temp1 = string(i->first);
            temp2 = (rep.getValueToString(temp1));
            if ((i->second).type() == typeid(bool)) {
                if (strcmp(temp2.c_str(), "true") == 0) {
                    j=1;
                }
                else if (strcmp(temp2.c_str(), "false") == 0) {
                    j = 0;
                }
                json_object_object_add(local_json2, temp1.c_str(),
                                       json_object_new_boolean(j));
            }
            else if((i->second).type() == typeid(int)) {
                json_object_object_add(local_json2, temp1.c_str(),
                                       json_object_new_int(atoi(temp2.c_str())));
            }
            else if((i->second).type() == typeid(string)) {
                json_object_object_add(local_json2, temp1.c_str(),
                                       json_object_new_string(temp2.c_str()));
            }
            else {
                cout << "no value" << endl;
            }
        }//for
        strcpy(reinterpret_cast<char *>((duplicate_list2).uri),
               (char*)rep.getUri().c_str());
        Resource_list *temp = resource_head;
        while(temp != NULL) {
            if(strcmp(reinterpret_cast<char *>(duplicate_list2.uri),
                      reinterpret_cast<char *>(temp->uri)) == 0) {
                temp->onobserve_instance((handle_t)temp,local_json2);
            }
            temp = temp->next;
        }
    }
    catch(std::exception& e){
        cout << "Exception: " << e.what() << " in Put failed" <<endl;
    }
}
int32_t observe_flag = 1;
//............................................................................
void DM_observe(handle_t h, onobserve_ptr call_back, int32_t startStop) {
    global_on_call_back = call_back;
    obs_h = h;
    try{
        if (startStop == 0) {
            reinterpret_cast<Resource_list*>(h)->DM_Resource->observe(
                        OBSERVE_TYPE_TO_USE, QueryParamsMap(), &onObserve);
            reinterpret_cast<Resource_list*>(h)->onobserve_instance = call_back;
            reinterpret_cast<Resource_list*>(h)->status = OBSERVE_STATE;
            observe_flag = 0;//syncs connection for Read Task
        }
        else if (startStop == 1) {
            printf("Cancelling Observe...\n");
            reinterpret_cast<Resource_list*>(h)->DM_Resource->cancelObserve();
            reinterpret_cast<Resource_list*>(h)->status = IDLE_STATE;
            observe_flag = 1;
        }
    }
    catch(std::exception& e){
        cout << "Exception: " << e.what() << " in DM_observe failed" <<endl;
    }
    return ;
}//DM_observe
//............................................................................
handle_t global_handle,delete_handle;
void on_DeleteResource(const HeaderOptions&, const int32_t unused)
{
    Resource_list *local_head1 = resource_head;
    Resource_list *free_node = NULL;
    if(check_delete == OC_STACK_OK)
    {
        if(strcmp(reinterpret_cast<Resource_list*>(global_handle)->uri,local_head1->uri) == 0) //first node hit
        {
            if(local_head1->next != NULL){
                resource_head=local_head1->next;
            }
            else{
                resource_head = NULL;
                free(local_head1);
            }
            reinterpret_cast<Resource_list*>(global_handle)->onDelete_instance(delete_handle);
        }
        else
        {
            while(local_head1->next != NULL)
            {
                if(strcmp(reinterpret_cast<Resource_list*>(global_handle)->uri,local_head1->next->uri)==0)
                {
                    free_node=local_head1->next;
                    if(local_head1->next->next != NULL){
                        local_head1->next=local_head1->next->next;
                    }
                    else{
                        local_head1->next=NULL;
                    }
                    free(free_node);
                    reinterpret_cast<Resource_list*>(global_handle)->onDelete_instance(delete_handle);
                    break;
                }
                else
                    local_head1=local_head1->next;
            }
            //return;
        }
        reinterpret_cast<Resource_list*>(callBack_handle)->onDelete_instance(callBack_handle);
    }
    return;
}
//............................................................................
void DM_Delete(handle_t h, onDelete_ptr callback) {
    callBack_handle = h;
    try
    {
        global_handle = h;
        if (reinterpret_cast<Resource_list*>(h)->status == OBSERVE_STATE) {
            reinterpret_cast<Resource_list*>(h)->DM_Resource->cancelObserve();
            reinterpret_cast<Resource_list*>(h)->status = IDLE_STATE;
        }
        reinterpret_cast<Resource_list*>(h)->onDelete_instance = callback;
        check_delete =
                reinterpret_cast<Resource_list*>(h)->DM_Resource->deleteResource(&on_DeleteResource);
    }
    catch(std::exception& e)
    {
        cout << "Exception: " << e.what() << " in DM_get failed" <<endl;
        return ;
    }
    return;
}
//............................................................................
void DM_Terminate(void) {
    Resource_list *resource_duplicate = resource_head;
    Resource_list *temp = NULL;
    while(resource_duplicate != NULL) {
        temp = resource_duplicate;
        resource_duplicate = resource_duplicate->next;
        temp->DM_Resource.reset();
//        temp->onDelete_instance = NULL;
//        temp->onget_instance = NULL;
//        temp->onobserve_instance = NULL;
//        temp->onput_instance = NULL;
//        temp->status = -1;
//        memset(temp->uri, '\0', sizeof(temp->uri));
        free(temp);
    }
    resource_head = NULL;
    terminateListofDevices();
    terminateListofIOTDevices();
    terminateNonIotivityhandler();
}

//****************************************************************************
// NOTES:
//
//
//
//
//
