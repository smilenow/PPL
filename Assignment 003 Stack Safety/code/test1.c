#include <stdio.h>
#include <string.h>

int main(void)
{
    int len = 11;
    char str[4] = {0};
    
    gets(str); // Used gets() to cause buffer overflow
    
    printf("\n len = [%d] \n", len);
    
    //len  = strlen(str);
    printf("\n len of string entered is : [%d]\n", strlen(str));
    
    return 0;
}
