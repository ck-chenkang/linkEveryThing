#ifndef __CONNECT_CONFIG_H__
#define __CONNECT_CONFIG_H__
#include <stdio.h>
#include "../inc/cJSON.h"
struct deviceStruct
{
    char *Name;
    char *Ip;
};

struct connectStruct
{
    char *nodeId;
    char *credentialKey;
    int deviceCount;
    struct deviceStruct *deviceInfo;
} connectInfo;

static char *jsonStr;
static cJSON *root = NULL;
static cJSON *item = NULL; 

static void getJsonStr();

static void getNodeIdAndCredentialkey();

static void getDevicesInfo();

void initConnectInfo();

#endif