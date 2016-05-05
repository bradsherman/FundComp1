// Brad Sherman
// Fundamentals of Computing 1
// Lab 8 Part 2
//

#include <stdio.h>
#include "gfx2.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Object  {
	int x_pos;
	int y_pos;
	double speed;
	double xspeed;
	double yspeed;
	int size;
	double theta;
};

double new_v( void );
void draw_pivot( struct Object *, struct Object *, struct Object *, struct Object *, int, int, int, double );
void draw_pendulum( struct Object *, struct Object *, struct Object *, int, int, int, int, double );
void draw_base( struct Object *, struct Object *, int, int );
void draw_buckets( struct Object *, int, int );

int main( void ) {
	// Initialize variables
	srand(time(NULL));
	int xsize = 1244, ysize = 700;
	double xcenter = xsize/2, ycenter = ysize/2, deltat = .1;
	int wait = 100000;
	char c;	
	struct Object pivot, *piv = &pivot;
	struct Object pendulum, *pen = &pendulum;
	struct Object base, *b = &base;
	struct Object buckets, *bucket = &buckets;	
	// Initialize attributes of carnival objects
	piv->x_pos = xcenter;
	piv->y_pos = 20;
	piv->speed = .3;
	piv->size = 15;
	piv->theta = 0;

	pen->xspeed = 1.5;
	pen->yspeed = 1.5;

	pen->size = 200;

	b->size = 100;
	b->theta = 0;
	b->speed = 1;

	bucket->size = 25;

	gfx_open( xsize, ysize, "Carnival" );
	
	while( c != 'q' ) {
		// Clear window and set background color and elements
		gfx_clear();
		gfx_clear_color( 102, 255, 255 );
		gfx_color( 0, 255, 0 );
		gfx_fill_rectangle( 0, ysize - 60, xsize, 60 );
		gfx_color( 0, 0, 0);	
		gfx_line( 0, 20, xsize, 20);
		// Draw pivot object
		draw_pivot( piv, pen, b, bucket, xsize, ysize, xcenter, deltat );
		// Update theta values for objects to allow for movement
		piv->theta = piv->theta + piv->speed*deltat;
		pen->theta = pen->theta + pen->yspeed*deltat;
		b->theta = b->theta + b->speed*deltat;	

		gfx_flush();
		usleep(wait);
		if( gfx_event_waiting()) c = gfx_wait();	
		if( c == 'p' ) c = gfx_wait();
	}
}

double new_v( void ) {
	int v = rand() % 400 + 1;
	v = v*(pow(-1,(rand() & 2) + 1) );
	return v;
}
void draw_pivot( struct Object *piv, struct Object *pen, struct Object *b, struct Object *bucket, int xsize, int ysize, int xcenter, double deltat ) {
	// Determine position of pivot, without getting within 200 pixels of the edge
	piv->x_pos = xcenter + (xcenter-200)*sin(piv->theta);
	// Draw pendulum based on the position of the pivot
	draw_pendulum( pen, b, bucket, piv->x_pos, piv->y_pos, xsize, ysize, deltat );
	gfx_color( 0, 102, 0);
	gfx_fill_arc( piv->x_pos - piv->size, piv->y_pos - piv->size, 2*piv->size, 2*piv->size, 0, 360 );
}

void draw_pendulum( struct Object *pen, struct Object *b, struct Object *bucket, int piv_xpos, int piv_ypos, int xsize, int ysize, double deltat ) {
	gfx_color( 255, 0, 0);
	// Determine position of the bottom of the pendulum, making sure that the structure
	// does not go outside the window
	pen->x_pos = piv_xpos + pen->xspeed*deltat + 200*cos(pen->theta);;
	pen->y_pos = pen->size*sin(pen->theta) + 180;

	// (b->size + 2*bucket->size) is roughly the distance fromt the center of the 
	// square to the edge of a bucket at its widest, so it is used to make sure the
	// structure doesn't go outside the window
	if( pen->x_pos > xsize-(b->size + 2*bucket->size) ) {
		pen->x_pos = xsize-(b->size + 2*bucket->size);
		pen->xspeed = -1*pen->xspeed;
	}
	else if( pen->x_pos < (b->size + 2*bucket->size ) ) {
		pen->x_pos = (b->size + 2*bucket->size );
		pen->xspeed = -1*pen->xspeed;
	}
	if( pen->y_pos < piv_ypos + (b->size + 2*bucket->size)) {
		pen->y_pos = piv_ypos + (b->size + 2*bucket->size);
		pen->yspeed = -1*pen->yspeed;
	}
	else if( pen->y_pos > ysize - (b->size + 2*bucket->size + 100) ) {
		pen->y_pos = ysize - (b->size + 2*bucket->size + 100);
		pen->yspeed = -1*pen->yspeed;
	}
	gfx_line( piv_xpos, piv_ypos, pen->x_pos, pen->y_pos );
	// Draw square based on the position of the pendulum
	draw_base( b, bucket, pen->x_pos, pen->y_pos );
}

void draw_base( struct Object *b, struct Object *bucket, int pen_xpos, int pen_ypos ) {
	int i;
	int x1, y1, x2, y2;
	int corners[4][2];
	for( i = 0; i < 4; i++ ) {
		// Determines the two coordinates to draw the line at, and stores them
		// in order to draw the buckets after.
		x1 = pen_xpos + b->size*cos(b->theta);
		y1 = pen_ypos + b->size*sin(b->theta);
		b->x_pos = x1;
		b->y_pos = y2;
		b->theta += M_PI/2;
		x2 = pen_xpos + b->size*cos(b->theta);
		y2 = pen_ypos + b->size*sin(b->theta);
		b->x_pos = x2;
		b->y_pos = y2;	
		corners[i][0] = x2;
		corners[i][1] = y2;
		gfx_color( 0, 0, 153 );
		gfx_line( pen_xpos, pen_ypos, x2, y2 );
		gfx_line( x1, y1, x2, y2 );	
	}
	int j;
	for( j = 0; j < 4; j++ ) {
		draw_buckets( bucket, corners[j][0], corners[j][1] );
	}
	
}
void draw_buckets( struct Object *bucket, int b_xpos, int b_ypos ) {
	gfx_color( 255, 128, 0 );
	gfx_fill_rectangle( b_xpos - bucket->size, b_ypos - .5*bucket->size, 2*bucket->size, bucket->size );
}
