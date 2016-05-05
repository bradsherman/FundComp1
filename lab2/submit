// Brad Sherman
// Fundamentals of Computing 1
// Lab 2 Part 3
// Create and display a graph of a non-trivial function and show its maximum and
// minimum values and where they occur.

#include<stdio.h>
#include<math.h>

int main( void ) {
	printf( "Here is a graph of the function y = (15*cos(x)) + 20 for x = 0 to 100\n" );
	printf( "  X      Y\n" );
	float x;
	float y;
	int l;	
	float xmax = 0;
	float max=0;
	float xmin = 0;
	float min=100;
	
	for( x = 0; x <= 20; x = x + .5 ) {
		y = (15*cos(x)) + 20;
		// Finds the maximum
		if( y > max ) {
		max = y;
		xmax = x;
		}
		// Finds the minimum
		if( y < min ) {
		min = y;
		xmin = x;
		}
		printf( "%5.1f   %5.1f ", x, y );
		int g;
		// Rounds to create integers since there are no half pound symbols
		g = round(y);
		for( l = 1; l <= g; l++ ) {
			printf("#");
		}
		printf("\n");
	}
	printf( "The maximum of the function was %4.1f at x = %4.1f\n", max, xmax );
	printf( "The minimum of the function was %4.1f at x = %4.1f\n", min, xmin );
}

