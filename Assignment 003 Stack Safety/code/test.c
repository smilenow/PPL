#include <stdio.h>
#include <string.h>

int gao() {
    int i = 12;
    char buffer[4] = {0};
/*
    buffer[0] = '0';
    buffer[1] = '1';
    buffer[2] = '2';
    buffer[3] = '3';
    buffer[4] = '4';
    buffer[5] = '5';
    buffer[6] = '6';
    buffer[7] = '7';
    buffer[8] = '8';
*/
    gets(buffer);
    printf("%d\n",i);
    printf("%d\n",(int)strlen(buffer));
    return 0;
}

int main(){
    printf("before gao()\n");
    gao();
    printf("after gao()\n");
    return 0;
}
