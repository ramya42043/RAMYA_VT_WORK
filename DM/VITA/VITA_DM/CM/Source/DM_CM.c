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
#include "../Headers/DM_CM.h"
/*...........................................................................*/
int32_t DM_CM_Get(const int8_t *handle, onGet_ptr callback){
    uint64_t ulHandle = 0;
    sscanf(handle, "%lx", &ulHandle);
    DM_Get((handle_t)ulHandle, callback);
    return 0;
}
/*...........................................................................*/
int32_t DM_CM_Put(const int8_t *handle, json_object *obj) {
    uint64_t ulHandle = 0;
    sscanf(handle, "%lx", &ulHandle);
    DM_Put((handle_t)ulHandle, obj);
    return 0;
}
/*...........................................................................*/
int32_t DM_CM_Observe(const int8_t *handle, onobserve_ptr callback, int32_t startStop) {
    int64_t ulHandle = 0;
    sscanf(handle, "%lx", &ulHandle);
    DM_observe((handle_t)ulHandle, callback, startStop);
    return 0;
}
/*****************************************************************************
 * NOTES:
 *
 *
 *
 *
 */
