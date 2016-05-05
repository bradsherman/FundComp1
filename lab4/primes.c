// Brad Sherman
// Fundamentals of Computing 1
// Lab 4 Part 2
//

#include<stdio.h>


int main( void ) {

	int nums[1000];
	int k = 2;
	// Initialize all values to 1
	for( k = 2; k <= 999; k++ ) {
		nums[k] = 1;
	}
	int i = 2;
	int j = 2;
	for( i = 2; i <= 999; i++ ) {
		j = 2;
		// change all multiples of prime 
		// numbers to 0, starting with 2
		while( i*j <= 999) {
			nums[i*j] = 0;
			j = j + 1;
		}
	}
	int m = 0;
	int n = 0;
	for( m = 1; m <= 999; m++ ) {
		if( nums[m] == 1 ) {
			n = n + 1;
			if( n % 10 == 0) {
				printf( "%4d \n", m );
			} else {
				printf( "%4d ", m );
			}
		}
	} printf( "\n" );
}
