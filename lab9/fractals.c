// Brad Sherman
// Fundamentals of Computing 1
// Lab 9
//

#include <stdio.h>
#include "gfx4.h"
#include <math.h>

void sierpinski( int, int, int, int, int, int );
void draw_triangle( int, int, int, int, int, int );
void shrinking_squares( int, int, double );
void draw_square( int, int, double );
void spiral_squares( int, int, double, double );
void circular_lace( int, int, double, double );
void snowflake( int, int, double, double );
void tree( int, int, double, double );
void fern( int, int, double, double );
void spirals( int, int, double, double );

int main( void ) {
	char c;
	int xsize = 700, ysize = 700;
	int buff = 20; // padding to keep the shapes away from the edge of the screen
	double length = 200;	
	double radius = 250;
	double theta = M_PI/4;

	gfx_open( xsize, ysize, "Fractals" );

	while( c != 'q' ) {
		gfx_clear();
		switch ( c ) {
			// Xsize and Ysize over 2 are the center of the screen, and most
			// other constants were found by running the program multiple times
			// to see which way it looked the best at.
			case '1':
				sierpinski( buff, buff, xsize-buff, buff, xsize/2, ysize-buff); 
				break;
			case '2':
				shrinking_squares( xsize/2, ysize/2, length );
				break;
			case '3':
				spiral_squares( xsize/2, ysize/2, radius, theta );
				break;
			case '4':
				circular_lace( xsize/2, ysize/2, radius, 0 );
				break;
			case '5':
				snowflake( xsize/2, ysize/2, radius, theta );
				break;
			case '6':
				tree( xsize/2, ysize-buff, length, M_PI/2 );
				break;
			case '7':
				fern( xsize/2, ysize-buff, 1./2*length, M_PI/2 );
				break;
			case '8':
				spirals( xsize/2, ysize/2-100, radius+50, theta );
				break;
			default:
				break;
		}
		c = gfx_wait();
	}
}
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 ) {
	// Base Case
	if( abs(x2-x1) < 2 ) return;
	
	draw_triangle( x1, y1, x2, y2, x3, y3 );
	
	// Recursion
	sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
	sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
	sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}
void draw_triangle( int x1, int y1, int x2, int y2, int x3, int y3 ) {
	gfx_line( x1, y1, x2, y2 );
	gfx_line( x2, y2, x3, y3 );
	gfx_line( x3, y3, x1, y1 );
}
void shrinking_squares( int x, int y, double length ) {
	// Base Case
	if( length < 4 ) return;
	draw_square( x, y, length );	
	double length2 = length/2;
	// length3 is one half the length of the side of the current square
	// found by pythagorean's theorem, since length is the 
	// hypotenuse of a triangle made inside the curent square
	double length3 = sqrt(pow(length,2)/2);
	// Recursion
	shrinking_squares( x + length3, y + length3, length2 );
	shrinking_squares( x + length3, y - length3, length2 );
	shrinking_squares( x - length3, y - length3, length2 );
	shrinking_squares( x - length3, y + length3, length2 );
}
void spiral_squares( int x, int y, double radius, double theta ) {
	// Base Case
	if( radius < 2 ) return;
	
	int x2 = x + radius*cos(theta);
	int y2 = y + radius*sin(theta);
	draw_square( x2, y2, radius/4 );
	// Constants found through trial and error
	double r2 = radius*9/10;
	double theta2 = theta + M_PI/6;

	// Recursion
	spiral_squares( x, y, r2, theta2);
}
void draw_square( int x, int y, double length ) {
	int x1, y1, x2, y2;
	double theta = M_PI/4;
	int i;
	for( i = 0; i < 4; i++ ) {
		x1 = x + length*cos(theta);
		y1 = y + length*sin(theta);
		theta = theta + M_PI/2;
		x2 = x + length*cos(theta);
		y2 = y + length*sin(theta);
		gfx_line( x1, y1, x2, y2 );
	}
}
void circular_lace( int x, int y, double radius, double theta ) {
	// Base Case
	if( radius < 2 ) return;
	gfx_circle( x, y, radius );
	double theta2 = M_PI/3;
	double r2 = radius/3;
	int i;
	// Recursion
	for( i = 0; i < 6; i++ ) {
		circular_lace( x+radius*cos(theta+i*theta2), y+radius*sin(theta+i*theta2), r2, 0);
	}
}
void snowflake( int x, int y, double length, double theta ) {
	// Base Case
	if(length < 2 ) return;
	int i;
	double theta2 = 2*M_PI/5;
	double r2 = length/3;
	for( i = 0; i < 5; i++ ) {
		gfx_line( x, y, x+length*cos(theta+i*theta2), y+length*sin(theta+i*theta2));
		// Recursion
		snowflake( x+length*cos(theta+i*theta2), y+length*sin(theta+i*theta2), r2, theta);
	}
}
void tree( int x, int y, double length, double theta ) {
	// Base Case
	if( length < 2 ) return;
	int x2 = x+length*cos(theta);
	int y2 = y-length*sin(theta);
	gfx_line( x, y, x2, y2);
	double theta2 = M_PI/6;
	double l2 = length*7/10;
	// Recursion
	tree( x2, y2, l2, theta+theta2);
	tree( x2, y2, l2, theta-theta2);
}
void fern( int x, int y, double length, double theta ) {
	// Base Case
	if( length < 3 ) return;
	int x2 = x+4*length*cos(theta);
	int y2 = y-4*length*sin(theta);
	double theta2 = M_PI/6;
	double l2 = length/3;
	gfx_line( x, y, x2, y2 );
	int i;
	for( i = 1; i < 5; i++ ) {	
		// Recursion
		fern( x+i*length*cos(theta), y-i*length*sin(theta), l2, theta+theta2 );
		fern( x+i*length*cos(theta), y-i*length*sin(theta), l2, theta-theta2 );
	}
}
void spirals( int x, int y, double radius, double theta ) {
	// Base Case
	if( radius < .5 ) return;
	int x1 = x + radius*cos(theta);
	int y1 = y + radius*sin(theta);
	theta = theta + M_PI/6;
	radius = radius*9./10;
	int x2 = x + radius*cos(theta);
	int y2 = y + radius*sin(theta);
	gfx_line(x1, y1, x2, y2 );
	// Recursion
	spirals( x, y, radius, theta );
	spirals( x1, y1, radius/3, theta );
	spirals( x2, y2, radius/3, theta );
}
