#include <stdio.h>
long fact(int x){
	if (x<=1) return 1;
	else return x+fact(x-1);
}
int main(){
	int x;
	scanf("%d",&x);
	printf("X = %d , ",x);
	printf("%ld", fact(x));
	printf(" , OK!\n");
}
