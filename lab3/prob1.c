// Brad Sherman
// Fundamentals Of Computing 1
// Lab 3 Part 1
//
//


#include<stdio.h>
int getgcd(int,int);

int main( void ) {
	
	int x;
	int y;
	
	printf( "Please enter two numbers to find their greatest common divisor.\n" );
	printf( "\n" );
	printf( "Number 1: " );
	scanf( "%d", &x );
	printf( "Number 2: " );
	scanf( "%d", &y );
	
	int g;
	g = getgcd(x,y);
	printf( "The greatest common divisor of %d and %d is %d. \n", x,y,g );
}

int getgcd( int x, int y ) {
	while( y != 0 ) {
	int a, b;
	a = x;  // Introduce a and b so that we can store the original values
	b = y;  // of x and y before we start doing calculations.
	x = b;
	y = a%b; // y is now the remainder which we use to divide our new x 
	}        // value with on our next iteration as in the Euclidean algorithm.
	return x;
}	
