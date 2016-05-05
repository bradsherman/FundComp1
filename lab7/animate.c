// Brad Sherman
// Fundamentals of Computing 1
// Lab 7 Part 3
//

#include <stdio.h>
#include "gfx.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int new_omega( void );
void make_circles( int, int, int, int, double, double, double );
void make_squares( int, int, int, int, double, double, double, double, double );
void make_triangles( int, int, int, int, double, double, double, double, double );

int main( void ) {
	srand(time(NULL));
	int xsize = 1244, ysize = 700;
	double x = xsize/2, y = ysize/2, deltat = .01;
	int wait = 10000;
	double big_omega = new_omega();
	double small_omega = new_omega();
	double big_dtheta = 0, small_dtheta = 0;
	char c = 'c', c2 = 'c';
	int R = 250; // Radius of the big circle
	int r = 50; // Radius of shapes on the circle
	
	gfx_open( xsize, ysize, "SpinZone" );

	while( c != 'q' ) {

		gfx_clear();		
		gfx_color( 255, 255, 255 );
		gfx_circle( x, y, R );

		gfx_text( x-150, y-40, "Welcome to the SpinZone");
		gfx_text( x-150, y-30, "Left click to change rotation speed of the big circle");
		gfx_text( x-150, y-20, "Right click to change movement speed of small shapes");
		gfx_text( x-150, y-10, "Press \'t\' to change small shapes to triangles");
		gfx_text( x-150, y, "Press \'s\' to change small shapes to squares");
		gfx_text( x-150, y+10, "Press \'c\' to change small shapes to circles");
		gfx_text( x-150, y+20, "Press \'q\' to quit"); 

		big_dtheta = big_dtheta + big_omega*deltat;
		small_dtheta = small_dtheta + small_omega*deltat;	

		switch( c ) {
			case 1:
			// change rotation speed of big circle
				big_omega = new_omega();
				c = c2;
				break;
			case 3:
			// change rotation speed of smaller shapes
				small_omega = new_omega();
				c = c2;
				break;
			case 't':
			// change smaller shapes to triangles
				make_triangles(x, y, R, r, big_omega, big_dtheta, small_omega, small_dtheta, deltat);
				c2 = 't';
				break;
			case 's':
			// change smaller shapes to squares
				make_squares(x, y, R, r, big_omega, big_dtheta, small_omega, small_dtheta, deltat);
				c2 = 's';
				break;
			case 'c':
			// change smaller shapes to circles
				make_circles(x, y, R, r, big_omega, big_dtheta, deltat);
				c2 = 'c';
				break;
			case 'q':
				break;
			default:
				break;				

		}
		
		gfx_flush();
		usleep(wait);

		if( gfx_event_waiting() ) {
			c = gfx_wait();
		}
	}
}

int new_omega( void ) {
	int omega = (rand() % 3 + 1);
	omega = omega*( pow(-1, (rand() % 2) + 1) );
	return omega;
}

void make_circles( int x, int y, int R, int r, double omega, double dtheta, double deltat ) {
	double theta = 0;
	gfx_color( 0, 0, 255 );
	for( theta = 0; theta < (2*M_PI); theta = theta + ( M_PI/4 ) ) {
		gfx_circle( x + R*cos(theta+dtheta), y + R*sin(theta+dtheta), r );
	}
}

void make_squares( int x, int y, int R, int r, double big_omega, double big_dtheta, double small_omega, double small_dtheta, double deltat ) {
	double theta = 0;
	double bigx, smallx, bigy, smally;
	gfx_color( 255, 0, 0 );
	for( theta = 0; theta < (2*M_PI); theta = theta + ( M_PI/4 ) ) {
		bigx = R*cos(theta+big_dtheta);
		bigy = R*sin(theta+big_dtheta);		
		smallx = r*cos(theta+small_dtheta);
		smally = r*sin(theta+small_dtheta);
			
		gfx_line( x + bigx + smallx, y + bigy + smally, x + bigx + smallx, y + bigy - smally);
		gfx_line( x + bigx + smallx, y + bigy - smally, x + bigx - smallx, y + bigy - smally);
		gfx_line( x + bigx - smallx, y + bigy - smally, x + bigx - smallx, y + bigy + smally);
		gfx_line( x + bigx - smallx, y + bigy + smally, x + bigx + smallx, y + bigy + smally);
	}
} 

void make_triangles( int x, int y, int R, int r, double big_omega, double big_dtheta, double small_omega, double small_dtheta, double deltat ) {
	double theta = 0;
	double bigx, smallx, bigy, smally;
	gfx_color( 0, 255, 0 );
	for( theta = 0; theta < (2*M_PI); theta = theta + ( M_PI/4 ) ) {
		bigx = R*cos(theta+big_dtheta);
		bigy = R*sin(theta+big_dtheta);
		smallx = r*cos(theta+small_dtheta);
		smally = r*sin(theta+ small_dtheta);
		gfx_line( x + bigx + smallx, y + bigy - smally, x + bigx, y + bigy + smally);
		gfx_line( x + bigx, y + bigy + smally, x + bigx - smallx, y + bigy - smally);
		gfx_line( x + bigx - smallx, y + bigy - smally, x + bigx + smallx, y + bigy - smally);
	}
}
