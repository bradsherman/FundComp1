// Brad Sherman
// Fundamentals of Computing 1
// Lab 9 Gallery
//

#include <stdio.h>
#include "gfx4.h"
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

struct Tree {
	int x;
	int y;
	double size;
	double theta;
	double dtheta;
	double omega;
};

void tree( int, int, double, double );
int randx( int );
double randsize( int );
int randcolor( void );

int main( void ) {
	// Initialize variables
	int numtrees = 20;
	struct Tree Trees[numtrees];
	int xsize = 1000;
	int ysize = 700;
	srand(time(NULL));
	char c;

	int i;
	// Set original values of each tree
	for( i = 0; i < numtrees; i++ ) {
		Trees[i].x = randx(xsize);
		Trees[i].y = ysize - 50;
		Trees[i].size = randsize(ysize);
		Trees[i].theta = M_PI/2;//randtheta();
	}
	gfx_open( xsize, ysize, "Tree Gallery" );
	i = 0;
	while( c != 'q' ) {
		// Draw background color
		gfx_clear_color( 102, 255, 255 );
		gfx_clear();
		gfx_color( 0, 255, 0);
		gfx_fill_rectangle( 0, ysize-50, xsize, 50);
		// Draw each tree using the array of Tree structs
		for( i = 0; i < numtrees; i++ ) {
			gfx_color( randcolor(), randcolor(), randcolor() );
			Trees[i].x = randx(xsize);
			Trees[i].size = randsize(ysize);
			tree(Trees[i].x, Trees[i].y, Trees[i].size, Trees[i].theta );
		}
		
		c = gfx_wait();
	}
}
int randcolor() {
	// used to give each tree a random color
	return (rand() % 255 );
}
void tree( int x, int y, double length, double theta) {
	// Base Case
	if( length < 2 ) return;
	int x2 = x+length*cos(theta);
	int y2 = y-length*sin(theta);
	gfx_line( x, y, x2, y2 );
	double theta2 = M_PI/6;
	double l2 = length*7./10;
	// Recursion
	tree( x2, y2, l2, theta + theta2 );
	tree( x2, y2, l2, theta - theta2 );
}
int randx(int xsize) {
	// Gives trees random x position based on the size of the screen
	return ( rand() % xsize + 1 );
}
double randsize(int ysize) {
	// Gives trees random height based on height of the screen
	return ( rand() % (ysize-3*ysize/4) + 1 );
}
