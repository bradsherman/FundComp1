// Brad Sherman
// Fundamentals of Computing 1
// Lab 5 Extra Credit
//


#include<stdio.h>
int factorial( int );

int main( void ) {
	
	int i;
	int j;
	int sum = 0;
	for( j = 1; j <= 9999999; j++ ) {
		for( i = 1; i <= sizeof(j)/sizeof(int); i++) {
			sum = sum + factorial(j[i]);
			if( sum == j ) {
				printf("The factorial of each digit of %d equals %d.\n", j,j );
			}
		}
	}
}

int factorial( int x ) {
	int sum = 1;
	int i;
	for( i = 1; i <= x; i++ ) {
		sum = sum*i;
	}
	return sum;
}
 
