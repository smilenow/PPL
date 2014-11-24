===

Many language rules are checked by the compiler, and it is possible to bypass the rules using assembly language after compilation. Consider the following C program:


	#include <stdio.h>
	
	int x=3;
	int main(void) {
    	int x=5;
    	printf("x = %d", x);
	    return 0; 
	}

1. Compile the program and generate its assembly code.
2. Understand the assembly code and modify it to let the program print the global variable x instead of the local variable x.


Submit a report discussing the generated assembly code and your modification. Explain your way in detail.