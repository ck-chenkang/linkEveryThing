#include <stdio.h>
#include <stdlib.h>

typedef struct deviceStruct
{
   char *name;
   char *ip;
} deviceStruct;

deviceStruct * midDeviceStruct;

void test(){
    midDeviceStruct = malloc(sizeof *midDeviceStruct);
    midDeviceStruct->name = "nihaoa,wojuedeyaochucuo!!!";
    midDeviceStruct->ip = "192.168.163.12";
    printf("size of struct %ld\n", sizeof midDeviceStruct);
    puts(midDeviceStruct->name);
    printf("sizeof int %ld\n", sizeof(int));
    printf("sizeof char %ld\n", sizeof(char));
    printf("sizeof char* %ld\n", sizeof(char*));
}

int main(int agrc, char **argv)
{
    test();
    puts(midDeviceStruct->name);

    return 0;
}