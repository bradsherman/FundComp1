// Brad Sherman
// Fundamentals of Computing 1
// Lab 5 Extra Credit
//

#include<stdio.h>

int main( void ) {

	int stack[100][30];
	int i = 0;
	int d = 0;
	int 	

	FILE *in_file = fopen("flapjacks.dat","r"); 

	if( in_file == NULL ) {
		printf("Error: Could not open file\n");
		return(0);
	}

	while( fscanf(stdin, "%i", &d)  != 'EOF' ){
		stack[i] = d;
		i++
	} 
