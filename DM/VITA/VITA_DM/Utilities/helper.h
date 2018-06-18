#ifndef HELPER_H
#define HELPER_H

#include "VITA_DM.h"
#include "../Source/json/json_helper.h"

#ifdef __cplusplus
extern "C" {
#endif

int8_t *VITA_helper_macaddr(VITA_DM_DEVICETYPE_e deviceType);
void checkInternetConnection(void);
const int8_t *parseResponseObj(json_object *json);

void test_log();
void log_print(int8_t* filename, int32_t line, int8_t *fmt,...);
int8_t* print_time();

#define LOG_PRINT(...) log_print(__FILE__, __LINE__, __VA_ARGS__ )

#ifdef __cplusplus
}
#endif

#endif //!HELPER_H
