#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include "setexdata.h"
#include "DatahubEdge.h"
#include "connectConfig.h"

#define RELEASE true // true or false means exe different so file
#define THREADCOUNT 9
pthread_t thread_id[THREADCOUNT];

/* create a sleep function used for demo */
int nsleep(long miliseconds);

void getSetexData(int devicenum);
void sendSetexData(int devicenum);

bool IsConnected = false;
/* create event callback */
void edgeAgent_Connected()
{
    printf("Connect success\n");
    IsConnected = true;
}

void edgeAgent_Disconnected()
{
    printf("Disconnected\n");
    IsConnected = false;
}

void edgeAgent_Recieve(char *cmd, char *val)
{

    if (strcmp(cmd, WirteValueCommand) == 0)
    {
        printf("write value: %s\n", val);
    }
    else if (strcmp(cmd, WriteConfigCommand) == 0)
    {
        printf("write config: %s\n", val);
    }
}

void threadS(int threadId,void *function,int devicenum){
    if(pthread_create( &thread_id[threadId], NULL,function, (void*)devicenum) != 0){
        printf("Create thread err!\n");
    }
    return;
}


int main(int argc, char *argv[])
{   

    initConnectInfo();
    char *text_tagArr[20] = {"getInfoWord", "getInfoDoubleWord","getInfoBit", "getFunctionInitMarker", 
    "getFunctionActivationMarker", "getFunctionQuitMarker", "getValueParameter", 
    "getActualValueParameter", "getAlarms", "getAlarms2", "getControlMarker",
    "getControlWords", "getControllerParameter", "getTimers", "getMachineConstant",
    "getBatchParameter","getBatchParameterDS737","getBatchParameterNextBatch",
    "getMaintenanceCounter","getActionButtons"};


    /*  load library */
    void (*SetConnectEvent)();
    void (*SetDisconnectEvent)();
    void (*SetMessageReceived)();
    void (*Constructor)(TOPTION_STRUCT);
    void (*Connect)();
    void (*Disconnect)();
    int (*UploadConfig)(ActionType, TNODE_CONFIG_STRUCT);
    int (*SendData)(TEDGE_DATA_STRUCT);
    int (*SendDeviceStatus)(TEDGE_DEVICE_STATUS_STRUCT);

    void *handle;
    if (RELEASE)
    {
        handle = dlopen("./WISEPaaS.Datahub.Edge.so", RTLD_LAZY);
    }
    else
    {
        handle = dlopen("./DatahubEdge.so.1.0.2", RTLD_LAZY);
    }

    if (!handle)
    {
        fputs(dlerror(), stderr);
        exit(1);
    }
  
    SetConnectEvent = dlsym(handle, "SetConnectEvent");
    SetDisconnectEvent = dlsym(handle, "SetDisconnectEvent");
    SetMessageReceived = dlsym(handle, "SetMessageReceived");

    Constructor = dlsym(handle, "Constructor");
    Connect = dlsym(handle, "Connect");
    Disconnect = dlsym(handle, "Disconnect");
    UploadConfig = dlsym(handle, "UploadConfig");
    SendData = dlsym(handle, "SendData");
    SendDeviceStatus = dlsym(handle, "SendDeviceStatus");

    /*  Set Event */
    SetConnectEvent(edgeAgent_Connected);
    SetDisconnectEvent(edgeAgent_Disconnected);
    SetMessageReceived(edgeAgent_Recieve);

    /*  Set Construct */
    TOPTION_STRUCT options;
    options.AutoReconnect = true;
    options.ReconnectInterval = 1000;
    options.NodeId = connectInfo.nodeId; // your node Id
    options.Heartbeat = 60;
    options.DataRecover = true;
    options.ConnectType = DCCS; // set your connect type: DCCS or MQTT
    options.Type = Gatway;
    options.UseSecure = false;
    options.OvpnPath = "";

    switch (options.ConnectType)
    {
    case 1:                                                              // DCCS
        options.DCCS.CredentialKey = connectInfo.credentialKey; // your CredentialKey
        options.DCCS.APIUrl = "https://api-dccs-ensaas.hz.wise-paas.com.cn/";
        break;

    case 0: // MQTT
        options.MQTT.HostName = "YOUR_MQTT_HOST";
        options.MQTT.Port = 1883;
        options.MQTT.Username = "admin";
        options.MQTT.Password = "admin";
        options.MQTT.ProtocolType = TCP;
        break;
    }

    /*  Set Config */
    TNODE_CONFIG_STRUCT config;
    ActionType action = Create;

    config.Id = options.NodeId;
    config.Description = "";
    config.Name = "";
    config.Type = 1;

    char *mydeviceName = connectInfo.deviceInfo->Name;
    int device_num = connectInfo.deviceCount; //differt from devicenum
    int text_tag_num = 20;

    PTDEVICE_CONFIG_STRUCT device = malloc(device_num * sizeof(struct DEVICE_CONFIG_STRUCT));
    PTTEXT_TAG_CONFIG textTag = malloc(text_tag_num * sizeof(struct TEXT_TAG_CONFIG));

    char *TagName = NULL;
    char *DevId = NULL;
    char *DevName = NULL;
    char *Value = NULL;

    for(int i=0;i<device_num; i++){
        for(int j=0;j<text_tag_num; j++){
               
            textTag[j].Name = text_tagArr[j];
            textTag[j].Description = "";
            textTag[j].ReadOnly = false;
            textTag[j].ArraySize = 0;
            textTag[j].AlarmStatus = false; 
        }
        device[i].Id = (connectInfo.deviceInfo + i)->Name;
        device[i].Name = (connectInfo.deviceInfo + i)->Name;
        device[i].Type = "";
        device[i].Description = "";
        //device[i].RetentionPolicyName = "";
        device[i].TextNumber = text_tag_num;
        device[i].TextTagList = textTag;
    }
    config.DeviceNumber = device_num;
    config.DeviceList = device;

    /* Set Device Status */
    TEDGE_DEVICE_STATUS_STRUCT status;
    status.DeviceNumber = device_num;

    PTDEVICE_LIST_STRUCT dev_list = malloc(device_num * sizeof(struct DEVICE_LIST_STRUCT));

    for(int i=0; i < device_num; i++){
        dev_list[i].Id = (connectInfo.deviceInfo + i)->Name;
        dev_list[i].Status = 1;
    }
    status.DeviceList = dev_list;

    /* Set Data Content */
    TEDGE_DATA_STRUCT data;
    PTEDGE_DEVICE_STRUCT data_device = malloc(device_num * sizeof(struct EDGE_DEVICE_STRUCT));
    PTEDGE_TEXT_TAG_STRUCT text_data_tag = malloc(text_tag_num * sizeof(struct EDGE_TEXT_TAG_STRUCT));

    /* Use SDK API */
    Constructor(options);
    Connect();

    nsleep(2000);

    UploadConfig(action, config);
    SendDeviceStatus(status);
    while (1)
    {
        nsleep(1000); // send simulation per sec
        int devicenum = 0;
        for(devicenum; devicenum < connectInfo.deviceCount; devicenum++){
            // initDevice(devicenum);  

            int count = 1000;    
            int len = count*sizeof(unsigned) + count + (2 + 1)*2 + 1;
            functionActivationMarker[devicenum]= malloc(len);
            memset(functionActivationMarker[devicenum], '\0', len);

            
            threadS(1,getValueParameterData, devicenum);
            threadS(2,getActualValueParameterData, devicenum);
            threadS(3,getAlarmsData, devicenum);
            threadS(4,getInfoBitData, devicenum);
            threadS(5,getInfoWordData, devicenum);
            threadS(6,getInfoDoubleWordData, devicenum);
            threadS(7,getBatchParameterData, devicenum);   
            threadS(0,getFunctionActivationMarkerDataStat, devicenum);      
            threadS(8,getFunctionActivationMarkerDataEnd, devicenum);       

            pthread_join(thread_id[0], NULL);
            pthread_join(thread_id[1], NULL);
            pthread_join(thread_id[2], NULL);
            pthread_join(thread_id[3], NULL);
            pthread_join(thread_id[4], NULL);
            pthread_join(thread_id[5], NULL);
            pthread_join(thread_id[6], NULL);
            pthread_join(thread_id[7], NULL); 
            pthread_join(thread_id[8], NULL); 
            strcat(functionActivationMarker[devicenum],FAS);
            strcat(functionActivationMarker[devicenum],FAE); 
            
            free(FAS);
            free(FAE);
        }
        for (int i = 0; i < device_num; i++)
        {
            (text_data_tag + 0)->Name = "getValueParameter";
            (text_data_tag + 0)->Value = valueParameter[i];

            (text_data_tag + 1)->Name = "getActualValueParameter";
            (text_data_tag + 1)->Value = actualValueParameter[i];

            (text_data_tag + 2)->Name = "getAlarms";
            (text_data_tag + 2)->Value = alarms[i];

            (text_data_tag + 3)->Name = "getInfoBit";
            (text_data_tag + 3)->Value = infoBitData[i];

            (text_data_tag + 4)->Name = "getInfoWord";
            (text_data_tag + 4)->Value = infoWordData[i];

            (text_data_tag + 5)->Name = "getInfoDoubleWord";
            (text_data_tag + 5)->Value = infoDoubleWordData[i];

            (text_data_tag + 6)->Name = "getBatchParameter";
            (text_data_tag + 6)->Value = batchParameter[i];

            (text_data_tag + 7)->Name = "getFunctionActivationMarker";
            (text_data_tag + 7)->Value = functionActivationMarker[i];

            data_device[i].TextTagNumber = 8;
            data_device[i].TextTagList = text_data_tag;
            data_device[i].Id = mydeviceName;
        }
        data.DeviceNumber = device_num;
        data.DeviceList = data_device;
        //data.Time = "2020-04-21T09:47:03.633Z";  //%Y-%m-%dT%H:%M:%S.MSZ
        int result_senddata = SendData(data);
        printf("%d\n", result_senddata);
        for(int i = 0; i < device_num; i++){
            // free(valueParameter[i]);
            // free(actualValueParameter[i]);
            // free(alarms[i]);
            // free(infoBitData[i]);
            // free(infoWordData[i]);
            // free(infoDoubleWordData[i]);
            // free(batchParameter[i]);
            // free(functionActivationMarker[i]);
        }
    }

    /* release */
    free(device);
    free(textTag);
    free(data_device);
    free(text_data_tag);
    free(dev_list);

    dlclose(handle);

    return 0;
}

/* create a sleep function used for demo */
int nsleep(long miliseconds)
{
    struct timespec req, rem;

    if (miliseconds > 999)
    {
        req.tv_sec = (int)(miliseconds / 1000);                            /* Must be Non-Negative */
        req.tv_nsec = (miliseconds - ((long)req.tv_sec * 1000)) * 1000000; /* Must be in range of 0 to 999999999 */
    }
    else
    {
        req.tv_sec = 0;                      /* Must be Non-Negative */
        req.tv_nsec = miliseconds * 1000000; /* Must be in range of 0 to 999999999 */
    }
    return nanosleep(&req, &rem);
}

void getSetexData(int devicenum){
  
}

void sendSetexData(int devicenum){


}

