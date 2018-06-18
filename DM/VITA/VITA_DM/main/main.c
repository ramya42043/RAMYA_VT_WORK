#include<stdio.h>
#include "../Source/VITA_DM.h"
#include <json/json.h>
#include <unistd.h>

int main() {
	char *str = "{\"power\":88}";
    char str1[100] = {'\0'};
    json_object *jobj = json_tokener_parse(str);
    VITA_DM_Init();
#if 1
    VITA_DM_Discover(onFoundResource);
    printf("etner: ");
    scanf("%s",str1);
    VITA_DM_Get(str1, DM_onGet);
    sleep(1);
    VITA_DM_Put(str1, jobj);
    sleep(1);
    VITA_DM_Get(str1, DM_onGet);
    sleep(1);
    VITA_DM_Delete(str1, DM_onDelete);
    sleep(5);
    VITA_DM_Get(str1, DM_onGet);
    sleep(1);
#endif
    while(1);
	return 0;
}
