#include<stdio.h>
#include <stdint.h>
#include <json/json.h>
typedef void* handle_t;
typedef void (*onGet_ptr)(handle_t, json_object*);
typedef void (*onPut_ptr)(handle_t, json_object*);
typedef void (*onobserve_ptr)(handle_t, json_object*);

void DM_Get(handle_t, onGet_ptr);
void DM_onGet(handle_t, json_object*);
void DM_observe(handle_t , onobserve_ptr, int32_t);
void DM_Put(handle_t, json_object*);

int32_t DM_CM_Get(const int8_t *, onGet_ptr);
int32_t DM_CM_Put(const int8_t *, json_object *);
int32_t DM_CM_Observe(const int8_t *, onobserve_ptr, int32_t );
