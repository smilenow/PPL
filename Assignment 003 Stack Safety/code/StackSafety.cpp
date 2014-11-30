#include <iostream>
long fact(int x){
	if (x<=1) return 1;
	else return x+fact(x-1);
}
int main(){
	int x;
	for (x=0;x<1000000;x++){
		printf("X = %d , ",x);
		printf("%ld", fact(x));
		printf(" , OK!\n");
	}
}
