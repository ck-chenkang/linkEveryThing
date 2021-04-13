#include "config.h"


struct configStruct  loadconfig(){
    FILE *fp =NULL; 
    char buff[255];  
    struct configStruct localConfig; 
    
    fp = fopen("./config.ini", "r");
    for (int i = 0; i < 4; i++)
    {        
        fgets(buff, 255, fp);
        switch (i)
        {
        case 0:           
            getNeedConfig(buff, localConfig.nodeId);
        break;
        case 1:
            getNeedConfig(buff, localConfig.credentialKey);
 
            break;
        case 2:
            getNeedConfig(buff, localConfig.deviceName);
 
            break;
        case 3:
            getNeedConfig(buff, localConfig.deviceIp);

            break;        
        default:
            break;
        }
    }
    fclose(fp);
    fp = NULL;
    return localConfig;
}

void  getNeedConfig(char * midbuff , char mid[255]){
    char *ptr; //ptr is to store memery address of '='
    int pos = 0;//pos is to store index of '='
    char c = '=';    
    ptr = strchr(midbuff, c);
    pos = ptr - midbuff;
    for(int i=pos; i<=255;i++){
        if(midbuff[i] == NULL){
            ptr = NULL;
            midbuff = NULL;
            break;
        }
        mid[i-pos] = midbuff[i+1];
    } 
}