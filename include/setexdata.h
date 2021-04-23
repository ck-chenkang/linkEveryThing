#ifndef __SETEXDATA_H__
#define __SETEXDATA_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "connectConfig.h"
#include "setexAPI.h"
#define arr_num 10

char *FAS;
char *FAE;
enum {
    getInfoWord_ENU=0, getInfoDoubleWord_ENU,getInfoBit_ENU, getFunctionActivationMarkerDataStat_ENU,
    getFunctionActivationMarkerDataEnd_ENU,getValueParameter_ENU,
    getActualValueParameter_ENU,getAlarms_ENU,getBatchParameter_ENU
} tagIndexList;

char *infoWordData[arr_num];
char *infoDoubleWordData[arr_num];
char *infoBitData[arr_num];
char *functionInitMarker[arr_num];
char *functionActivationMarker[arr_num];
char *functionQuitMarker[arr_num];
char *valueParameter[arr_num];
char *actualValueParameter[arr_num];
char *alarms[arr_num];
// char *alarms2[arr_num];
// char *controlMarker[arr_num];
// char *controlWords[arr_num];
// char *controllerParameter[arr_num];
// char *timers[arr_num];
// char *machineConstant[arr_num];
char *batchParameter[arr_num];
// char *batchParameterDS737[arr_num];
// char *mavoidenanceCounter[arr_num];
// char *actionButtons[arr_num];

void initDevice(int devicenum, int tagindex);

void getInfoWordData(int devicenum);
void getInfoDoubleWordData(int devicenum);
void getInfoBitData(int devicenum);
// void getFunctionInitMarkerData(int devicenum);
void getFunctionActivationMarkerDataStat(int devicenum);
void getFunctionActivationMarkerDataEnd(int devicenum);
// void getFunctionActivationMarkerData(int devicenum);
// void getFunctionQuitMarkerData(int devicenum);
void getValueParameterData(int devicenum);
void getActualValueParameterData(int devicenum);
void getAlarmsData(int devicenum);
// void getAlarms2Data(int devicenum);
// void getControlMarkerData(int devicenum);
// void getControlWordsData(int devicenum);
// void getControllerParameterData(int devicenum);
// void getTimersData(int devicenum);
// void getMachineConstantData(int devicenum);
void getBatchParameterData(int devicenum);
// void getBatchParameterDS737Data(int devicenum);
// void getMavoidenanceCounterData(int devicenum);
// void getActionButtonsData(int devicenum);

#endif