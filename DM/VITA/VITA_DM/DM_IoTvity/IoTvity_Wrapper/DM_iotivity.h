#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
 #define EXTERNC extern "C"
 #else
 #define EXTERNC
 #endif

#include<stdlib.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif
#ifdef HAVE_WINDOWS_H
#include <Windows.h>
#endif
#include <json-c/json.h>

#include<stdio.h>

#include<stdint.h>

#define MAX_NUM_OF_ATR 40

typedef void* handle_t;
//User level structure
typedef void* handle_t;
typedef struct
{
    char name[40];
    handle_t handle;
}Resource_info;
//typedef void (*onGet_ptr)(json_object*);
//typedef void (*onPut_ptr)(json_object*);
//typedef void (*onobserve_ptr)(json_object*);
#if 1
typedef void (*disc_ptr)(Resource_info*);
typedef void (*onGet_ptr)(handle_t, json_object*);
typedef void (*onPut_ptr)(handle_t, json_object*);
typedef void (*onobserve_ptr)(handle_t, json_object*);

enum device_status{ IDLE_STATE, GET_STATE, PUT_STATE, OBSERVE_STATE};
typedef int device_status_t;

int dm_init(int);
void DM_Discovery(disc_ptr);
void DM_Get(handle_t, onGet_ptr);
void DM_observe(handle_t h, onobserve_ptr, int32_t);
typedef void (*onDelete_ptr)(handle_t);
void DM_Delete(handle_t handle, onDelete_ptr callback);
//void DM_Put(Resource_info*,json_object*,onPut_ptr);
void DM_Put(handle_t,json_object*);
void DM_Terminate(void);
void terminateListofDevices(void);
void terminateListofIOTDevices(void);
void terminateNonIotivityhandler(void);
void stopdiscovery(void);
#endif



//Application structure
/*typedef struct NODE
{
    Resource_info *res;
    NODE *next;
}OnNode;
*/
//extern typedef void (*disc_ptr)(Resource_info*);

#if 0
void DM_onPut(handle_t,json_object* global_json);
#endif


#if 0
void DM_onObserve(handle_t, json_object* global_json);
#endif




 #undef EXTERNC

#ifdef __cplusplus
}
#endif



