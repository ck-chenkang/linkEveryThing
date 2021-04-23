#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv)
{
    FILE *f = fopen("connectConfig.json", "rb");
    if(f == NULL){
        puts("open file failed");
        return -1;
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);
    puts(string);    
    free(string);
    return 0;
}