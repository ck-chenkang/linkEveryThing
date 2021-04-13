#include <stdio.h>
#include <string.h>

struct configStruct
{
    char nodeId[255];
    char credentialKey[255];
    char deviceName[255];
    char deviceIp[255];
};


struct configStruct  loadconfig();
void  getNeedConfig(char * buff ,char mid[255]);