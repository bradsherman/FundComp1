// Brad Sherman
// Fundamentals of Computing 1
// Lab 2 Part 1
// Create a multiplication table with user designated dimensions

#include <stdio.h>

int main( void ){
	// Initialize variables and get user input
	int rows;
	int col;
	printf( "Please input the number of rows you would like: \n" );
	scanf( "%d", &rows );
	printf( "Please input the number of columns you would like: \n" );
	scanf( "%d", &col );
	
	// Check for valid input
	if( rows < 0 || col < 0 ) {
		printf( "Please enter a positive number of rows and columns.\n" );
		return(0);
	}
	
	int x;
	int y;
	// Prints first row to include special character of *
	printf( "%4c", '*' );
	for( y = 1; y <= col; y++ ) {
		printf( "%4d", y );
	}
	printf("\n");
	// Row iterator
	for( x = 1; x <= rows; x++ ) {
		printf ( "%4d", x );
		// Column iterator
		for( y = 1; y <= col; y++ ) {
			int entry = x*y;
			printf( "%4d", entry );
		}
		printf( "\n" );
	}
}

