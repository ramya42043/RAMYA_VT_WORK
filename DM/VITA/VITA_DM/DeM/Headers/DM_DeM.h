#include <stdio.h>
#include<stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdint.h>

#define MAX_NAME_SIZE 248

typedef void* handle_t;
typedef struct
{
    char name[40];
    handle_t handle;
}Resource_info;

typedef struct {
    int8_t name[MAX_NAME_SIZE];
    int8_t id[50];
    int32_t signal;
}DM_DeM_discover_Info_t;

typedef void (*disc_ptr)(Resource_info*);
typedef void (*onDelete_ptr)(handle_t);
int dm_init(int);
int32_t DM_DeM_Init(void);
int32_t DM_DeM_Discovery(disc_ptr);
void DM_Discovery(disc_ptr);
void DM_DeM_Delete(const int8_t*, onDelete_ptr);
void DM_Delete(handle_t, onDelete_ptr);
void DM_DeM_Terminate(void);
void DM_Terminate(void);
void statemachine(void);
