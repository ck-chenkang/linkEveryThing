#include <stdio.h>
#include <string.h>

/* Case insensitive string comparison, doesn't consider two NULL pointers equal though */
static int case_insensitive_strcmp(const unsigned char *string1, const unsigned char *string2)
{
    if ((string1 == NULL) || (string2 == NULL))
    {
        return 1;
    }

    if (string1 == string2)
    {
        return 0;
    }

    for(; tolower(*string1) == tolower(*string2); (void)string1++, string2++)
    {
        if (*string1 == '\0')
        {
            return 0;
        }
    }

    return tolower(*string1) - tolower(*string2);
}


int main(){
    unsigned  char * a = "nihao";
    unsigned char * b = "ni";
    int result = case_insensitive_strcmp(a, b);
    printf("%d\n", result);
    return 0;
}