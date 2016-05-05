// Brad Sherman
// Fundamentals of Computing 1
// Lab 7 Part 2
//

#include <stdio.h>
#include "gfx.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int new_v( void );

int main( void ) {
	srand(time(NULL));
	double x, y, deltat = .01;
	int wait = 10000;
	int vx = new_v();
	int vy = new_v();
	int loop = 1;
	char c;	
	int radius = 50;
	int xsize = 600, ysize = 600;

	gfx_open( xsize, ysize, "Bounce" );
	x = xsize/2;
	y = ysize/2;	

	while( loop ) {
		if( c == 'q' ) loop = 0;
	
		gfx_clear();
		gfx_color( 243, 26, 26 );
		gfx_circle( x, y, radius );
	
		if( c == 1 ) {
			x = gfx_xpos();
			y = gfx_ypos();
			vx = new_v();
			vy = new_v();
			c = 0;
		}	

		x = x + vx*deltat;;
		y = y + vy*deltat;;
		if( x + radius >= xsize ) {
			vx = -1*vx;
			x = xsize - radius - 1;
		}
		if( x - radius <= 0 ) {
			vx = -1*vx;
			x = radius + 1;
		}
		if( y + radius >= ysize ) {
			vy = -1*vy;
			y = ysize - radius - 1;
		}
		if( y - radius <= 0 ) {
			vy = -1*vy;
			y = radius + 1;
		}
		
		gfx_flush();
		usleep(wait);
	
		if( gfx_event_waiting() ) {
			c = gfx_wait();
		}
	}
}

int new_v( void ) {
	int vx = rand() % 400 + 1;
	vx = vx*( pow(-1, (rand() % 2) + 1) );
	return vx;
}

