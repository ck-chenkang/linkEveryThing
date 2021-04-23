#include <stdio.h>

int main(int agrc, char **argv)
{ 
    printf("%d\n", agrc);  // parameter count + 1
    printf("%s\n", argv[0]); // the program path
    printf("%s\n", argv[1]); // first parameter
    return 0;
}