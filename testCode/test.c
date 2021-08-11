#include <stdio.h>
#include <stdbool.h>

int main(int agrc, char **argv)
{
    int a[] = {1,2,3,4};
    printf("a + 2 = %d\n", *(a + 2));
    return 0;
}