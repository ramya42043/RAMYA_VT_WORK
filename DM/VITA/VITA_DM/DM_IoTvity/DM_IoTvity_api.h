#if 0
typedef void (*disc_ptr)(Resource_info*);
typedef void (*onGet_ptr)(handle_t,json_object*);
typedef void (*onPut_ptr)(handle_t,json_object*);
typedef void (*onobserve_ptr)(handle_t,json_object*);

int DM_DeM_Init(void);
int DM_IoTVity_Discovery(disc_ptr);
int DM_CM_Get(const char *, onGet_ptr);
int DM_CM_Put(const char *handle,json_object *obj);
int DM_CM_Observe(const char *handle, onobserve_ptr, int32_t);
#endif


