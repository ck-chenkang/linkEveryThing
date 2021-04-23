#include "setexdata.h"
#include <pthread.h>
void initDevice(int devicenum, int tagindex)
{

    int ch[10] = {0, 1, 0, 0, 1, 0, 0, 1, 1, 1};
    const char *deviceip = (connectInfo.deviceInfo + devicenum)->Ip;
    puts(deviceip);
    int result = initialize(deviceip, devicenum, tagindex);
    getPictureLayers(ch, devicenum, tagindex);
    setPictureLayers(ch, devicenum, tagindex);
}
//1-200
void getInfoWordData(int devicenum)
{
    if (sockHandle[devicenum][getInfoWord_ENU] == 0)
    {
        initDevice(devicenum, getInfoWord_ENU);
    }
    int value = 0;
    int count = 199;
    int len = count * sizeof(int) + count + 2 + 1;
    infoWordData[devicenum] = malloc(len);
    memset(infoWordData[devicenum], '\0', len);
    strcat(infoWordData[devicenum], "{");
    for (int i = 1; i <= count; i++)
    {
        char s[10];
        getInfoWord(i, &value, devicenum, getInfoWord_ENU);
        if (i != count)
        {
            sprintf(s, "%d,", value);
        }
        else
        {
            sprintf(s, "%d", value);
        }
        strcat(infoWordData[devicenum], s);
        // printf("index: %d, value: %d\n", i, value);
    }
    strcat(infoWordData[devicenum], "}");
    printf("%s\n", infoWordData[devicenum]);
    return;
}

//1-20
void getInfoDoubleWordData(int devicenum)
{
    if (sockHandle[devicenum][getInfoDoubleWord_ENU] == 0)
    {
        initDevice(devicenum, getInfoDoubleWord_ENU);
    }
    unsigned value = 0;
    int count = 20;
    int len = count * sizeof(unsigned) + count + 2 + 1;

    infoDoubleWordData[devicenum] = malloc(len);
    memset(infoDoubleWordData[devicenum], '\0', len);
    strcat(infoDoubleWordData[devicenum], "{");
    for (int i = 1; i <= count; i++)
    {
        char s[10];
        getInfoDoubleWord(i, &value, devicenum, getInfoDoubleWord_ENU);
        if (i != count)
        {
            sprintf(s, "%d,", value);
        }
        else
        {
            sprintf(s, "%d", value);
        }
        strcat(infoDoubleWordData[devicenum], s);
        // printf("index: %d, value: %d\n", i, value);
    }
    strcat(infoDoubleWordData[devicenum], "}");
    printf("%s\n", infoDoubleWordData[devicenum]);
    return;
}

//1-100
void getInfoBitData(int devicenum)
{
    if (sockHandle[devicenum][getInfoBit_ENU] == 0)
    {
        initDevice(devicenum, getInfoBit_ENU);
    }

    int value = 0;
    int count = 100;
    int len = count * sizeof(unsigned) + count + 2 + 1;

    infoBitData[devicenum] = malloc(len);
    memset(infoBitData[devicenum], '\0', len);
    strcat(infoBitData[devicenum], "{");
    for (int i = 1; i <= count; i++)
    {
        char s[10];
        getInfoBit(i, &value, devicenum, getInfoBit_ENU);
        if (i != count)
        {
            sprintf(s, "%d,", value);
        }
        else
        {
            sprintf(s, "%d", value);
        }
        strcat(infoBitData[devicenum], s);
        // printf("index: %d, value: %d\n", i, value);
    }
    strcat(infoBitData[devicenum], "}");
    printf("%s\n", infoBitData[devicenum]);
    return;
}

//1-1000
/* void getFunctionInitMarkerData(int devicenum){
    initDevice(devicenum, 3);  
    int value = 0;
    int count = 1000;
    int len = count*sizeof(unsigned) + count + 2 + 1;

    functionInitMarker[devicenum]= malloc(len);
    memset(functionInitMarker[devicenum], '\0', len);
    strcat(functionInitMarker[devicenum], "{");
    for (int i = 1; i <= count; i++)
    {
        char s[10];       
        getFunctionInitMarker(i, &value, devicenum, 3);
        if(i != count){
            sprintf(s, "%d,", value);
        }
        else{
            sprintf(s, "%d", value);
        }
        strcat(functionInitMarker[devicenum],s);
        // printf("index: %d, value: %d\n", i, value);        
    }
    strcat(functionInitMarker[devicenum], "}");
    printf("%s\n", functionInitMarker[devicenum]);
    return;
} */

//1-500
void getFunctionActivationMarkerDataStat(int devicenum)
{
    if (sockHandle[devicenum][getFunctionActivationMarkerDataStat_ENU] == 0)
    {
        initDevice(devicenum, getFunctionActivationMarkerDataStat_ENU);
    }
    pthread_t thread1;
    pthread_t thread2;
    int value = 0;
    int count = 500;
    int len = count * sizeof(unsigned) + count + 2 + 1;

    FAS = malloc(len);
    memset(FAS, '\0', len);
    strcat(FAS, "{");
    for (int i = 1; i <= count; i++)
    {
        char s[10];
        getFunctionActivationMarker(i, &value, devicenum, getFunctionActivationMarkerDataStat_ENU);

        sprintf(s, "%d,", value);

        strcat(FAS, s);
        printf("index: %d, value: %d\n", i, value);
    }
    printf("%s\n", FAS);
    return;
}

//501-1000
void getFunctionActivationMarkerDataEnd(int devicenum)
{
    if (sockHandle[devicenum][getFunctionActivationMarkerDataEnd_ENU] == 0)
    {
        initDevice(devicenum, getFunctionActivationMarkerDataEnd_ENU);
    }
    pthread_t thread1;
    pthread_t thread2;
    int value = 0;
    int count = 500;
    int len = count * sizeof(unsigned) + count + 2 + 1;
    FAE = malloc(len);
    for (int i = (count + 1); i <= (count + 500); i++)
    {
        char s[10];
        getFunctionActivationMarker(i, &value, devicenum, getFunctionActivationMarkerDataEnd_ENU);
        if (i != (count + 500))
        {
            sprintf(s, "%d,", value);
        }
        else
        {
            sprintf(s, "%d", value);
        }
        strcat(FAE, s);
        printf("index: %d, value: %d\n", i, value);
    }
    strcat(FAE, "}");
    printf("%s\n", FAE);
    return;
}

//1-1000
/* void getFunctionQuitMarkerData(int devicenum){
    initDevice(devicenum, 6);  
    int value = 0;
    int count = 1000;
    int len = count*sizeof(unsigned) + count + 2 + 1;

    functionQuitMarker[devicenum]= malloc(len);
    memset(functionQuitMarker[devicenum], '\0', len);
    strcat(functionQuitMarker[devicenum], "{");
    for (int i = 1; i <= count; i++)
    {
        char s[10];       
        getFunctionQuitMarker(i, &value, devicenum);
        if(i != count){
            sprintf(s, "%d,", value);
        }
        else{
            sprintf(s, "%d", value);
        }
        strcat(functionQuitMarker[devicenum],s);
        // printf("index: %d, value: %d\n", i, value);        
    }
    strcat(functionQuitMarker[devicenum], "}");
    printf("%s\n", functionQuitMarker[devicenum]);
    return;
} */

//1-314 she ding zhi
void getValueParameterData(int devicenum)
{
    if (sockHandle[devicenum][getValueParameter_ENU] == 0)
    {
        initDevice(devicenum, getValueParameter_ENU);
    }
    int value = 0;
    int count = 314;
    int len = count * sizeof(unsigned) + count + 2 + 1;

    valueParameter[devicenum] = malloc(len);
    memset(valueParameter[devicenum], '\0', len);
    strcat(valueParameter[devicenum], "{");
    for (int i = 1; i <= count; i++)
    {
        char s[10];
        getValueParameter(i, &value, devicenum, getValueParameter_ENU);
        if (i != count)
        {
            sprintf(s, "%d,", value);
        }
        else
        {
            sprintf(s, "%d", value);
        }
        strcat(valueParameter[devicenum], s);
        // printf("index: %d, value: %d\n", i, value);
    }
    strcat(valueParameter[devicenum], "}");
    printf("%s\n", valueParameter[devicenum]);
    return;
}

//1-314 shi ji zhi
void getActualValueParameterData(int devicenum)
{
    if (sockHandle[devicenum][getActualValueParameter_ENU] == 0)
    {
        initDevice(devicenum, getActualValueParameter_ENU);
    }

    int value = 0;
    int count = 314;
    int len = count * sizeof(unsigned) + count + 2 + 1;

    actualValueParameter[devicenum] = malloc(len);
    memset(actualValueParameter[devicenum], '\0', len);
    strcat(actualValueParameter[devicenum], "{");
    for (int i = 1; i <= count; i++)
    {
        char s[10];
        getActualValueParameter(i, &value, devicenum, getActualValueParameter_ENU);
        if (i != count)
        {
            sprintf(s, "%d,", value);
        }
        else
        {
            sprintf(s, "%d", value);
        }
        strcat(actualValueParameter[devicenum], s);
        // printf("index: %d, value: %d\n", i, value);
    }
    strcat(actualValueParameter[devicenum], "}");
    printf("%s\n", actualValueParameter[devicenum]);
    return;
}

//1-500
void getAlarmsData(int devicenum)
{
    if (sockHandle[devicenum][getAlarms_ENU] == 0)
    {
        initDevice(devicenum, getAlarms_ENU);
    }
    int value = 0;
    int count = 500;
    int len = count * sizeof(unsigned) + count + 2 + 1;

    alarms[devicenum] = malloc(len);
    memset(alarms[devicenum], '\0', len);
    strcat(alarms[devicenum], "{");
    for (int i = 1; i <= count; i++)
    {
        char s[10];
        getAlarms(i, &value, devicenum, getAlarms_ENU);
        if (i != count)
        {
            sprintf(s, "%d,", value);
        }
        else
        {
            sprintf(s, "%d", value);
        }
        strcat(alarms[devicenum], s);
        // printf("index: %d, value: %d\n", i, value);
    }
    strcat(alarms[devicenum], "}");
    printf("%s\n", alarms[devicenum]);
    return;
}

//1-20
void getBatchParameterData(int devicenum)
{
    if (sockHandle[devicenum][getBatchParameter_ENU] == 0)
    {
        initDevice(devicenum, getBatchParameter_ENU);
    }
    int value = 0;
    int count = 20;
    int len = count * sizeof(unsigned) + count + 2 + 1;

    batchParameter[devicenum] = malloc(len);
    memset(batchParameter[devicenum], '\0', len);
    strcat(batchParameter[devicenum], "{");
    for (int i = 1; i <= count; i++)
    {
        char s[10];
        getBatchParameter(i, &value, devicenum, getBatchParameter_ENU);
        if (i != count)
        {
            sprintf(s, "%d,", value);
        }
        else
        {
            sprintf(s, "%d", value);
        }
        strcat(batchParameter[devicenum], s);
        // printf("index: %d, value: %d\n", i, value);
    }
    strcat(batchParameter[devicenum], "}");
    printf("%s\n", batchParameter[devicenum]);
    return;
}
