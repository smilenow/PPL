#include <stdio.h>
int x=3;
int main(void) {
    int x=5;
    int ret = printf("x = %d", x);
    printf("ret = %d",ret);
    return 0;
}