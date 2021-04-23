#ifndef _GNU_SOURCE
#define _GNU_SOURCE //need
#endif 
#include <stdio.h>

int main(int argc, char**argv  ){

    char **test;
    asprintf(&test, "hello, %d\n", 123); // '&' is needed
    printf("%p\n",test);
    printf("%p\n",*test);
    printf("%s\n",test);
    puts(test);
    free(test);
    return 0;
}