#include "connectConfig.h"

static void getJsonStr(){
    FILE *f = fopen("connectConfig.json", "rb");
    if (f == NULL)
    {
        puts("open connectConfig.json failed");
        return -1;
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    jsonStr = malloc(fsize + 1);
    fread(jsonStr, 1, fsize, f);
    fclose(f);
}

static void getNodeIdAndCredentialkey(){
    getJsonStr();
    root = cJSON_Parse(jsonStr);
    if (!root)
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
    }
    else
    {
        item = cJSON_GetObjectItem(root, "nodeid"); 
        connectInfo.nodeId = item->valuestring;

        item = cJSON_GetObjectItem(root, "credentialKey"); 
        connectInfo.credentialKey = item->valuestring;

        printf("%s\n", connectInfo.nodeId);
        printf("%s\n", connectInfo.credentialKey);

    }
}

static void getDevicesInfo(){    
    cJSON *countItem = NULL;
    cJSON *connectItem  = NULL;
    

    item = cJSON_GetObjectItem(root, "devices"); //root 是使用 cjson对象
    printf("%s\n\n", cJSON_Print(item));   

    countItem = cJSON_GetObjectItem(item, "count");
    connectInfo.deviceCount = countItem->valueint;

    struct deviceStruct *midDeviceStruct = malloc(sizeof *midDeviceStruct);//? i don't know if this will happen something unexpected
    printf("%d\n", sizeof *midDeviceStruct);
    connectInfo.deviceInfo = midDeviceStruct;

    connectItem = cJSON_GetObjectItem(item, "connectInfo");
    printf("%s\n\n", cJSON_Print(connectItem));

    int i = 0;
    if (NULL != connectItem)
    {
        cJSON *client_list = connectItem->child;        
        while (client_list != NULL)
        {
            if(i >= connectInfo.deviceCount){
                printf("err:device count is larger than device connectinfo!!\n");
                break;
            }
            char *name = cJSON_GetObjectItem(client_list, "name")->valuestring;
            char *ip = cJSON_GetObjectItem(client_list, "ip")->valuestring;
            printf("name: %s  ip: %s\n", name, ip);
            connectInfo.deviceInfo[i].Name = name;
            connectInfo.deviceInfo[i].Ip = ip;
            i++;
            client_list = client_list->next;
        }
        i = 0;
    }
}

void initConnectInfo(){
    getJsonStr();
    getNodeIdAndCredentialkey();
    getDevicesInfo();
    free(jsonStr);
}