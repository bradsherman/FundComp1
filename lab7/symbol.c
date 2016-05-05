// Brad Sherman
// Fundamentals Of Computing 1
// Lab 7 Part 1
//
 
#include<stdio.h>
#include "gfx.h"
#include<ctype.h>
#include<math.h>	

int main( void ) {

	int xsize = 500;
	int ysize = 500;

	char c;
	
	gfx_open( xsize, ysize, "Symbol Program" );
	
	gfx_clear();

	int i;

	while( c = gfx_wait() ) {
		double xc = gfx_xpos();
		double yc = gfx_ypos();
		int dx;
		if( isupper(c) ) c = tolower(c);
		switch( c ) {
	
			case 1:
				dx = 20;
				gfx_color( 0, 0, 204 );
				gfx_line( xc-dx, yc-dx, xc-dx, yc+dx );
				gfx_line( xc-dx, yc+dx, xc+dx, yc+dx );
				gfx_line( xc+dx, yc+dx, xc+dx, yc-dx );
				gfx_line( xc+dx, yc-dx, xc-dx, yc-dx );
				break;
			case 't':
				dx = 20;
				gfx_color( 0, 175, 0 );
				gfx_line( xc-dx, yc-dx, xc, yc+dx );
				gfx_line( xc, yc+dx, xc+dx, yc-dx );
				gfx_line( xc+dx, yc-dx, xc-dx, yc-dx );
				break;
			case 'c':
				gfx_color( 255, 255, 255 );
				gfx_circle( xc, yc, 20 );
				break;
			default:
				if( c >= '3' && c <= '9' ) {	
					i = c - '0';
				}		
				int j;
				double theta = (360/i)*(M_PI/180);
				int r = 30;
				gfx_color( 102, 0, 102 );
				for( j = 0; j < i; j++ ) {
					gfx_line( xc+r*cos(theta*j), yc+r*sin(theta*j), xc+r*cos(theta*(j+1)), yc+r*sin(theta*(j+1)) );
				}  
				break;
		}
		if( c == 'q' ) break;
	}
} 
