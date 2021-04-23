#ifndef __SETEXAPI_H__
#define __SETEXAPI_H__
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>

#define SETEXPORT 50000
#define BUFFER_SIZE 516


int sockHandle[10][21];


int initialize(const char *deviceip,int sockHandleIndex, int tagindex);

int getPictureLayers(int *ch,int sockHandleIndex, int tagindex); 
int setPictureLayers(int *ch,int sockHandleIndex, int tagindex);

int getInfoWord(int index, int*value,int sockHandleIndex, int tagindex);
int setInfoWord(int index, int value,int sockHandleIndex, int tagindex);

int getInfoDoubleWord(int index, unsigned *value,int sockHandleIndex, int tagindex);
int setInfoDoubleWord(int index, unsigned value,int sockHandleIndex, int tagindex);

int getInfoBit(int index, int *value,int sockHandleIndex, int tagindex);
int setInfoBit(int index, int value,int sockHandleIndex, int tagindex);

int getFunctionInitMarker(int index, int *value,int sockHandleIndex, int tagindex);
int setFunctionInitMarker(int index, int value,int sockHandleIndex, int tagindex);

int getFunctionActivationMarker(int index, int *value,int sockHandleIndex, int tagindex);
int setFunctionActivationMarker(int index, int value,int sockHandleIndex, int tagindex);

int getFunctionQuitMarker(int index, int *value,int sockHandleIndex, int tagindex);
int setFunctionQuitMarker(int index, int value,int sockHandleIndex, int tagindex);

int getValueParameter(int index, int *value,int sockHandleIndex, int tagindex);
int setValueParameter(int index, int value,int sockHandleIndex, int tagindex);

int getActualValueParameter(int index, int *value,int sockHandleIndex, int tagindex);
int setActualValueParameter(int index, int value,int sockHandleIndex, int tagindex);

int getAlarms(int index, int *value,int sockHandleIndex, int tagindex);
int setAlarms(int index, int value,int sockHandleIndex, int tagindex);

int getAlarms2(int index, int *value,int sockHandleIndex, int tagindex);
int setAlarms2(int index, int value,int sockHandleIndex, int tagindex);

int getControlMarker(int index, int *value,int sockHandleIndex, int tagindex);
int setControlMarker(int index, int value,int sockHandleIndex, int tagindex);

int getControlWords(int index, int *value,int sockHandleIndex, int tagindex);
int setControlWords(int index, int value,int sockHandleIndex, int tagindex);

int getControllerParameter(int index, int *value,int sockHandleIndex, int tagindex);
int setControllerParameter(int index, int value,int sockHandleIndex, int tagindex);

int getTimers(int index, int *value,int sockHandleIndex, int tagindex);
int setTimers(int index, int value,int sockHandleIndex, int tagindex);

int getMachineConstant(int index, int *value,int sockHandleIndex, int tagindex);
int setMachineConstant(int index, int value,int sockHandleIndex, int tagindex);

int getBatchParameter(int index, int *value,int sockHandleIndex, int tagindex);
int setBatchParameter(int index, int value,int sockHandleIndex, int tagindex);

int getBatchParameterDS737(int index, int *value,int sockHandleIndex, int tagindex);
int setBatchParameterDS737(int index, int value,int sockHandleIndex, int tagindex);

int getBatchParameterNextBatch(int index, int *value,int sockHandleIndex, int tagindex);
int setBatchParameterNextBatch(int index, int value,int sockHandleIndex, int tagindex);

int getMaintenanceCounter(int index, int *value,int sockHandleIndex, int tagindex);
int setMaintenanceCounter(int index, int value,int sockHandleIndex, int tagindex);

int getActionButtons(int index, int *value,int sockHandleIndex, int tagindex);
int setActionButtons(int index, int value,int sockHandleIndex, int tagindex);

#endif
