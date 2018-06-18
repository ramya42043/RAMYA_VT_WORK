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
#include "../Headers/DM_DeM.h"
#define SERVER 0
#define CLIENT 1
#define SERVER_CLIENT 2
DM_DeM_discover_Info_t DeM_disc_info[100];
int32_t count = 0;
sem_t disc_sem;
pthread_t discovery_thread;

/*...........................................................................*/
int32_t DM_DeM_Init(void) {
    int32_t res;
    res = sem_init(&disc_sem, 0, 0);
    if (res != 0) {
        perror("Semaphore initialization failed");
        return -1;
    }
    res = pthread_create(&discovery_thread, NULL, (void *)statemachine, NULL);
    if (res != 0) {
        perror("IOTVITY Task creation failed");
        return -1;
    }
    if(dm_init(SERVER_CLIENT) != 0){
        printf("failed to initialize\n");
        exit(1);
    }
    count = 0;
    return 0;
}
/*...........................................................................*/
int32_t DM_DeM_Discovery(disc_ptr callback) {
    DM_Terminate();
    sleep(1);
    DM_Discovery(callback);
    sem_post(&disc_sem);
    return 0;
}
/*...........................................................................*/
void DM_DeM_Delete(const int8_t* handle, onDelete_ptr callback) {
    uint64_t ulHandle = 0;
    sscanf(handle, "%lx", &ulHandle);
    DM_Delete((handle_t)ulHandle, callback);
    return;
}

/*...........................................................................*/
void DM_DeM_Terminate(void) {
    printf("%s\n", __func__);
    DM_Terminate();
}

/*...........................................................................*/
void statemachine(void) {
   /*while(1)
   {
       sem_wait(&disc_sem);
       sleep(30);
       if(count != 0)
       {
           if(VITA_DM_DSM_IoTvity_Disc_Send(DeM_disc_info ,count))
           {
               printf("Failed to store IoTvity resource details at SM\n");
           }
           else
           {
               printf("IoTvity Resource details Stored at SM\n");
           }
       }
       else
       {
           printf("No Resource found\n");
       }
       count = 0;
    }*/
    return ;
}
/*****************************************************************************
 * NOTES:
 *
 *
 *
 *
 */

