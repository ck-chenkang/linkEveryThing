#include "setexAPI.h"

void testSetexAPI()
{
    int ch[10] = {0, 1, 0, 0, 1, 0, 0, 1, 1, 1};
    const char *deviceip = "192.168.13.202";
    int value = 0;
    unsigned uvalue = 0;
    initialize(deviceip); 
    printf("__INT_MAX__:%d\n ", __INT_MAX__);
    printf("getPictureLayers: %d\n", getPictureLayers(ch));
    printf("setPictureLayers: %d\n", setPictureLayers(ch));
    for(int i=1; i <= 200; i++){
        getInfoWord(i, &value);
        printf("index:%-10d    ", i);
        printf("value:%d\n" , value);
    }    
}

int main()
{
    printf("Programming is stating.....\n");
    // testSetexAPI();
    printf("Programming is ending.....\n");    
    return 0;
}