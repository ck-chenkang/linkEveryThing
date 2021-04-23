#include <stdio.h>
#include <stdlib.h>
#include "../../inc/cJSON.h"
/* 
{
    "nodeid": "a0ab655b-068a-42d1-97ff-6bcd6a91afd3",
    "credentialKey": "fb228cf66c2fdea54ff0d9a1fcbe65nb",
    "devices": {
        "count": "2",
        "connectInfo": 
        [
            {
                "name": "F01",
                "ip": "192.168.13.201"
            },
            {
                "name": "F02",
                "ip": "192.168.13.203"
            }
        ]
    }
}
*/
/* 
https://www.cnblogs.com/yeshenmeng/p/12714661.html
https://www.cnblogs.com/piaoyang/p/9274925.html
 */
int main(int argc, char **argv)
{

    FILE *f = fopen("connectConfig.json", "rb");
    if (f == NULL)
    {
        puts("open file failed");
        return -1;
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);
    puts(string);

    cJSON *root = NULL;
    cJSON *item = NULL;
    root = cJSON_Parse(string);
    printf("%s\n\n", cJSON_Print(root));

    item = cJSON_GetObjectItem(root, "devices"); //root 是使用 cjson对象
    printf("%s\n\n", cJSON_Print(item));

    item = cJSON_GetObjectItem(item, "connectInfo");
    printf("%s\n\n", cJSON_Print(item));
    // cJSON *object = cJSON_GetArrayItem(arrayItem,0);   //因为这个对象是个数组获取，且只有一个元素所以写下标为0获取
    if (NULL != item)
    {
        cJSON *client_list = item->child;
        while (client_list != NULL)
        {
            char *name = cJSON_GetObjectItem(client_list, "name")->valuestring;
            char *ip = cJSON_GetObjectItem(client_list, "ip")->valuestring;
            printf("name: %s  ip: %s\n", name, ip);
            client_list = client_list->next;
        }
    }
    free(string);
    return 0;
}