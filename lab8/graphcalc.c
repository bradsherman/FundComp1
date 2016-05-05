// Brad Sherman
// Fundamentals of Computing 1
// Lab 8 Part 1
// 
 
#include <stdio.h>
#include "gfx2.h"
#include <string.h>
#include <unistd.h>
#include <math.h>

char *num2str( int );
void draw_axes( int, int, int, int );
void redraw( int, int, int, int, int );
double factorial( int );
double taylor_series( double, int );
void draw_legend( int );

int main( void ) {
	int i, terms = 1;
	int xsize = 700, ysize = 700;
	char a;

	gfx_open( xsize, ysize, "Graphing Calculator" );
	gfx_clear();	

	int xcenter = xsize/2;
	int ycenter = ysize/2;
	
	while( a != 'q' ) {
		// Draw legend, axes, and graphs each time the plus or minus is pushed
		draw_legend( terms );
		draw_axes(xcenter, ycenter, xsize, ysize);		
		redraw( terms, xsize, ysize, xcenter, ycenter);
		if( a == '=' ) {
			terms++;
			gfx_clear();
			draw_axes(xcenter, ycenter, xsize, ysize);		
			redraw(terms, xsize, ysize, xcenter, ycenter);
			draw_legend( terms );
		}
		if( a == '-' && terms != 1 ) {
			terms--;
			gfx_clear();
			draw_axes(xcenter, ycenter, xsize, ysize);		
			redraw(terms, xsize, ysize, xcenter, ycenter);
			draw_legend( terms );
		}
		a = gfx_wait();
	}
}

char *num2str( int n ) {
	static char a[10], *p = a;
	snprintf( p, 10, "%d", n );
	return p;
}

void draw_axes( int xcenter, int ycenter, int xsize, int ysize ) {
	int i;
	gfx_color( 0, 153, 153 );
	gfx_line( 0, ycenter, xsize, ycenter );
	gfx_line( xcenter, 0, xcenter, ysize );
	gfx_text( xcenter + 5, ycenter + 15, "0" );
	// Draw x axis and then y axis by doing both the positive and negative numbers
	// and ticks in the same for loop for x and y respectively.

	for( i = 1; i < 11; i++ ) {
		gfx_text( xcenter + i*35 - 3, ycenter + 15, num2str(i) );
		gfx_line( xcenter + i*35, ycenter - 2, xcenter + i*35, ycenter + 2);
		gfx_text( xcenter - i*35 - 8, ycenter + 15, num2str(-1*i) ); 	
		gfx_line( xcenter - i*35, ycenter - 2, xcenter - i*35, ycenter + 2);
	}
	for( i = 1; i < 11; i++ ) {
		gfx_text( xcenter - 20, ycenter - i*35 + 5, num2str(i) );
		gfx_line( xcenter - 2, ycenter - i*35, xcenter + 2, ycenter - i*35);
		gfx_text( xcenter - 25, ycenter + i*35 + 5, num2str(-1*i) ); 	
		gfx_line( xcenter - 2, ycenter + i*35, xcenter + 2, ycenter + i*35);
	}
}

double factorial( int x ) {
	// Factorial function used in the taylor series expansion
	int i;
	double factorial = 1;
	if( x == 0 ) return 1;
	else {
		for( i = 1; i <= x; i++) {
			factorial = factorial*i;
		}
		return factorial;
	}
}	
	
void redraw( int terms, int xsize, int ysize, int xcenter, int ycenter ) {
	// These variables are for the taylor series approximation
	int i, x1, y1, x2, y2;
	double xdub1, ydub1, xdub2, ydub2;
	// These variables are for the sine wave
	int x3, y3, x4, y4;
	double xdub3, ydub3, xdub4, ydub4;

	for( i = 0; i < xsize; i++ ) {
		// Set each x-coordinate in pixel form
		x1 = i;
		x3 = i;
		x2 = i + 1;
		x4 = i + 1;
		// Scale the pixel coordinate to decimal value relative to the graph
		xdub1 = (x1 - xcenter)/35.;
		xdub2 = (x2 - xcenter)/35.;
		xdub3 = (x3 - xcenter)/35.;
		xdub4 = (x4 - xcenter)/35.;
		// Find y coordinate relative to the graph
		ydub1 = taylor_series( xdub1, terms );
		ydub2 = taylor_series( xdub2, terms );
		ydub3 = sin(xdub3);
		ydub4 = sin(xdub4);
		// Convert y coordinate back to pixel form
		y1 =  (ydub1*-35.) + ycenter;
		y2 = (ydub2*-35.) + ycenter;	
		y3 = (ydub3*-35.) + ycenter;
		y4 = (ydub4*-35.) + ycenter;
		// Print graphs, only prints the taylor series points that 
		// are contained in the window
		gfx_color( 0, 204, 0 );
		gfx_line( x3,y3,x4,y4 );
		gfx_color( 255, 0, 127 );
		if( y1 <= ysize && y2 <= ysize && y1 >= 0 && y2 >= 0 ) {
			gfx_line( x1, y1, x2, y2 );
		}
	}
}

double taylor_series( double x, int terms ) {
	// Taylor series approximation for x, with "terms" number of terms
	// Used in the redraw function
	int i;
	double j, sum = 0;
	for( i = 0; i < terms; i++ ) {
		j = i;
		sum = (pow(-1.,j)*(pow(x,(2*j+1))/factorial(2*j+1))) + sum;
	}
	return sum;
}

void draw_legend( int terms ) {
	// Legend for sine wave and taylor series approximation
	char legend[50] = "Taylor Series: ";
	strcat(legend, num2str(terms) );
	strcat(legend, " terms" );
	gfx_color( 0, 204, 0 );
	gfx_line( 25, 25, 35, 25 );
	gfx_text( 40, 30, "Sine wave" );
	gfx_color( 255, 0, 127 );
	gfx_line( 25, 40, 35, 40 );
	gfx_text( 40, 45, legend );
}
