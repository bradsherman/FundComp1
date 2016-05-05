// Brad Sherman
// Fundamentals of Computing 1
// Final Project
// Functions for Donkey Kong

#include <stdio.h>
#include "gfx5.h"
#include "gfxe.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "finalfunc.h"

double returnHeight( struct Mario_s *m, int xsize, int ysize, int railWidth, double railAngle ) {
	// Returns the proper height for mario to return to when he jumps
	switch( m->level) {
		case 1:
			if( m->xpos < xsize/2 ) return (ysize-railWidth*2-.5*m->height);
			else return (ysize-railWidth*2-.5*m->height-(m->xpos-(xsize/2))*tan(railAngle));
			break;
		case 2:
			return (ysize-railWidth*11-.5*m->height+(m->xpos)*tan(railAngle));
			break;
		case 3:
			return (ysize-railWidth*17-.5*m->height-(m->xpos-railWidth*3)*tan(railAngle));
			break;
		case 4:
			return (ysize-railWidth*25-.5*m->height);
			break;
		default:
			return 0;
			break;
	}
}
void decreaseLives( struct Mario_s *m, struct Barrel_s *Barrels, int xsize, int ysize, int maxBarrels ) { 
	// Reset Mario and the barrels to start a new life
	gfx_color( 0, 255, 0);
	int length = gfx_textpixelwidth( "YOU DIED. LIVES LEFT: 3", "lucidasanstypewriter-bold-24");
	gfx_changefont( "lucidasanstypewriter-bold-24");
	char buffer[30];
	snprintf( buffer, 30, "YOU DIED. LIVES LEFT: %d",m->lives );
	gfx_text( xsize/2-.5*length, ysize/2-60, buffer );
	m->xpos = m->xstart;
	m->ypos = m->ystart;
	m->level = 1;
	m->falling = 0;
	int j;
	for( j = 0; j < maxBarrels; j++ ) {
		Barrels[j].xpos = Barrels[j].xstart;
		Barrels[j].ypos = Barrels[j].ystart;
		Barrels[j].level = 4;
		Barrels[j].falling = 0;
	}
	gfx_flush();
	usleep(3000000);
}
void loseScreen( int xsize, int ysize ) {
	// Notify player that he/she has lost
	gfx_color( 0, 255, 0);
	int length = gfx_textpixelwidth( "GAME OVER", "lucidasanstypewriter-bold-24" );
	gfx_changefont( "lucidasanstypewriter-bold-24");
	gfx_text( xsize/2-.5*length, ysize/2-60, "GAME OVER" );
	gfx_flush();
	usleep(3000000);
}
void winScreen( int xsize, int ysize ) {
	// Notify player that he/she has won
	gfx_color( 0, 255, 0 );
	int length = gfx_textpixelwidth( "Congratulations! You saved Peach!", "lucidasanstypewriter-bold-12");
	gfx_changefont( "lucidasanstypewriter-bold-12");
	gfx_text( xsize/2-.5*length, ysize/2-60, "Congratulations! You saved Peach!");
	gfx_flush();
	usleep(3000000);
}
char pauseGame( int xsize, int ysize, char c ) {
	// Notify player that he/she has paused the game
	gfx_color( 0, 255, 0 );
	gfx_changefont( "lucidasanstypewriter-bold-12");
	int length = gfx_textpixelwidth( "Paused, press any button to unpause (besides p)", "lucidasanstypewriter-bold-12");
	gfx_text( xsize/2-.5*length, ysize/2-30, "Paused, press any button to unpause (besides p)" );
	gfx_flush();
	while( c == 'p' )c = gfx_wait();
	return c;
}
void drawmarioHeads( int xsize, int numLives ) {
	// Draw mario heads in upper right corner corresponding
	// to number of lives left
	int i;
	for( i = 0; i < numLives; i++ ) {
		drawmarioHead( xsize-15-15*i, 25, 1 );
	}
}
void initializePeach( struct Peach_s *peach, int xsize, int ysize, int ladderWidth, int railWidth ) {
	peach->orientation = 1;
	peach->height = 31;
	peach->width =16;
	peach->xpos = xsize/2-.5*ladderWidth-.5*peach->width;
	peach->ypos = ysize-31*railWidth-.5*peach->height;
}
void initializeBarrels( struct Barrel_s * Barrels, struct Kong_s * k, int ysize, int maxBarrels, int railWidth, double railAngle, double deltat ) {
	int j;
	for( j = 0; j < maxBarrels; j++ ) {
		Barrels[j].vx = 225;
		Barrels[j].radius = 10;
		Barrels[j].falling = 0;
		Barrels[j].level = 4;
		Barrels[j].xstart = 1.5*k->width+Barrels[j].radius+1;
		Barrels[j].ystart = ysize-25*railWidth-Barrels[j].radius;
		Barrels[j].xpos = Barrels[j].xstart;
		Barrels[j].ypos = Barrels[j].ystart;
		Barrels[j].dx = Barrels[j].vx*deltat;
		Barrels[j].dy = Barrels[j].dx*sin(railAngle);
	}
}
void initializeMario( struct Mario_s * m, int xsize, int ysize, int railWidth ) {
	m->xstart = 2*railWidth;
	m->ystart = ysize-2*railWidth-10;
	m->xpos = m->xstart;
	m->ypos = m->ystart;
	m->vx = 300;
	m->orientation = 1;
	m->width = 15*abs(m->orientation);
	m->height = 19*abs(m->orientation);
	m->level = 1;
	m->falling = 0;
	m->lives = 3;
	m->jump = 0;
	m->onLadder = 0;
}
void initializeKong( struct Kong_s * k, int railWidth, int ysize ) {
	k->width = 38;
	k->height = 32;
	k->xpos = k->width;
	k->ypos = ysize-railWidth*25-.5*k->height;
	k->orientation = 1;	
}
char startScreen( int xsize ) {
	// Draw start screen, telling user how to play
	char c;
	// Get Logo
	char* dkLogo = readRAWImage("dk", 0 );

	// Start Screen
	gfx_clear_color( 255, 255, 255 );
	gfx_clear();
	printRAWImage( 50, 50, 500, 333, dkLogo );
	gfx_color( 0, 0, 255 );
	gfx_changefont("lucidasanstypewriter-bold-24");
	int length = gfx_textpixelwidth( "INSTRUCTIONS", "lucidasanstypewriter-bold-24");
	gfx_text( xsize/2 - .5*length, 425, "INSTRUCTIONS" );
	length = gfx_textpixelwidth( "Arrow keys to move", "lucidasanstypewriter-bold-24");
	gfx_text( xsize/2 - .5*length, 450, "Arrow keys to move");
	length = gfx_textpixelwidth( "Spacebar to jump", "lucidasanstypewriter-bold-24");
	gfx_text( xsize/2 - .5*length, 475, "Spacebar to jump");
	length = gfx_textpixelwidth( "Press 'p' to pause", "lucidasanstypewriter-bold-24");
	gfx_text( xsize/2 - .5*length, 500, "Press 'p' to pause");
	length = gfx_textpixelwidth( "Press 'q' to quit", "lucidasanstypewriter-bold-24");
	gfx_text( xsize/2 - .5*length, 525, "Press 'q' to quit");
	length = gfx_textpixelwidth( "Press 's' to start", "lucidasanstypewriter-bold-24");
	gfx_text( xsize/2 - .5*length, 550, "Press 's' to start!");
	length = gfx_textpixelwidth( "Avoid Donkey Kong's barrels to save Peach!", "lucidasanstypewriter-bold-24");
	gfx_text( xsize/2 -.5*length, 600, "Avoid Donkey Kong's barrels to save Peach!");
	gfx_changefont( "lucidasanstypewriter-bold-18" );
	length = gfx_textpixelwidth( "Made by: Brad Sherman", "lucidasanstypewriter-bold-18");
	gfx_text( xsize/2 - .5*length, 650, "Made by: Brad Sherman" );
	while( c != 's' && c != 'q' ) {
		if( gfx_event_waiting() ) c = gfx_wait();
	}
	return c;
}	
int checkCollision( struct Mario_s *m, struct Barrel_s b, int numBarrels ) {
	// Check for collision between mario and any of the barrels
	int i;
	for( i = 0; i < numBarrels; i++ ) {
		if( m->xpos+.5*m->width > b.xpos-b.radius && m->xpos+.5*m->width < b.xpos+b.radius && m->ypos+.5*m->height > b.ypos-b.radius && m->ypos+.5*m->height < b.ypos+b.radius) return 1;
		if( m->xpos-.5*m->width < b.xpos+b.radius && m->xpos+.5*m->width > b.xpos-b.radius && m->ypos+.5*m->height > b.ypos-b.radius && m->ypos+.5*m->height < b.ypos+b.radius) return 1;
		if( m->xpos+.5*m->width > b.xpos-b.radius && m->xpos+.5*m->width < b.xpos+b.radius && m->ypos-.5*m->height < b.ypos+b.radius && m->ypos-.5*m->height > b.ypos-b.radius) return 1;
		if( m->xpos-.5*m->width < b.xpos+b.radius && m->xpos+.5*m->width > b.xpos-b.radius && m->ypos-.5*m->height < b.ypos+b.radius && m->ypos-.5*m->height > b.ypos-b.radius) return 1;
		
		else return 0;
	}
	return 0;	
}
void drawBarrels( struct Barrel_s *b, int numBarrels, double xsize, double ysize, int railWidth, double railAngle, double deltat, int *t ) {
	// Draw all the barrels on the screen
	int i;
	for( i = 0; i < numBarrels; i++) {
		if( b[i].falling ) barrelFall( b, deltat, xsize, ysize, railWidth, railAngle, t, i );	
		else {
			switch( b[i].level ) {
				case 1:
					if( b[i].xpos+b[i].radius < 0 ) {
						b[i].xpos = b[i].xstart;
						b[i].ypos = b[i].ystart;
						b[i].level = 4;
					}else if( b[i].ypos+b[i].radius < ysize-2*railWidth ) {
						b[i].dy = b[i].dx*sin(railAngle);
						b[i].xpos = b[i].xpos - b[i].dx;
						b[i].ypos = b[i].ypos + b[i].dy;
					}else {
						b[i].xpos = b[i].xpos - b[i].dx;
						b[i].ypos = ysize-2*railWidth-b[i].radius;
					}break;
				case 2:
					if( b[i].xpos-b[i].radius > xsize-3*railWidth ) b[i].falling = 1;
					else {
						b[i].dy = b[i].dx*sin(railAngle);
						b[i].ypos = b[i].ypos + b[i].dy;
						b[i].xpos = b[i].xpos + b[i].dx;
					}break;
				case 3:
					if( b[i].xpos+b[i].radius < 3*railWidth ) b[i].falling = 1;
					else {
						b[i].dy = b[i].dx*sin(railAngle);
						b[i].ypos = b[i].ypos + b[i].dy;
						b[i].xpos = b[i].xpos - b[i].dx;
					}break;
				case 4:
					if( b[i].xpos-b[i].radius > xsize-railWidth*3 ) b[i].falling = 1;
					else {
						b[i].xpos = b[i].xpos + b[i].dx;
					}break;
			}
		}
		drawBarrel( b[i] );
	}
}
void drawBarrel( struct Barrel_s b ) {
	// Draw singular barrel
	gfx_color( 202, 94, 0 );
	gfx_fill_arc( b.xpos-b.radius, b.ypos-b.radius, 2*b.radius, 2*b.radius, 0, 360 );   
}
void barrelFall( struct Barrel_s* b, double deltat, double xsize, double ysize, int railWidth, double railAngle, int *t, int i ) {
	// Describe movement of a barrel as it falls off of an edge
	b[i].vy = 9.8*(*t);
	b[i].dy = b[i].vy*deltat;
	b[i].ypos = b[i].ypos + b[i].dy;
	(*t)++;
	switch( b[i].level ) {
		case 2:
			if( b[i].ypos+(b[i].radius) > (ysize-railWidth*2-(xsize/2-(xsize-b[i].xpos))*tan(railAngle) ) ) {
				b[i].ypos = -1+ysize-railWidth*2-(xsize/2-(xsize-b[i].xpos))*tan(railAngle)-b[i].radius;
				b[i].falling = 0;
				b[i].level = 1;
				*t = 0;
			}break;
		case 3:
			if( b[i].ypos+b[i].radius > (ysize-railWidth*11+(b[i].xpos)*tan(railAngle)) ) {
				b[i].ypos = -1-b[i].radius+ysize-railWidth*11+(b[i].xpos)*tan(railAngle);
				b[i].falling = 0;
				b[i].level = 2;
				*t = 0;
			}break;
		case 4:
			if( b[i].ypos+b[i].radius > (ysize-railWidth*17-(b[i].xpos-3*railWidth)*tan(railAngle)) ) {
				b[i].ypos = -1-b[i].radius+(ysize-railWidth*17-(b[i].xpos-3*railWidth)*tan(railAngle));
				b[i].falling = 0;
				b[i].level = 3;
				*t = 0;
			}
			break;
	}
	
}
void checkFall( struct Mario_s * m, double deltat, int *t, int xsize, int ysize, int railWidth, double railAngle) {
	// Describe movement of mario as he falls off of an edge
	m->vy = 9.8*(*t);
	m->dy = m->vy*deltat;
	m->ypos = m->ypos + m->dy;
	(*t)++;
	switch( m->level ) {
		case 2:
			if( m->ypos+(.5*m->height) > (ysize-railWidth*2-(xsize/2-(xsize-m->xpos))*tan(railAngle) ) ) {
				m->ypos = -1+ysize-railWidth*2-(xsize/2-(xsize-m->xpos))*tan(railAngle)-(.5*m->height);
				m->falling = 0;
				m->level = 1;
				*t = 0;
			}
			break;
		case 3:
			if( m->ypos+(.5*m->height) > (ysize-railWidth*11+(m->xpos)*tan(railAngle)) ) {
				m->ypos = -1-(.5*m->height)+ysize-railWidth*11+(m->xpos)*tan(railAngle);
				m->falling = 0;
				m->level = 2;
				*t = 0;
			}
			break;
		case 4:
			if( m->ypos+(.5*m->height) > (ysize-railWidth*17-(m->xpos-3*railWidth)*tan(railAngle)) ) {
				m->ypos = -1-(.5*m->height)+(ysize-railWidth*17-(m->xpos-3*railWidth)*tan(railAngle));
				m->falling = 0;
				m->level = 3;
				*t = 0;
			}
			break;
	}
}
void checkPosition( struct Mario_s * m, double xsize, double ysize, double railAngle, double railWidth, double ladderWidth, int dir ) {
	// Checks to see where Mario is
	// return 0 for no ladder
	// return 1 for up ladder
	// return 2 for down ladder

	// dir 1 means mario is trying to go up
	if( dir == 1 ) {
		switch( m->level ) {
			case 1:
				if( (m->xpos-(.5*m->width) > xsize-(railWidth*6)) && (m->xpos+(.5*m->width) < xsize-(railWidth*6)+ladderWidth) ) m->onLadder = 1;
				else m->onLadder = 0;
				break;
			case 2:
				if( (m->xpos-(.5*m->width) > railWidth*6) && (m->xpos+(.5*m->width) < (railWidth*6)+ladderWidth) ) m->onLadder = 1;
				else if( (m->xpos-(.5*m->width) > xsize-(railWidth*6)) && (m->xpos+(.5*m->width) < xsize-(railWidth*6)+ladderWidth && m->ypos+.5*m->height > -1+(ysize-railWidth*11+(m->xpos)*tan(railAngle)))) m->onLadder = 1;
				else m->onLadder = 0;
				break;
			case 3:
				if( (m->xpos-(.5*m->width) > xsize-(railWidth*6)) && (m->xpos+(.5*m->width) < xsize-(railWidth*6)+ladderWidth) ) m->onLadder = 1;
				else if( (m->xpos-(.5*m->width) > railWidth*6) && (m->xpos+(.5*m->width) < (railWidth*6)+ladderWidth) && m->ypos+.5*m->height > -1+ysize-railWidth*17-(m->xpos-3*railWidth)*tan(railAngle)) m->onLadder = 1;
				else m->onLadder = 0;
				break;
			case 4:
				if( m->xpos-.5*m->width > xsize/2-.5*ladderWidth && m->xpos+.5*m->width < xsize/2+.5*ladderWidth ) m->onLadder = 1;
				else if((m->xpos-(.5*m->width) > xsize-(railWidth*6)) && (m->xpos+(.5*m->width) < xsize-(railWidth*6)+ladderWidth) && m->ypos+.5*m->height > ysize-railWidth*25) m->onLadder = 1;
				else m->onLadder = 0;
				break;
			default:
				m->onLadder = 0;
				break;
		}
	// dir 2 means mario is trying to go down
	}else if( dir == 2 ) {
		switch( m->level ) {
			case 1:
				if( (m->xpos-(.5*m->width) > xsize-(railWidth*6)) && (m->xpos+(.5*m->width) < xsize-(railWidth*6)+ladderWidth) && m->ypos+(.5*m->height) < -1+(ysize-2*railWidth-(m->xpos-xsize/2)*tan(railAngle))  ) m->onLadder = 2;
				else m->onLadder = 0;
				break;
			case 2:
				if( (m->xpos-(.5*m->width) > xsize-(railWidth*6)) && (m->xpos+(.5*m->width) < xsize-(railWidth*6)+ladderWidth) ) m->onLadder = 2;
				else if( (m->xpos-(.5*m->width) > railWidth*6) && (m->xpos+(.5*m->width) < (railWidth*6)+ladderWidth)&& m->ypos+(.5*m->height) < -1+(ysize-11*railWidth+(m->xpos)*tan(railAngle))) m->onLadder = 2;
				else m->onLadder = 0;
				break;
			case 3:
				if( (m->xpos-(.5*m->width) > railWidth*6) && (m->xpos+(.5*m->width) < (railWidth*6)+ladderWidth) ) m->onLadder = 2; 
				else if( (m->xpos-(.5*m->width) > xsize-(railWidth*6)) && (m->xpos+(.5*m->width) < xsize-(railWidth*6)+ladderWidth) && m->ypos+(.5*m->height) < -1+(ysize-railWidth*17-(m->xpos-3*railWidth)*tan(railAngle))) m->onLadder = 2;
				else m->onLadder = 0;
				break;
			case 4:
				if( (m->xpos-(.5*m->width) > xsize-(railWidth*6)) && (m->xpos+(.5*m->width) < xsize-(railWidth*6)+ladderWidth) ) m->onLadder = 2;
				else if( m->xpos-(.5*m->width) > xsize/4 && m->xpos-(.5*m->width) < 3*xsize/4 && m->ypos+.5*m->width < -1+ysize-railWidth*25 ) m->onLadder = 2;
				else m->onLadder = 0;
				break;
			default:
				m->onLadder = 0;
				break;
		}	
	}
	else m->onLadder = 0;
}	
void ladderMovement( struct Mario_s *m, int xsize, int ysize, double railWidth, double railAngle, double deltat ) {
	// Describe movement of mario on the ladders

	// Moving down a ladder
	if( m->onLadder == 2 ) {
		switch( m->level ) {
			case 1:
				if( m->ypos+(.5*m->height) < (ysize-railWidth*2-(xsize/2-(xsize-m->xpos))*tan(railAngle) ) ) {
					m->vy = 150;
					m->dy = m->vy*deltat;
					m->ypos = m->ypos + m->dy;  
				}break;
			case 2:
				if( m->ypos+(.5*m->height) > (ysize-railWidth*2-(xsize/2-(xsize-m->xpos))*tan(railAngle) ) ) {
					m->ypos = -1+ysize-railWidth*2-(xsize/2-(xsize-m->xpos))*tan(railAngle)-(.5*m->height);
					m->level = 1;
					return;
				}else if( m->ypos+(.5*m->height) < (ysize-railWidth*11+(m->xpos)*tan(railAngle))){
					m->vy = 150;
					m->dy = m->vy*deltat;
					m->ypos = m->ypos + m->dy;
				}else {
					m->vy = 150;
					m->dy = m->vy*deltat;
					m->ypos = m->ypos + m->dy;
				}break;
			case 3:
				if( m->ypos+(.5*m->height) > (ysize-railWidth*11+(m->xpos)*tan(railAngle)) ) {
					m->ypos = -1-(.5*m->height)+ysize-railWidth*11+(m->xpos)*tan(railAngle);
					m->level = 2;
					return;
				} else {
					m->vy = 150;
					m->dy = m->vy*deltat;
					m->ypos = m->ypos + m->dy;
				}break;
			case 4:
				if( m->ypos+(.5*m->height) > (ysize-railWidth*17-(m->xpos-3*railWidth)*tan(railAngle)) ) {
					m->ypos = -1-(.5*m->height)+(ysize-railWidth*17-(m->xpos-3*railWidth)*tan(railAngle));
					m->level = 3;
					return;
				}else {
					m->vy = 150;
					m->dy = m->vy*deltat;
					m->ypos = m->ypos + m->dy;
				}break;
		}
	// Moving up a ladder
	}else if( m->onLadder == 1 ) {
		switch( m->level ) {
			case 1:	
				if( m->ypos+.5*m->height < ysize-(railWidth*9)) {
					m->level = 2;
				}else {
					m->vy = 150;
					m->dy = m->vy*deltat;
					m->ypos = m->ypos - m->dy;
				}
				break;
			case 2:
				if( m->ypos+.5*m->height < ysize-(railWidth*17)-7) {
					m->level = 3;
					return;
				}else {
					m->vy = 150;
					m->dy = m->vy*deltat;
					m->ypos = m->ypos - m->dy;
				}
				break;
			case 3:
				if( m->ypos+.5*m->height < ysize-(railWidth*25) ) {
					m->level = 4;
					return;
				} else {
					m->vy = 150;
					m->dy = m->vy*deltat;
					m->ypos = m->ypos - m->dy;
				}
				break;
			case 4:
				if( m->ypos+.5*m->height < ysize-railWidth*31 ) {
					m->level = 5;
					return;
				}
				else if( m->ypos+.5*m->height > ysize-railWidth*25) {
					m->vy = 150;
					m->dy = m->vy*deltat;
					m->ypos = m->ypos - m->dy;
				}else {
					m->vy = 120;
					m->dy = m->vy*deltat;
					m->ypos = m->ypos - m->dy;
				}	
				break;
		}
	}	
}
		
void moveRight( struct Mario_s * m, int xsize, int ysize, double railAngle, int railWidth, double deltat ) {
	// Describes mario's movement as he moves right
	m->orientation = 1;
	if( m->jump ) return;
	if(m->xpos+m->width+m->dx > xsize ) return;
	else {
		switch( m->level ) {
			case 1:
				m->xpos = m->xpos + m->dx;
				if( m->xpos+m->width+m->dx > xsize/2) m->ypos = m->ypos - m->dy;
				break;
			case 2:
				if(m->xpos+m->dx-m->width> xsize-(railWidth*3))	m->falling = 1;
				else{
					m->xpos = m->xpos + m->dx;
					m->ypos = m->ypos + m->dy;
				}break;
			case 3:
				m->xpos = m->xpos + m->dx;
				m->ypos = m->ypos - m->dy;
				break;
			case 4:
				if( m->xpos-m->width+m->dx > xsize-railWidth*3 ) m->falling = 1;
				else m->xpos = m->xpos + m->dx;
				break;	
		}
	}
}
void moveLeft( struct Mario_s * m, int xsize, int railWidth ) {
	// Describes mario's movement as he moves left
	m->orientation = -1;
	if( m->jump ) return;
	if(m->xpos-m->width-m->dx < 0 ) return;
	else {
		switch( m->level ) {
			case 1:
				m->xpos = m->xpos - m->dx;
				if( m->xpos+m->width+m->dx > xsize/2) m->ypos = m->ypos + m->dy;
				break;
			case 2:
				m->xpos = m->xpos - m->dx;
				m->ypos = m->ypos - m->dy;
				break;
			case 3:
				if(m->xpos+m->width-m->dx < railWidth*3) m->falling = 1;
				else{
					m->xpos = m->xpos - m->dx;
					m->ypos = m->ypos + m->dy;
				}break;
			case 4:
				m->xpos = m->xpos - m->dx;
				break;
		
		}
	}
}
void drawRails( double xsize, double ysize, double railAngle, int railWidth ){
	// Throughout the program, the tops of the rails drawn in this function are
	// used as a barrier for mario's movement, which is why railWidth and 
	// railAngle appear in many other functions, so that mario's movement fits
	// within the bounds of these rails
	gfx_color( 255, 51, 72 );
	int i = 0;
	for( i = 0; i < railWidth; i++ ) {
		//Bottom Rail
		gfx_line( 0, ysize-railWidth-i, xsize/2, ysize-railWidth-i );
		gfx_line( xsize/2, ysize-railWidth-i, xsize, ysize-railWidth-(xsize/2)*tan(railAngle)-i);
	
		// Second Rail
		gfx_line( 0, ysize-railWidth*10-i, xsize-railWidth*3, ysize+(xsize-3*railWidth)*tan(railAngle)-railWidth*10-i );
	
		// Third Rail
		gfx_line( railWidth*3, ysize-railWidth*16-i, xsize, ysize-(xsize-3*railWidth)*tan(railAngle)-railWidth*16-i );

		// Fourth Rail 
		gfx_line( 0, ysize-railWidth*24-i, xsize-railWidth*3, ysize-railWidth*24-i );	
	
		// Top Rail
		gfx_line( xsize/4, ysize-railWidth*30-i, 3*xsize/4, ysize-railWidth*30-i);
	}	
}
void drawLadders( double xsize, double ysize, double railAngle, int railWidth, double ladderWidth ) {
	// Draw all of the ladders based on the positions of the rails

	gfx_color( 255, 255, 255 );
	// Bottom Ladder
	gfx_line( xsize-railWidth*6, ysize-2*railWidth-((xsize/2)-railWidth*6)*tan(railAngle), xsize-railWidth*6, ysize-railWidth*10+(xsize-railWidth*6)*tan(railAngle) );
	gfx_line( xsize-railWidth*6+ladderWidth, ysize-2*railWidth-((xsize/2)-railWidth*6+ladderWidth)*tan(railAngle), xsize-railWidth*6+ladderWidth, ysize-railWidth*10+(xsize-railWidth*6+ladderWidth)*tan(railAngle) );

	// Second Ladder
	gfx_line( railWidth*6, ysize-railWidth*11+(railWidth*6)*tan(railAngle), railWidth*6, ysize-railWidth*16-(railWidth*3)*tan(railAngle) );
	gfx_line( railWidth*6+ladderWidth, ysize-railWidth*11+(railWidth*6+ladderWidth)*tan(railAngle), railWidth*6+ladderWidth, ysize-railWidth*16-(railWidth*3+ladderWidth)*tan(railAngle) );
	
	// Third Ladder 
	gfx_line( xsize-railWidth*6, ysize-railWidth*17-(xsize-railWidth*9)*tan(railAngle), xsize-railWidth*6, ysize-railWidth*24 );
	gfx_line( xsize-railWidth*6+ladderWidth, ysize-railWidth*17-(xsize-railWidth*9+ladderWidth)*tan(railAngle), xsize-railWidth*6+ladderWidth, ysize-railWidth*24 );

	// Fourth Ladder
	gfx_line( xsize/2-.5*ladderWidth, ysize-railWidth*24, xsize/2-.5*ladderWidth, ysize-railWidth*30 );
	gfx_line( xsize/2+.5*ladderWidth, ysize-railWidth*24, xsize/2+.5*ladderWidth, ysize-railWidth*30 );

	// Draw Rungs
	int i;
	for( i = 0; i < 6; i++ ) {
		gfx_line( xsize-railWidth*6, ysize-railWidth*(3+i), xsize-railWidth*6+ladderWidth, ysize-railWidth*(3+i) );
		gfx_line( railWidth*6, ysize-railWidth*(11+i), railWidth*6+ladderWidth, ysize-railWidth*(11+i) );
		gfx_line( xsize-railWidth*6, ysize-railWidth*(19+i), xsize-railWidth*6+ladderWidth, ysize-railWidth*(19+i) );
		gfx_line( xsize/2-.5*ladderWidth, ysize-railWidth*(25+i), xsize/2+.5*ladderWidth, ysize-railWidth*(25+i) );
	}
}
void drawPeach( int x, int y, int o ) {
	// Peach is 31 Pixels tall and 16 pixels wide
	// dark pink
	gfx_color( 209, 0, 153 );
	gfx_point( x-o*7, y+9);
	gfx_point( x-o*7, y+10);
	gfx_point( x-o*7, y+11);
	gfx_point( x-o*7, y+12);
	gfx_point( x-o*7, y+13);
	gfx_point( x-o*7, y+14);
	gfx_point( x-o*7, y-1);
	gfx_point( x-o*7, y);
	gfx_point( x-o*7, y+1);
	gfx_point( x-o*6, y+7);
	gfx_point( x-o*6, y+8);
	gfx_point( x-o*6, y+14);
	gfx_point( x-o*6, y+15);
	gfx_point( x-o*5, y-2);
	gfx_point( x-o*5, y+1);
	gfx_point( x-o*5, y+5);
	gfx_point( x-o*5, y+6);
	gfx_point( x-o*5, y+15);
	gfx_point( x-o*4, y-3);
	gfx_point( x-o*4, y+1);
	gfx_point( x-o*4, y+5);
	gfx_point( x-o*4, y+11);
	gfx_point( x-o*4, y+12);
	gfx_point( x-o*4, y+13);
	gfx_point( x-o*4, y+14);
	gfx_point( x-o*4, y+15);
	gfx_point( x-o*3, y-3);
	gfx_point( x-o*3, y-2);
	gfx_point( x-o*3, y-1);
	gfx_point( x-o*3, y);
	gfx_point( x-o*3, y+7);
	gfx_point( x-o*3, y+14);
	gfx_point( x-o*3, y+15);
	gfx_point( x-o*2, y-3);
	gfx_point( x-o*2, y+1);
	gfx_point( x-o*2, y+8);
	gfx_point( x-o*2, y+15);
	gfx_point( x-o*1, y-2);
	gfx_point( x-o*1, y+3);
	gfx_point( x-o*1, y+9);
	gfx_point( x-o*1, y+15);
	gfx_point( x, y-1);
	gfx_point( x, y+3);
	gfx_point( x, y+8);
	gfx_point( x, y+15);
	gfx_point( x+o*8, y+9);
	gfx_point( x+o*8, y+10);
	gfx_point( x+o*8, y+11);
	gfx_point( x+o*8, y+12);
	gfx_point( x+o*8, y+13);
	gfx_point( x+o*8, y+14);
	gfx_point( x+o*8, y-1);
	gfx_point( x+o*8, y);
	gfx_point( x+o*8, y+1);
	gfx_point( x+o*7, y+7);
	gfx_point( x+o*7, y+8);
	gfx_point( x+o*7, y+14);
	gfx_point( x+o*7, y+15);
	gfx_point( x+o*6, y-2);
	gfx_point( x+o*6, y+1);
	gfx_point( x+o*6, y+5);
	gfx_point( x+o*6, y+6);
	gfx_point( x+o*6, y+15);
	gfx_point( x+o*5, y-3);
	gfx_point( x+o*5, y+1);
	gfx_point( x+o*5, y+5);
	gfx_point( x+o*5, y+11);
	gfx_point( x+o*5, y+12);
	gfx_point( x+o*5, y+13);
	gfx_point( x+o*5, y+14);
	gfx_point( x+o*5, y+15);
	gfx_point( x+o*4, y-3);
	gfx_point( x+o*4, y-2);
	gfx_point( x+o*4, y-1);
	gfx_point( x+o*4, y);
	gfx_point( x+o*4, y+7);
	gfx_point( x+o*4, y+14);
	gfx_point( x+o*4, y+15);
	gfx_point( x+o*3, y-3);
	gfx_point( x+o*3, y+1);
	gfx_point( x+o*3, y+8);
	gfx_point( x+o*3, y+15);
	gfx_point( x+o*2, y-2);
	gfx_point( x+o*2, y+3);
	gfx_point( x+o*2, y+9);
	gfx_point( x+o*2, y+15);
	gfx_point( x+o*1, y-1);
	gfx_point( x+o*1, y+3);
	gfx_point( x+o*1, y+8);
	gfx_point( x+o*1, y+15);
		
	// Light pink
	gfx_color( 255, 117, 219 );
	gfx_point( x-o*6, y+9);
	gfx_point( x-o*6, y+13);
	gfx_point( x-o*5, y);
	gfx_point( x-o*5, y+7);
	gfx_point( x-o*5, y+11);
	gfx_point( x-o*5, y+12);
	gfx_point( x-o*5, y+13);
	gfx_point( x-o*5, y+14);
	gfx_point( x-o*4, y-1);
	gfx_point( x-o*4, y);
	gfx_point( x-o*4, y+6);
	gfx_point( x-o*4, y+7);
	gfx_point( x-o*4, y+8);
	gfx_point( x-o*4, y+9);
	gfx_point( x-o*4, y+10);
	gfx_point( x-o*3, y+8);
	gfx_point( x-o*3, y+9);
	gfx_point( x-o*3, y+10);
	gfx_point( x-o*3, y+11);
	gfx_point( x-o*3, y+12);
	gfx_point( x-o*3, y+13);
	gfx_point( x-o*2, y-2);
	gfx_point( x-o*2, y);
	gfx_point( x-o*2, y+9);
	gfx_point( x-o*2, y+13);
	gfx_point( x-o*2, y+14);
	gfx_point( x-o*1, y-1);
	gfx_point( x-o*1, y+1);
	gfx_point( x-o*1, y+10);
	gfx_point( x-o*1, y+14);
	gfx_point( x, y+1);
	gfx_point( x, y+4);
	gfx_point( x, y+9);
	gfx_point( x, y+10);
	gfx_point( x, y+11);
	gfx_point( x+o*7, y+9);
	gfx_point( x+o*7, y+13);
	gfx_point( x+o*6, y);
	gfx_point( x+o*6, y+7);
	gfx_point( x+o*6, y+11);
	gfx_point( x+o*6, y+12);
	gfx_point( x+o*6, y+13);
	gfx_point( x+o*6, y+14);
	gfx_point( x+o*5, y-1);
	gfx_point( x+o*5, y);
	gfx_point( x+o*5, y+6);
	gfx_point( x+o*5, y+7);
	gfx_point( x+o*5, y+8);
	gfx_point( x+o*5, y+9);
	gfx_point( x+o*5, y+10);
	gfx_point( x+o*4, y+8);
	gfx_point( x+o*4, y+9);
	gfx_point( x+o*4, y+10);
	gfx_point( x+o*4, y+11);
	gfx_point( x+o*4, y+12);
	gfx_point( x+o*4, y+13);
	gfx_point( x+o*3, y-2);
	gfx_point( x+o*3, y);
	gfx_point( x+o*3, y+9);
	gfx_point( x+o*3, y+13);
	gfx_point( x+o*3, y+14);
	gfx_point( x+o*2, y-1);
	gfx_point( x+o*2, y+1);
	gfx_point( x+o*2, y+10);
	gfx_point( x+o*2, y+14);
	gfx_point( x+o*1, y+1);
	gfx_point( x+o*1, y+4);
	gfx_point( x+o*1, y+9);
	gfx_point( x+o*1, y+10);
	gfx_point( x+o*1, y+11);
	
	// White-ish Pink
	gfx_color( 255, 196, 240 );
	gfx_point( x-o*6, y+10);
	gfx_point( x-o*6, y+11);
	gfx_point( x-o*6, y+12);
	gfx_point( x-o*5, y-1);
	gfx_point( x-o*5, y+8);
	gfx_point( x-o*5, y+9);
	gfx_point( x-o*5, y+10);
	gfx_point( x-o*4, y-2);
	gfx_point( x-o*2, y-1);
	gfx_point( x-o*2, y+10);
	gfx_point( x-o*2, y+11);
	gfx_point( x-o*2, y+12);
	gfx_point( x-o*1, y);
	gfx_point( x-o*1, y+2);
	gfx_point( x-o*1, y+11);
	gfx_point( x-o*1, y+12);
	gfx_point( x-o*1, y+13);
	gfx_point( x, y);
	gfx_point( x, y+12);
	gfx_point( x, y+13);
	gfx_point( x, y+14);
	gfx_point( x+o*7, y+10);
	gfx_point( x+o*7, y+11);
	gfx_point( x+o*7, y+12);
	gfx_point( x+o*6, y-1);
	gfx_point( x+o*6, y+8);
	gfx_point( x+o*6, y+9);
	gfx_point( x+o*6, y+10);
	gfx_point( x+o*5, y-2);
	gfx_point( x+o*3, y-1);
	gfx_point( x+o*3, y+10);
	gfx_point( x+o*3, y+11);
	gfx_point( x+o*3, y+12);
	gfx_point( x+o*2, y);
	gfx_point( x+o*2, y+2);
	gfx_point( x+o*2, y+11);
	gfx_point( x+o*2, y+12);
	gfx_point( x+o*2, y+13);
	gfx_point( x+o*1, y);
	gfx_point( x+o*1, y+12);
	gfx_point( x+o*1, y+13);
	gfx_point( x+o*1, y+14);

	// Hair
	gfx_color( 235, 196, 0);
	gfx_point( x-o*7, y-1);
	gfx_point( x-o*7, y-2);
	gfx_point( x-o*7, y-3);
	gfx_point( x-o*6, y-2);
	gfx_point( x-o*6, y-4);
	gfx_point( x-o*6, y-5);
	gfx_point( x-o*6, y-9);
	gfx_point( x-o*6, y-10);
	gfx_point( x-o*5, y-3);
	gfx_point( x-o*5, y-6);
	gfx_point( x-o*5, y-7);
	gfx_point( x-o*5, y-8);
	gfx_point( x-o*5, y-9);
	gfx_point( x-o*4, y-4);
	gfx_point( x-o*4, y-6);
	gfx_point( x-o*4, y-7);
	gfx_point( x-o*4, y-8);
	gfx_point( x-o*4, y-10);
	gfx_point( x-o*4, y-11);
	gfx_point( x-o*4, y-12);
	gfx_point( x-o*3, y-4);
	gfx_point( x-o*3, y-9);
	gfx_point( x-o*3, y-13);
	gfx_point( x-o*2, y-10);
	gfx_point( x-o*2, y-12);
	gfx_point( x-o*1, y-10);
	gfx_point( x-o*1, y-11);
	gfx_point( x, y-9);
	gfx_point( x, y-11);
	gfx_point( x+o*8, y-1);
	gfx_point( x+o*8, y-2);
	gfx_point( x+o*8, y-3);
	gfx_point( x+o*7, y-2);
	gfx_point( x+o*7, y-4);
	gfx_point( x+o*7, y-5);
	gfx_point( x+o*7, y-9);
	gfx_point( x+o*7, y-10);
	gfx_point( x+o*6, y-3);
	gfx_point( x+o*6, y-6);
	gfx_point( x+o*6, y-7);
	gfx_point( x+o*6, y-8);
	gfx_point( x+o*6, y-9);
	gfx_point( x+o*5, y-4);
	gfx_point( x+o*5, y-6);
	gfx_point( x+o*5, y-7);
	gfx_point( x+o*5, y-8);
	gfx_point( x+o*5, y-10);
	gfx_point( x+o*5, y-11);
	gfx_point( x+o*5, y-12);
	gfx_point( x+o*4, y-4);
	gfx_point( x+o*4, y-9);
	gfx_point( x+o*4, y-13);
	gfx_point( x+o*3, y-10);
	gfx_point( x+o*3, y-12);
	gfx_point( x+o*2, y-10);
	gfx_point( x+o*2, y-11);
	gfx_point( x+o*1, y-9);
	gfx_point( x+o*1, y-11);
	//Lighter Yellow
	gfx_color( 255, 255, 7);
	gfx_point( x-o*6, y-3);
	gfx_point( x-o*5, y-4);
	gfx_point( x-o*5, y-5);
	gfx_point( x-o*4, y-5);
	gfx_point( x-o*4, y-8);
	gfx_point( x-o*3, y-9);
	gfx_point( x-o*3, y-10);
	gfx_point( x-o*3, y-11);
	gfx_point( x-o*2, y-10);
	gfx_point( x, y-9);
	gfx_point( x+o*7, y-3);
	gfx_point( x+o*6, y-4);
	gfx_point( x+o*6, y-5);
	gfx_point( x+o*5, y-5);
	gfx_point( x+o*5, y-8);
	gfx_point( x+o*4, y-9);
	gfx_point( x+o*4, y-10);
	gfx_point( x+o*4, y-11);
	gfx_point( x+o*3, y-10);
	gfx_point( x+o*1, y-9);

	// Face
	gfx_color( 255, 223, 115 );
	gfx_point( x-o*4, y+3);
	gfx_point( x-o*3, y+2);
	gfx_point( x-o*2, y+6);
	gfx_point( x-o*2, y-5);
	gfx_point( x-o*2, y-6);
	gfx_point( x-o*2, y-7);
	gfx_point( x-o*1, y+7);
	gfx_point( x-o*1, y-4);
	gfx_point( x-o*1, y-5);
	gfx_point( x-o*1, y-8);
	gfx_point( x, y-2);
	gfx_point( x, y-4);
	gfx_point( x, y-5);
	gfx_point( x, y-6);
	gfx_point( x, y-7);
	gfx_point( x+o*5, y+3);
	gfx_point( x+o*4, y+2);
	gfx_point( x+o*3, y+6);
	gfx_point( x+o*3, y-5);
	gfx_point( x+o*3, y-6);
	gfx_point( x+o*3, y-7);
	gfx_point( x+o*2, y+7);
	gfx_point( x+o*2, y-4);
	gfx_point( x+o*2, y-5);
	gfx_point( x+o*2, y-8);
	gfx_point( x+o*1, y-2);
	gfx_point( x+o*1, y-4);
	gfx_point( x+o*1, y-5);
	gfx_point( x+o*1, y-6);
	gfx_point( x+o*1, y-7);
	//Darker color
	gfx_color( 255, 125, 125 );
	gfx_point( x-o*4, y+2);
	gfx_point( x-o*3, y-5);
	gfx_point( x-o*3, y-6);
	gfx_point( x-o*3, y-7);
	gfx_point( x-o*3, y-8);
	gfx_point( x-o*2, y-4);
	gfx_point( x-o*2, y-9);
	gfx_point( x-o*1, y-3);
	gfx_point( x-o*1, y-9);
	gfx_point( x, y-3);
	gfx_point( x, y-8);
	gfx_point( x+o*5, y+2);
	gfx_point( x+o*4, y-5);
	gfx_point( x+o*4, y-6);
	gfx_point( x+o*4, y-7);
	gfx_point( x+o*4, y-8);
	gfx_point( x+o*3, y-4);
	gfx_point( x+o*3, y-9);
	gfx_point( x+o*2, y-3);
	gfx_point( x+o*2, y-9);
	gfx_point( x+o*1, y-3);
	gfx_point( x+o*1, y-8);
	
	// Crown and gloves
	gfx_color( 255, 255, 255 );
	gfx_point( x-o*3, y+3);
	gfx_point( x-o*3, y+4);
	gfx_point( x-o*2, y-13);
	gfx_point( x-o*2, y-14);
	gfx_point( x-o*2, y-15);
	gfx_point( x-o*2, y+4);
	gfx_point( x-o*2, y+5);
	gfx_point( x-o*1, y-12);
	gfx_point( x-o*1, y-13);
	gfx_point( x-o*1, y+5);
	gfx_point( x-o*1, y+6);
	gfx_point( x, y-12);
	gfx_point( x, y-14);
	gfx_point( x, y-15);
	gfx_point( x, y+2);
	gfx_point( x+o*4, y+3);
	gfx_point( x+o*4, y+4);
	gfx_point( x+o*3, y-13);
	gfx_point( x+o*3, y-14);
	gfx_point( x+o*3, y-15);
	gfx_point( x+o*3, y+4);
	gfx_point( x+o*3, y+5);
	gfx_point( x+o*2, y-12);
	gfx_point( x+o*2, y-13);
	gfx_point( x+o*2, y+5);
	gfx_point( x+o*2, y+6);
	gfx_point( x+o*1, y-12);
	gfx_point( x+o*1, y-14);
	gfx_point( x+o*1, y-15);
	gfx_point( x+o*1, y+2);
	
	// Crown Jewel
	gfx_color( 255, 0, 0);
	gfx_point( x, y-13);
	gfx_point( x+o*1, y-13);
	
	// Eyes
	gfx_color( 0, 0, 0);
	gfx_point( x-o*1, y-6);
	gfx_point( x-o*1, y-7);
	gfx_point( x+o*2, y-6);
	gfx_point( x+o*2, y-7);
	
	// Misc brown
	gfx_color( 107, 50, 0);
	gfx_point( x-o*5, y+2);
	gfx_point( x-o*5, y+3);
	gfx_point( x-o*4, y+4);
	gfx_point( x-o*3, y+1);
	gfx_point( x-o*3, y+5);
	gfx_point( x-o*3, y+6);
	gfx_point( x-o*2, y-8);
	gfx_point( x-o*2, y+2);
	gfx_point( x-o*2, y+3);
	gfx_point( x-o*2, y+7);
	gfx_point( x-o*1, y+4);
	gfx_point( x-o*1, y+8);
	gfx_point( x, y+5);
	gfx_point( x, y+6);
	gfx_point( x, y+7);
	gfx_point( x+o*6, y+2);
	gfx_point( x+o*6, y+3);
	gfx_point( x+o*5, y+4);
	gfx_point( x+o*4, y+1);
	gfx_point( x+o*4, y+5);
	gfx_point( x+o*4, y+6);
	gfx_point( x+o*3, y-8);
	gfx_point( x+o*3, y+2);
	gfx_point( x+o*3, y+3);
	gfx_point( x+o*3, y+7);
	gfx_point( x+o*2, y+4);
	gfx_point( x+o*2, y+8);
	gfx_point( x+o*1, y+5);
	gfx_point( x+o*1, y+6);
	gfx_point( x+o*1, y+7);
}	
void drawKong( int x, int y, int o ) {
	// Donkey Kong is 32 pixels tall and 38 pixels wide
	gfx_color( 153, 0, 0 );
	// dark brown
	gfx_point( x-o*19, y-3);
	gfx_point( x-o*19, y-2);
	gfx_point( x-o*19, y-1);
	gfx_point( x-o*19, y );
	gfx_point( x-o*18, y-3);
	gfx_point( x-o*18, y-2);
	gfx_point( x-o*18, y-1);
	gfx_point( x-o*18, y );
	gfx_point( x-o*18, y+1);
	gfx_point( x-o*17, y-4);
	gfx_point( x-o*17, y-3);
	gfx_point( x-o*17, y-2);
	gfx_point( x-o*17, y-1);
	gfx_point( x-o*17, y );
	gfx_point( x-o*17, y+1);
	gfx_point( x-o*17, y+2);
	gfx_point( x-o*17, y+14);
	gfx_point( x-o*16, y-4);
	gfx_point( x-o*16, y-3);
	gfx_point( x-o*16, y-2);
	gfx_point( x-o*16, y-1);
	gfx_point( x-o*16, y);
	gfx_point( x-o*16, y+1);
	gfx_point( x-o*16, y+2);
	gfx_point( x-o*16, y+3);
	gfx_point( x-o*16, y+9);
	gfx_point( x-o*16, y+10);
	gfx_point( x-o*16, y+11);
	gfx_point( x-o*16, y+12);
	gfx_point( x-o*16, y+13);
	gfx_point( x-o*15, y-5);
	gfx_point( x-o*15, y-4);
	gfx_point( x-o*15, y-3);
	gfx_point( x-o*15, y-2);
	gfx_point( x-o*15, y-1);
	gfx_point( x-o*15, y );
	gfx_point( x-o*15, y+3);
	gfx_point( x-o*15, y+2);
	gfx_point( x-o*15, y+1);
	gfx_point( x-o*15, y+8);
	gfx_point( x-o*15, y+9);
	gfx_point( x-o*15, y+10);
	gfx_point( x-o*15, y+11);
	gfx_point( x-o*15, y+12);
	gfx_point( x-o*15, y+13);
	gfx_point( x-o*15, y+15);
	gfx_point( x-o*14, y-6);
	gfx_point( x-o*14, y-5);
	gfx_point( x-o*14, y-4);
	gfx_point( x-o*14, y-2);
	gfx_point( x-o*14, y-1);
	gfx_point( x-o*14, y);
	gfx_point( x-o*14, y+1);
	gfx_point( x-o*14, y+2);
	gfx_point( x-o*14, y+3);
	gfx_point( x-o*14, y+7);
	gfx_point( x-o*14, y+8);
	gfx_point( x-o*14, y+9);
	gfx_point( x-o*14, y+10);
	gfx_point( x-o*14, y+11);
	gfx_point( x-o*14, y+12);
	gfx_point( x-o*14, y+13);
	gfx_point( x-o*14, y+14);
	gfx_point( x-o*13, y-6);
	gfx_point( x-o*13, y-5);
	gfx_point( x-o*13, y-4);
	gfx_point( x-o*13, y-3);
	gfx_point( x-o*13, y-2);
	gfx_point( x-o*13, y-1);
	gfx_point( x-o*13, y-3);
	gfx_point( x-o*13, y-1);
	gfx_point( x-o*13, y);
	gfx_point( x-o*13, y+1);
	gfx_point( x-o*13, y+2);
	gfx_point( x-o*13, y+3);
	gfx_point( x-o*13, y+4);
	gfx_point( x-o*13, y+6);
	gfx_point( x-o*13, y+7);
	gfx_point( x-o*13, y+8);
	gfx_point( x-o*13, y+9);
	gfx_point( x-o*13, y+10);
	gfx_point( x-o*13, y+11);
	gfx_point( x-o*13, y+12);
	gfx_point( x-o*13, y+13);
	gfx_point( x-o*13, y+14);
	gfx_point( x-o*12, y-7);
	gfx_point( x-o*12, y-6);
	gfx_point( x-o*12, y-5);
	gfx_point( x-o*12, y-4);
	gfx_point( x-o*12, y-3);
	gfx_point( x-o*12, y);
	gfx_point( x-o*12, y+1);
	gfx_point( x-o*12, y+2);
	gfx_point( x-o*12, y+3);
	gfx_point( x-o*12, y+4);
	gfx_point( x-o*12, y+5);
	gfx_point( x-o*12, y+6);
	gfx_point( x-o*12, y+7);
	gfx_point( x-o*12, y+8);
	gfx_point( x-o*12, y+9);
	gfx_point( x-o*12, y+10);
	gfx_point( x-o*12, y+11);
	gfx_point( x-o*12, y+12);
	gfx_point( x-o*12, y+13);
	gfx_point( x-o*12, y+14);
	gfx_point( x-o*11, y-8);
	gfx_point( x-o*11, y-7);
	gfx_point( x-o*11, y-6);
	gfx_point( x-o*11, y-5);
	gfx_point( x-o*11, y-4);
	gfx_point( x-o*11, y-3);
	gfx_point( x-o*11, y-2);
	gfx_point( x-o*11, y+1);
	gfx_point( x-o*11, y+2);
	gfx_point( x-o*11, y+3);
	gfx_point( x-o*11, y+4);
	gfx_point( x-o*11, y+5);
	gfx_point( x-o*11, y+6);
	gfx_point( x-o*11, y+7);
	gfx_point( x-o*11, y+8);
	gfx_point( x-o*11, y+9);
	gfx_point( x-o*11, y+10);
	gfx_point( x-o*11, y+11);
	gfx_point( x-o*11, y+12);
	gfx_point( x-o*11, y+13);
	gfx_point( x-o*10, y-8);
	gfx_point( x-o*10, y-7);
	gfx_point( x-o*10, y-6);
	gfx_point( x-o*10, y-5);
	gfx_point( x-o*10, y-4);
	gfx_point( x-o*10, y-3);
	gfx_point( x-o*10, y-2);
	gfx_point( x-o*10, y+1);
	gfx_point( x-o*10, y+2);
	gfx_point( x-o*10, y+3);
	gfx_point( x-o*10, y+4);
	gfx_point( x-o*10, y+6);
	gfx_point( x-o*10, y+7);
	gfx_point( x-o*10, y+8);
	gfx_point( x-o*10, y+9);
	gfx_point( x-o*10, y+10);
	gfx_point( x-o*10, y+11);
	gfx_point( x-o*10, y+12);
	gfx_point( x-o*10, y+13);
	gfx_point( x-o*10, y+15);
	gfx_point( x-o*9, y-8);
	gfx_point( x-o*9, y-4);
	gfx_point( x-o*9, y-3);
	gfx_point( x-o*9, y-2);
	gfx_point( x-o*9, y-1);
	gfx_point( x-o*9, y+1);
	gfx_point( x-o*9, y+2);
	gfx_point( x-o*9, y+3);
	gfx_point( x-o*9, y+4);
	gfx_point( x-o*9, y+5);
	gfx_point( x-o*9, y+7);
	gfx_point( x-o*9, y+8);
	gfx_point( x-o*9, y+9);
	gfx_point( x-o*9, y+10);
	gfx_point( x-o*9, y+11);
	gfx_point( x-o*9, y+12);
	gfx_point( x-o*9, y+13);
	gfx_point( x-o*9, y+14);
	gfx_point( x-o*8, y-4);
	gfx_point( x-o*8, y-3);
	gfx_point( x-o*8, y-2);
	gfx_point( x-o*8, y-1);
	gfx_point( x-o*8, y);
	gfx_point( x-o*8, y+1);
	gfx_point( x-o*8, y+2);
	gfx_point( x-o*8, y+3);
	gfx_point( x-o*8, y+4);
	gfx_point( x-o*8, y+6);
	gfx_point( x-o*8, y+7);
	gfx_point( x-o*8, y+8);
	gfx_point( x-o*8, y+9);
	gfx_point( x-o*8, y+10);
	gfx_point( x-o*8, y+11);
	gfx_point( x-o*8, y+12);
	gfx_point( x-o*8, y+13);
	gfx_point( x-o*7, y-11);
	gfx_point( x-o*7, y-10);
	gfx_point( x-o*7, y-9);
	gfx_point( x-o*7, y-4);
	gfx_point( x-o*7, y-3);
	gfx_point( x-o*7, y-2);
	gfx_point( x-o*7, y-1);
	gfx_point( x-o*7, y+2);
	gfx_point( x-o*7, y+3);
	gfx_point( x-o*7, y+4);
	gfx_point( x-o*7, y+7);
	gfx_point( x-o*7, y+8);
	gfx_point( x-o*7, y+9);
	gfx_point( x-o*7, y+10);
	gfx_point( x-o*7, y+11);
	gfx_point( x-o*7, y+12);
	gfx_point( x-o*7, y+13);
	gfx_point( x-o*6, y-12);
	gfx_point( x-o*6, y-11);
	gfx_point( x-o*6, y-10);
	gfx_point( x-o*6, y-9);
	gfx_point( x-o*6, y-5);
	gfx_point( x-o*6, y-2);
	gfx_point( x-o*6, y-1);
	gfx_point( x-o*6, y+3);
	gfx_point( x-o*6, y+9);
	gfx_point( x-o*6, y+11);
	gfx_point( x-o*6, y+12);
	gfx_point( x-o*5, y-13);
	gfx_point( x-o*5, y-12);
	gfx_point( x-o*5, y-10);
	gfx_point( x-o*5, y-9);
	gfx_point( x-o*5, y-6);
	gfx_point( x-o*5, y-2);
	gfx_point( x-o*5, y-1);
	gfx_point( x-o*5, y+2);
	gfx_point( x-o*5, y+4);
	gfx_point( x-o*5, y-10);
	gfx_point( x-o*5, y-11);
	gfx_point( x-o*4, y-13);
	gfx_point( x-o*4, y-14);
	gfx_point( x-o*4, y-6);
	gfx_point( x-o*4, y-1);
	gfx_point( x-o*4, y);
	gfx_point( x-o*4, y-10);
	gfx_point( x-o*3, y-15);
	gfx_point( x-o*3, y-14);
	gfx_point( x-o*3, y-6);
	gfx_point( x-o*3, y-1);
	gfx_point( x-o*3, y);
	gfx_point( x-o*2, y-15);
	gfx_point( x-o*2, y-14);
	gfx_point( x-o*2, y-6);
	gfx_point( x-o*2, y-1);
	gfx_point( x-o*2, y);
	gfx_point( x-o*2, y+10);
	gfx_point( x-o*1, y-15);
	gfx_point( x-o*1, y-14);
	gfx_point( x-o*1, y-13);
	gfx_point( x-o*1, y-10);
	gfx_point( x-o*1, y-8);
	gfx_point( x-o*1, y-6);
	gfx_point( x-o*1, y-1);
	gfx_point( x-o*1, y);
	gfx_point( x-o*1, y+1);
	gfx_point( x, y-15);
	gfx_point( x, y-14);
	gfx_point( x, y-13);
	gfx_point( x, y-12);
	gfx_point( x, y-8);
	gfx_point( x, y-6);
	gfx_point( x, y-1);
	gfx_point( x, y);
	gfx_point( x, y+1);
	gfx_point( x, y+10);
	gfx_point( x+o*1, y-15);
	gfx_point( x+o*1, y-14);
	gfx_point( x+o*1, y-13);
	gfx_point( x+o*1, y-10);
	gfx_point( x+o*1, y-8);
	gfx_point( x+o*1, y-6);
	gfx_point( x+o*1, y-1);
	gfx_point( x+o*1, y);
	gfx_point( x+o*1, y+9);
	gfx_point( x+o*1, y+10);
	gfx_point( x+o*2, y-15);
	gfx_point( x+o*2, y-14);
	gfx_point( x+o*2, y-6);
	gfx_point( x+o*2, y-1);
	gfx_point( x+o*2, y);
	gfx_point( x+o*3, y-15);
	gfx_point( x+o*3, y-14);
	gfx_point( x+o*3, y-6);
	gfx_point( x+o*3, y-1);
	gfx_point( x+o*3, y);
	gfx_point( x+o*3, y+10);
	gfx_point( x+o*4, y-14);
	gfx_point( x+o*4, y-13);
	gfx_point( x+o*4, y-6);
	gfx_point( x+o*4, y-1);
	gfx_point( x+o*4, y+2);
	gfx_point( x+o*4, y+4);
	gfx_point( x+o*4, y+10);
	gfx_point( x+o*4, y+11);	
	gfx_point( x+o*5, y-13);
	gfx_point( x+o*5, y-12);
	gfx_point( x+o*5, y-10);
	gfx_point( x+o*5, y-9);
	gfx_point( x+o*5, y-6);
	gfx_point( x+o*5, y-2);
	gfx_point( x+o*5, y-1);
	gfx_point( x+o*5, y+3);
	gfx_point( x+o*5, y+9);
	gfx_point( x+o*5, y+12);
	gfx_point( x+o*5, y+11);
	gfx_point( x+o*6, y-12);
	gfx_point( x+o*6, y-11);
	gfx_point( x+o*6, y-10);
	gfx_point( x+o*6, y-9);
	gfx_point( x+o*6, y-5);	
	gfx_point( x+o*6, y-2);
	gfx_point( x+o*6, y-1);
	gfx_point( x+o*6, y+2);
	gfx_point( x+o*6, y+3);
	gfx_point( x+o*6, y+4);
	gfx_point( x+o*6, y+7);
	gfx_point( x+o*6, y+8);
	gfx_point( x+o*6, y+9);
	gfx_point( x+o*6, y+10);
	gfx_point( x+o*6, y+11);
	gfx_point( x+o*6, y+12);
	gfx_point( x+o*6, y+13);
	gfx_point( x+o*7, y-4);
	gfx_point( x+o*7, y-3);
	gfx_point( x+o*7, y-2);
	gfx_point( x+o*7, y-1);
	gfx_point( x+o*7, y);
	gfx_point( x+o*7, y+1);
	gfx_point( x+o*7, y+2);
	gfx_point( x+o*7, y+3);
	gfx_point( x+o*7, y+4);
	gfx_point( x+o*7, y+6);
	gfx_point( x+o*7, y+7);
	gfx_point( x+o*7, y+8);
	gfx_point( x+o*7, y+9);
	gfx_point( x+o*7, y+10);
	gfx_point( x+o*7, y+11);
	gfx_point( x+o*7, y+12);
	gfx_point( x+o*7, y+13);
	gfx_point( x+o*8, y-8);
	gfx_point( x+o*8, y-4);
	gfx_point( x+o*8, y-3);
	gfx_point( x+o*8, y-2);
	gfx_point( x+o*8, y-1);
	gfx_point( x+o*8, y+1);
	gfx_point( x+o*8, y+2);
	gfx_point( x+o*8, y+3);
	gfx_point( x+o*8, y+4);
	gfx_point( x+o*8, y+5);
	gfx_point( x+o*8, y+7);
	gfx_point( x+o*8, y+8);
	gfx_point( x+o*8, y+9);
	gfx_point( x+o*8, y+10);
	gfx_point( x+o*8, y+11);
	gfx_point( x+o*8, y+12);
	gfx_point( x+o*8, y+13);
	gfx_point( x+o*8, y+14);
	gfx_point( x+o*9, y-8);
	gfx_point( x+o*9, y-7);
	gfx_point( x+o*9, y-6);
	gfx_point( x+o*9, y-5);
	gfx_point( x+o*9, y-4);
	gfx_point( x+o*9, y-3);
	gfx_point( x+o*9, y-2);
	gfx_point( x+o*9, y+1);
	gfx_point( x+o*9, y+2);
	gfx_point( x+o*9, y+3);
	gfx_point( x+o*9, y+4);
	gfx_point( x+o*9, y+6);
	gfx_point( x+o*9, y+7);
	gfx_point( x+o*9, y+8);
	gfx_point( x+o*9, y+9);
	gfx_point( x+o*9, y+10);
	gfx_point( x+o*9, y+11);
	gfx_point( x+o*9, y+12);
	gfx_point( x+o*9, y+13);
	gfx_point( x+o*9, y+15);
	gfx_point( x+o*10, y-8);
	gfx_point( x+o*10, y-7);
	gfx_point( x+o*10, y-6);
	gfx_point( x+o*10, y-5);
	gfx_point( x+o*10, y-4);
	gfx_point( x+o*10, y-3);
	gfx_point( x+o*10, y-2);
	gfx_point( x+o*10, y+1);
	gfx_point( x+o*10, y+2);
	gfx_point( x+o*10, y+3);
	gfx_point( x+o*10, y+4);
	gfx_point( x+o*10, y+5);
	gfx_point( x+o*10, y+6);
	gfx_point( x+o*10, y+7);
	gfx_point( x+o*10, y+8);
	gfx_point( x+o*10, y+9);
	gfx_point( x+o*10, y+10);
	gfx_point( x+o*10, y+11);
	gfx_point( x+o*10, y+12);
	gfx_point( x+o*10, y+13);
	gfx_point( x+o*11, y-7);
	gfx_point( x+o*11, y-6);
	gfx_point( x+o*11, y-5);
	gfx_point( x+o*11, y-4);
	gfx_point( x+o*11, y-3);
	gfx_point( x+o*11, y);
	gfx_point( x+o*11, y+1);
	gfx_point( x+o*11, y+2);
	gfx_point( x+o*11, y+3);
	gfx_point( x+o*11, y+4);
	gfx_point( x+o*11, y+5);
	gfx_point( x+o*11, y+6);
	gfx_point( x+o*11, y+7);
	gfx_point( x+o*11, y+8);
	gfx_point( x+o*11, y+9);
	gfx_point( x+o*11, y+10);
	gfx_point( x+o*11, y+11);
	gfx_point( x+o*11, y+12);
	gfx_point( x+o*11, y+13);
	gfx_point( x+o*11, y+14);
	gfx_point( x+o*12, y-6);
	gfx_point( x+o*12, y-5);
	gfx_point( x+o*12, y-4);
	gfx_point( x+o*12, y-3);
	gfx_point( x+o*12, y-2);
	gfx_point( x+o*12, y-1);
	gfx_point( x+o*12, y-3);
	gfx_point( x+o*12, y-1);
	gfx_point( x+o*12, y);
	gfx_point( x+o*12, y+1);
	gfx_point( x+o*12, y+2);
	gfx_point( x+o*12, y+3);
	gfx_point( x+o*12, y+4);
	gfx_point( x+o*12, y+6);
	gfx_point( x+o*12, y+7);
	gfx_point( x+o*12, y+8);
	gfx_point( x+o*12, y+9);
	gfx_point( x+o*12, y+10);
	gfx_point( x+o*12, y+11);
	gfx_point( x+o*12, y+12);
	gfx_point( x+o*12, y+13);
	gfx_point( x+o*12, y+14);
	gfx_point( x+o*18, y-3);
	gfx_point( x+o*18, y-2);
	gfx_point( x+o*18, y-1);
	gfx_point( x+o*18, y );
	gfx_point( x+o*17, y-3);
	gfx_point( x+o*17, y-2);
	gfx_point( x+o*17, y-1);
	gfx_point( x+o*17, y );
	gfx_point( x+o*17, y+1);
	gfx_point( x+o*16, y-4);
	gfx_point( x+o*16, y-3);
	gfx_point( x+o*16, y-2);
	gfx_point( x+o*16, y-1);
	gfx_point( x+o*16, y );
	gfx_point( x+o*16, y+1);
	gfx_point( x+o*16, y+2);
	gfx_point( x+o*16, y+14);
	gfx_point( x+o*15, y-4);
	gfx_point( x+o*15, y-3);
	gfx_point( x+o*15, y-2);
	gfx_point( x+o*15, y-1);
	gfx_point( x+o*15, y);
	gfx_point( x+o*15, y+1);
	gfx_point( x+o*15, y+2);
	gfx_point( x+o*15, y+3);
	gfx_point( x+o*15, y+9);
	gfx_point( x+o*15, y+10);
	gfx_point( x+o*15, y+11);
	gfx_point( x+o*15, y+12);
	gfx_point( x+o*15, y+13);
	gfx_point( x+o*14, y-5);
	gfx_point( x+o*14, y-4);
	gfx_point( x+o*14, y-3);
	gfx_point( x+o*14, y-2);
	gfx_point( x+o*14, y-1);
	gfx_point( x+o*14, y );
	gfx_point( x+o*14, y+3);
	gfx_point( x+o*14, y+2);
	gfx_point( x+o*14, y+1);
	gfx_point( x+o*14, y+8);
	gfx_point( x+o*14, y+9);
	gfx_point( x+o*14, y+10);
	gfx_point( x+o*14, y+11);
	gfx_point( x+o*14, y+12);
	gfx_point( x+o*14, y+13);
	gfx_point( x+o*14, y+15);
	gfx_point( x+o*13, y-6);
	gfx_point( x+o*13, y-5);
	gfx_point( x+o*13, y-4);
	gfx_point( x+o*13, y-2);
	gfx_point( x+o*13, y-1);
	gfx_point( x+o*13, y);
	gfx_point( x+o*13, y+1);
	gfx_point( x+o*13, y+2);
	gfx_point( x+o*13, y+3);
	gfx_point( x+o*13, y+7);
	gfx_point( x+o*13, y+8);
	gfx_point( x+o*13, y+9);
	gfx_point( x+o*13, y+10);
	gfx_point( x+o*13, y+11);
	gfx_point( x+o*13, y+12);
	gfx_point( x+o*13, y+13);
	gfx_point( x+o*13, y+14);
	
	// Face/Hands/Feet
	gfx_color(255, 207, 122);
	
	gfx_point( x-o*19, y+15);
	gfx_point( x-o*18, y+14);
	gfx_point( x-o*18, y+16);
	gfx_point( x-o*17, y+15);
	gfx_point( x-o*17, y+16);
	gfx_point( x-o*16, y+14);
	gfx_point( x-o*16, y+15);
	gfx_point( x-o*16, y+16);
	gfx_point( x-o*15, y+14);
	gfx_point( x-o*15, y+16);
	gfx_point( x-o*14, y+15);
	gfx_point( x-o*14, y+16);
	gfx_point( x-o*13, y+15);
	gfx_point( x-o*13, y+16);
	gfx_point( x-o*12, y+15);
	gfx_point( x-o*12, y+16);
	gfx_point( x-o*11, y+14);
	gfx_point( x-o*11, y+15);
	gfx_point( x-o*11, y+16);
	gfx_point( x-o*10, y-10);
	gfx_point( x-o*10, y-9);
	gfx_point( x-o*10, y+14);
	gfx_point( x-o*10, y+16);
	gfx_point( x-o*9, y-11);
	gfx_point( x-o*9, y-10);
	gfx_point( x-o*9, y-9);
	gfx_point( x-o*9, y-7);
	gfx_point( x-o*9, y-6);
	gfx_point( x-o*9, y-5);
	gfx_point( x-o*9, y+15);
	gfx_point( x-o*9, y+16);
	gfx_point( x-o*8, y-11);
	gfx_point( x-o*8, y-10);
	gfx_point( x-o*8, y-9);
	gfx_point( x-o*8, y-8);
	gfx_point( x-o*8, y-7);
	gfx_point( x-o*8, y-6);
	gfx_point( x-o*8, y-5);
	gfx_point( x-o*8, y+14);
	gfx_point( x-o*8, y+15);
	gfx_point( x-o*7, y-8);
	gfx_point( x-o*7, y-7);
	gfx_point( x-o*7, y-6);
	gfx_point( x-o*7, y-5);
	gfx_point( x-o*7, y);
	gfx_point( x-o*7, y+1);
	gfx_point( x-o*7, y+5);
	gfx_point( x-o*6, y-8);
	gfx_point( x-o*6, y-7);
	gfx_point( x-o*6, y-6);
	gfx_point( x-o*6, y-4);
	gfx_point( x-o*6, y-3);
	gfx_point( x-o*6, y);
	gfx_point( x-o*6, y+1);
	gfx_point( x-o*6, y+2);
	gfx_point( x-o*6, y+4);
	gfx_point( x-o*6, y+5);
	gfx_point( x-o*5, y-11);
	gfx_point( x-o*5, y-8);
	gfx_point( x-o*5, y-7);
	gfx_point( x-o*5, y-5);
	gfx_point( x-o*5, y-4);
	gfx_point( x-o*5, y-3);
	gfx_point( x-o*5, y);
	gfx_point( x-o*5, y+1);
	gfx_point( x-o*5, y+3);
	gfx_point( x-o*5, y+5);
	gfx_point( x-o*5, y+7);
	gfx_point( x-o*5, y+8);
	gfx_point( x-o*4, y-12);
	gfx_point( x-o*4, y-11);
	gfx_point( x-o*4, y-10);
	gfx_point( x-o*4, y-9);
	gfx_point( x-o*4, y-8);
	gfx_point( x-o*4, y-7);
	gfx_point( x-o*4, y-5);
	gfx_point( x-o*4, y-4);
	gfx_point( x-o*4, y-3);
	gfx_point( x-o*4, y-2);
	gfx_point( x-o*4, y+1);
	gfx_point( x-o*4, y+2);
	gfx_point( x-o*4, y+3);
	gfx_point( x-o*4, y+4);
	gfx_point( x-o*4, y+5);
	gfx_point( x-o*4, y+7);
	gfx_point( x-o*4, y+9);
	gfx_point( x-o*4, y-13);
	gfx_point( x-o*3, y-12);
	gfx_point( x-o*3, y-11);
	gfx_point( x-o*3, y-10);
	gfx_point( x-o*3, y-9);
	gfx_point( x-o*3, y-8);
	gfx_point( x-o*3, y-7);
	gfx_point( x-o*3, y-5);
	gfx_point( x-o*3, y-4);
	gfx_point( x-o*3, y-3);
	gfx_point( x-o*3, y-2);
	gfx_point( x-o*3, y+1);
	gfx_point( x-o*3, y+2);
	gfx_point( x-o*3, y+3);
	gfx_point( x-o*3, y+4);
	gfx_point( x-o*3, y+5);
	gfx_point( x-o*3, y+7);
	gfx_point( x-o*3, y+8);
	gfx_point( x-o*2, y-13);
	gfx_point( x-o*2, y-12);
	gfx_point( x-o*2, y-9);
	gfx_point( x-o*2, y-8);
	gfx_point( x-o*2, y-7);
	gfx_point( x-o*2, y-5);
	gfx_point( x-o*2, y-4);
	gfx_point( x-o*2, y-3);
	gfx_point( x-o*2, y-2);
	gfx_point( x-o*2, y+2);
	gfx_point( x-o*2, y+3);
	gfx_point( x-o*2, y+4);
	gfx_point( x-o*2, y+6);
	gfx_point( x-o*2, y+7);
	gfx_point( x-o*2, y+9);
	gfx_point( x-o*1, y-12);
	gfx_point( x-o*1, y-9);
	gfx_point( x-o*1, y-7);
	gfx_point( x-o*1, y-5);
	gfx_point( x-o*1, y-4);
	gfx_point( x-o*1, y-3);
	gfx_point( x-o*1, y-2);
	gfx_point( x-o*1, y+5);
	gfx_point( x-o*1, y+6);
	gfx_point( x-o*1, y+7);
	gfx_point( x-o*1, y+8);
	gfx_point( x, y-11);
	gfx_point( x, y-10);
	gfx_point( x, y-9);
	gfx_point( x, y-7);
	gfx_point( x, y-5);
	gfx_point( x, y-4);
	gfx_point( x, y-3);
	gfx_point( x, y-2);
	gfx_point( x, y+5);
	gfx_point( x, y+6);
	gfx_point( x, y+7);
	gfx_point( x, y+8);
	gfx_point( x, y+9);
	gfx_point( x+o*18, y+15);
	gfx_point( x+o*17, y+14);
	gfx_point( x+o*17, y+16);
	gfx_point( x+o*16, y+15);
	gfx_point( x+o*16, y+16);
	gfx_point( x+o*15, y+14);
	gfx_point( x+o*15, y+15);
	gfx_point( x+o*15, y+16);
	gfx_point( x+o*14, y+14);
	gfx_point( x+o*14, y+16);
	gfx_point( x+o*13, y+15);
	gfx_point( x+o*13, y+16);
	gfx_point( x+o*12, y+15);
	gfx_point( x+o*12, y+16);
	gfx_point( x+o*11, y+15);
	gfx_point( x+o*11, y+16);
	gfx_point( x+o*10, y+14);
	gfx_point( x+o*10, y+15);
	gfx_point( x+o*10, y+16);
	gfx_point( x+o*9, y-10);
	gfx_point( x+o*9, y-9);
	gfx_point( x+o*9, y+14);
	gfx_point( x+o*9, y+16);
	gfx_point( x+o*8, y-11);
	gfx_point( x+o*8, y-10);
	gfx_point( x+o*8, y-9);
	gfx_point( x+o*8, y-7);
	gfx_point( x+o*8, y-6);
	gfx_point( x+o*8, y-5);
	gfx_point( x+o*8, y+15);
	gfx_point( x+o*8, y+16);
	gfx_point( x+o*7, y-11);
	gfx_point( x+o*7, y-10);
	gfx_point( x+o*7, y-9);
	gfx_point( x+o*7, y-8);
	gfx_point( x+o*7, y-7);
	gfx_point( x+o*7, y-6);
	gfx_point( x+o*7, y-5);
	gfx_point( x+o*7, y+14);
	gfx_point( x+o*7, y+15);
	gfx_point( x+o*6, y-8);
	gfx_point( x+o*6, y-7);
	gfx_point( x+o*6, y-6);
	gfx_point( x+o*6, y-5);
	gfx_point( x+o*6, y);
	gfx_point( x+o*6, y+1);
	gfx_point( x+o*6, y+5);
	gfx_point( x+o*5, y-8);
	gfx_point( x+o*5, y-7);
	gfx_point( x+o*5, y-6);
	gfx_point( x+o*5, y-4);
	gfx_point( x+o*5, y-3);
	gfx_point( x+o*5, y);
	gfx_point( x+o*5, y+1);
	gfx_point( x+o*5, y+2);
	gfx_point( x+o*5, y+4);
	gfx_point( x+o*5, y+5);
	gfx_point( x+o*4, y-11);
	gfx_point( x+o*4, y-8);
	gfx_point( x+o*4, y-7);
	gfx_point( x+o*4, y-5);
	gfx_point( x+o*4, y-4);
	gfx_point( x+o*4, y-3);
	gfx_point( x+o*4, y);
	gfx_point( x+o*4, y+1);
	gfx_point( x+o*4, y+3);
	gfx_point( x+o*4, y+5);
	gfx_point( x+o*4, y+7);
	gfx_point( x+o*4, y+8);
	gfx_point( x+o*3, y-12);
	gfx_point( x+o*3, y-11);
	gfx_point( x+o*3, y-10);
	gfx_point( x+o*3, y-9);
	gfx_point( x+o*3, y-8);
	gfx_point( x+o*3, y-7);
	gfx_point( x+o*3, y-5);
	gfx_point( x+o*3, y-4);
	gfx_point( x+o*3, y-3);
	gfx_point( x+o*3, y-2);
	gfx_point( x+o*3, y+1);
	gfx_point( x+o*3, y+2);
	gfx_point( x+o*3, y+3);
	gfx_point( x+o*3, y+4);
	gfx_point( x+o*3, y+5);
	gfx_point( x+o*3, y+7);
	gfx_point( x+o*3, y+9);
	gfx_point( x+o*3, y-13);
	gfx_point( x+o*2, y-12);
	gfx_point( x+o*2, y-11);
	gfx_point( x+o*2, y-10);
	gfx_point( x+o*2, y-9);
	gfx_point( x+o*2, y-8);
	gfx_point( x+o*2, y-7);
	gfx_point( x+o*2, y-5);
	gfx_point( x+o*2, y-4);
	gfx_point( x+o*2, y-3);
	gfx_point( x+o*2, y-2);
	gfx_point( x+o*2, y+1);
	gfx_point( x+o*2, y+2);
	gfx_point( x+o*2, y+3);
	gfx_point( x+o*2, y+4);
	gfx_point( x+o*2, y+5);
	gfx_point( x+o*2, y+7);
	gfx_point( x+o*2, y+8);
	gfx_point( x+o*1, y-13);
	gfx_point( x+o*1, y-12);
	gfx_point( x+o*1, y-9);
	gfx_point( x+o*1, y-8);
	gfx_point( x+o*1, y-7);
	gfx_point( x+o*1, y-5);
	gfx_point( x+o*1, y-4);
	gfx_point( x+o*1, y-3);
	gfx_point( x+o*1, y-2);
	gfx_point( x+o*1, y+2);
	gfx_point( x+o*1, y+3);
	gfx_point( x+o*1, y+4);
	gfx_point( x+o*1, y+6);
	gfx_point( x+o*1, y+7);

	// Eyes
	gfx_color(255, 255, 255 );
	gfx_point( x-o*2, y-10);
	gfx_point( x-o*2, y-11);
	gfx_point( x-o*1, y-11);	
	gfx_point( x+o*2, y-10);
	gfx_point( x+o*2, y-11);
	gfx_point( x+o*1, y-11);

	// Misc
	gfx_color( 255, 144, 9);
	
	gfx_point( x-o*19, y+16);
	gfx_point( x-o*18, y-4);
	gfx_point( x-o*18, y+15);
	gfx_point( x-o*17, y-5);
	gfx_point( x-o*17, y+9);
	gfx_point( x-o*17, y+10);
	gfx_point( x-o*17, y+11);
	gfx_point( x-o*16, y-5);
	gfx_point( x-o*16, y+8);
	gfx_point( x-o*15, y-6);
	gfx_point( x-o*15, y+7);
	gfx_point( x-o*14, y-7);
	gfx_point( x-o*14, y-3);
	gfx_point( x-o*14, y+6);
	gfx_point( x-o*13, y-7);
	gfx_point( x-o*13, y-2);
	gfx_point( x-o*13, y+5);
	gfx_point( x-o*12, y-8);
	gfx_point( x-o*12, y-2);
	gfx_point( x-o*12, y-1);
	gfx_point( x-o*11, y-1);
	gfx_point( x-o*11, y);
	gfx_point( x-o*10, y-1);
	gfx_point( x-o*10, y);
	gfx_point( x-o*10, y+5);
	gfx_point( x-o*9, y);
	gfx_point( x-o*9, y+6);
	gfx_point( x-o*8, y+5);
	gfx_point( x-o*7, y+6);
	gfx_point( x-o*6, y+6);
	gfx_point( x-o*6, y+7);	
	gfx_point( x-o*6, y+8);	
	gfx_point( x-o*6, y+10);	
	gfx_point( x-o*5, y+6);	
	gfx_point( x-o*5, y+9);	
	gfx_point( x-o*4, y+6);	
	gfx_point( x-o*4, y+8);	
	gfx_point( x-o*3, y+6);	
	gfx_point( x-o*3, y+9);	
	gfx_point( x-o*3, y+10);	
	gfx_point( x-o*2, y+1);	
	gfx_point( x-o*2, y+5);	
	gfx_point( x-o*2, y+8);	
	gfx_point( x-o*1, y+2);	
	gfx_point( x-o*1, y+3);	
	gfx_point( x-o*1, y+4);	
	gfx_point( x-o*1, y+9);	
	gfx_point( x-o*1, y+10);
	gfx_point( x, y+2);	
	gfx_point( x, y+3);	
	gfx_point( x, y+4);
	gfx_point( x+o*1, y+1);
	gfx_point( x+o*1, y+5);
	gfx_point( x+o*1, y+8);	
	gfx_point( x+o*18, y+16);
	gfx_point( x+o*17, y-4);
	gfx_point( x+o*17, y+15);
	gfx_point( x+o*16, y-5);
	gfx_point( x+o*16, y+9);
	gfx_point( x+o*16, y+10);
	gfx_point( x+o*16, y+11);
	gfx_point( x+o*15, y-5);
	gfx_point( x+o*15, y+8);
	gfx_point( x+o*14, y-6);
	gfx_point( x+o*14, y+7);
	gfx_point( x+o*13, y-7);
	gfx_point( x+o*13, y-3);
	gfx_point( x+o*13, y+6);
	gfx_point( x+o*12, y-7);
	gfx_point( x+o*12, y-2);
	gfx_point( x+o*12, y+5);
	gfx_point( x+o*11, y-8);
	gfx_point( x+o*11, y-2);
	gfx_point( x+o*11, y-1);
	gfx_point( x+o*10, y-1);
	gfx_point( x+o*10, y);
	gfx_point( x+o*9, y-1);
	gfx_point( x+o*9, y);
	gfx_point( x+o*9, y+5);
	gfx_point( x+o*8, y);
	gfx_point( x+o*8, y+6);
	gfx_point( x+o*7, y+5);
	gfx_point( x+o*6, y+6);
	gfx_point( x+o*5, y+6);
	gfx_point( x+o*5, y+7);	
	gfx_point( x+o*5, y+8);	
	gfx_point( x+o*5, y+10);	
	gfx_point( x+o*4, y+6);	
	gfx_point( x+o*4, y+9);	
	gfx_point( x+o*3, y+6);	
	gfx_point( x+o*3, y+8);	
	gfx_point( x+o*2, y+6);	
	gfx_point( x+o*2, y+9);	
	gfx_point( x+o*2, y+10);	
}	
void drawmarioHead( int xc, int yc, int o ) {
	gfx_color(0, 0, 0);
	// Mouth/Moustache
	gfx_point( xc, yc );
	gfx_point( xc-o*1, yc );
	gfx_point( xc, yc-1);
	gfx_point( xc+o*1, yc);
	gfx_point( xc+o*2, yc);
	gfx_point( xc+o*3, yc);
	gfx_point( xc+o*4, yc);
	gfx_point( xc+o*5, yc);
	gfx_point( xc+o*1, yc+1);
	gfx_point( xc+o*2, yc+1);
	gfx_point( xc+o*3, yc+1);
	gfx_point( xc+o*4, yc+1);
	//Eyes
	gfx_point( xc, yc-3);
	gfx_point( xc, yc-4);
	gfx_point( xc+o*2, yc-3);
	gfx_point( xc+o*2, yc-4);
	//Hat Brim/Ear
	gfx_point( xc-o*3, yc-1);
	gfx_point( xc-o*3, yc-2);
	gfx_point( xc-o*3, yc-3);
	gfx_point( xc-o*2, yc-2);
	gfx_point( xc-o*4, yc-4);
	gfx_point( xc-o*3, yc-4);
	gfx_point( xc-o*2, yc-4);
	gfx_point( xc-o*2, yc-5);
	gfx_point( xc-o*1, yc-5);
	gfx_point( xc, yc-5);
	gfx_point( xc, yc-6);
	gfx_point( xc+o*1, yc-5);
	gfx_point( xc+o*1, yc-6);
	gfx_point( xc+o*2, yc-5);
	gfx_point( xc+o*2, yc-6);
	gfx_point( xc+o*3, yc-5);
	gfx_point( xc+o*3, yc-6);
	gfx_point( xc+o*4, yc-5);
	gfx_point( xc+o*4, yc-6);
	gfx_point( xc+o*5, yc-5);
	gfx_point( xc+o*5, yc-6);
	gfx_point( xc+o*6, yc-5);
	//Hat
	gfx_color( 255, 3, 3);
	gfx_point( xc-o*3, yc+3);
	gfx_point( xc-o*4, yc+3);
	gfx_point( xc-o*4, yc+2);
	gfx_point( xc-o*5, yc-5);
	gfx_point( xc-o*4, yc-5);
	gfx_point( xc-o*4, yc-6);
	gfx_point( xc-o*3, yc-5);
	gfx_point( xc-o*2, yc-6);
	gfx_point( xc-o*1, yc-6);
	gfx_point( xc-o*1, yc-7);
	gfx_point( xc, yc-7);
	gfx_point( xc+o*4, yc-7);
	gfx_point( xc+o*4, yc-8);
	gfx_color( 255, 117, 126 );
	gfx_point( xc-o*2, yc+3);
	gfx_point( xc-o*3, yc-6);
	gfx_point( xc-o*3, yc-7);
	gfx_point( xc-o*2, yc-7);
	gfx_point( xc-o*1, yc-8);
	gfx_point( xc, yc-8);
	gfx_point( xc+o*1, yc-8);
	gfx_point( xc+o*3, yc-8);
	gfx_color( 255, 255, 0 );
	gfx_point( xc+o*1, yc-7);
	gfx_point( xc+o*2, yc-7);
	gfx_point( xc+o*2, yc-8);
	gfx_point( xc+o*3, yc-7);
	//Face
	gfx_color( 255, 231, 131 );
	gfx_point( xc+o*1, yc-1); 
	gfx_point( xc+o*2, yc-1); 
	gfx_point( xc+o*3, yc-1); 
	gfx_point( xc+o*4, yc-1); 
	gfx_point( xc+o*5, yc-1); 
	gfx_point( xc+o*3, yc-4);
	gfx_point( xc+o*1, yc-4);
	gfx_point( xc-o*1, yc-4);
	gfx_point( xc-o*2, yc-3);
	gfx_point( xc-o*6, yc-2);
	gfx_point( xc-o*5, yc-1);
	gfx_point( xc-o*4, yc);
	gfx_point( xc-o*3, yc);
	gfx_point( xc-o*3, yc+1);
	gfx_point( xc-o*2, yc+1);
	gfx_point( xc-o*1, yc+1);
	gfx_point( xc, yc+1);
	gfx_color(255, 220, 250);
	gfx_point( xc-o*1, yc-3);
	gfx_point( xc-o*1, yc-2);
	gfx_point( xc-o*1, yc-1);
	gfx_point( xc-o*2, yc-1);
	gfx_point( xc-o*2, yc);
	gfx_point( xc, yc-2);
	gfx_point( xc+o*1, yc-2); 
	gfx_point( xc+o*2, yc-2); 
	gfx_point( xc+o*3, yc-2); 
	gfx_point( xc+o*4, yc-2); 
	gfx_point( xc+o*5, yc-2); 
	gfx_point( xc+o*1, yc-3);
	gfx_point( xc+o*3, yc-3);
	gfx_point( xc-o*4, yc-1);
	gfx_point( xc-o*4, yc-2);
	gfx_point( xc-o*4, yc-3);
	gfx_point( xc-o*5, yc-4);
	gfx_point( xc-o*6, yc-3);
}	
void drawMario( int xc, int yc, int o ) {
	// Mario is 19 pixels tall and 15 pixels wide
	gfx_color(0, 0, 0);
	// Mouth/Moustache
	gfx_point( xc, yc );
	gfx_point( xc-o*1, yc );
	gfx_point( xc, yc-1);
	gfx_point( xc+o*1, yc);
	gfx_point( xc+o*2, yc);
	gfx_point( xc+o*3, yc);
	gfx_point( xc+o*4, yc);
	gfx_point( xc+o*5, yc);
	gfx_point( xc+o*1, yc+1);
	gfx_point( xc+o*2, yc+1);
	gfx_point( xc+o*3, yc+1);
	gfx_point( xc+o*4, yc+1);
	//Eyes
	gfx_point( xc, yc-3);
	gfx_point( xc, yc-4);
	gfx_point( xc+o*2, yc-3);
	gfx_point( xc+o*2, yc-4);
	//Hat Brim/Ear
	gfx_point( xc-o*3, yc-1);
	gfx_point( xc-o*3, yc-2);
	gfx_point( xc-o*3, yc-3);
	gfx_point( xc-o*2, yc-2);
	gfx_point( xc-o*4, yc-4);
	gfx_point( xc-o*3, yc-4);
	gfx_point( xc-o*2, yc-4);
	gfx_point( xc-o*2, yc-5);
	gfx_point( xc-o*1, yc-5);
	gfx_point( xc, yc-5);
	gfx_point( xc, yc-6);
	gfx_point( xc+o*1, yc-5);
	gfx_point( xc+o*1, yc-6);
	gfx_point( xc+o*2, yc-5);
	gfx_point( xc+o*2, yc-6);
	gfx_point( xc+o*3, yc-5);
	gfx_point( xc+o*3, yc-6);
	gfx_point( xc+o*4, yc-5);
	gfx_point( xc+o*4, yc-6);
	gfx_point( xc+o*5, yc-5);
	gfx_point( xc+o*5, yc-6);
	gfx_point( xc+o*6, yc-5);
	//Other edges of body
	gfx_point( xc, yc-9);
	gfx_point( xc+o*1, yc-9);
	gfx_point( xc+o*2, yc-9);
	gfx_point( xc+o*3, yc-9);
	gfx_point( xc-o*1, yc-9);
	gfx_point( xc-o*2, yc-8);
	gfx_point( xc-o*3, yc-8);
	gfx_point( xc-o*4, yc-7);
	gfx_point( xc-o*5, yc-6);
	gfx_point( xc-o*6, yc-5);
	gfx_point( xc-o*6, yc-4);
	gfx_point( xc-o*7, yc-3);
	gfx_point( xc-o*7, yc-2);
	gfx_point( xc-o*7, yc-1);
	gfx_point( xc-o*6, yc-1);
	gfx_point( xc-o*6, yc);
	gfx_point( xc-o*5, yc);
	gfx_point( xc-o*5, yc+1);
	gfx_point( xc-o*6, yc+4);
	gfx_point( xc-o*7, yc+5);
	gfx_point( xc-o*7, yc+6);
	gfx_point( xc-o*7, yc+7);
	gfx_point( xc-o*7, yc+8);
	gfx_point( xc-o*6, yc+9);
	gfx_point( xc-o*5, yc+9);
	gfx_point( xc-o*4, yc+8);
	gfx_point( xc+o*3, yc+7);
	gfx_point( xc+o*3, yc+8);
	gfx_point( xc+o*4, yc+5);
	gfx_point( xc+o*4, yc+6);
	gfx_point( xc+o*4, yc+9);
	gfx_point( xc+o*5, yc+4);
	gfx_point( xc+o*5, yc+7);
	gfx_point( xc+o*5, yc+8);
	gfx_point( xc+o*5, yc+9);
	gfx_point( xc+o*6, yc+4);
	gfx_point( xc+o*6, yc+5);
	gfx_point( xc+o*6, yc+6);
	gfx_point( xc+o*6, yc+7);
	gfx_point( xc+o*6, yc+8);
	gfx_point( xc+o*7, yc+5);
	gfx_point( xc+o*7, yc+6);
	//Hat
	gfx_color( 255, 3, 3);
	gfx_point( xc-o*3, yc+3);
	gfx_point( xc-o*4, yc+3);
	gfx_point( xc-o*4, yc+2);
	gfx_point( xc-o*5, yc-5);
	gfx_point( xc-o*4, yc-5);
	gfx_point( xc-o*4, yc-6);
	gfx_point( xc-o*3, yc-5);
	gfx_point( xc-o*2, yc-6);
	gfx_point( xc-o*1, yc-6);
	gfx_point( xc-o*1, yc-7);
	gfx_point( xc, yc-7);
	gfx_point( xc+o*4, yc-7);
	gfx_point( xc+o*4, yc-8);
	gfx_color( 255, 117, 126 );
	gfx_point( xc-o*2, yc+3);
	gfx_point( xc-o*3, yc-6);
	gfx_point( xc-o*3, yc-7);
	gfx_point( xc-o*2, yc-7);
	gfx_point( xc-o*1, yc-8);
	gfx_point( xc, yc-8);
	gfx_point( xc+o*1, yc-8);
	gfx_point( xc+o*3, yc-8);
	gfx_color( 255, 255, 0 );
	gfx_point( xc+o*1, yc-7);
	gfx_point( xc+o*2, yc-7);
	gfx_point( xc+o*2, yc-8);
	gfx_point( xc+o*3, yc-7);
	//Face
	gfx_color( 255, 231, 131 );
	gfx_point( xc+o*1, yc-1); 
	gfx_point( xc+o*2, yc-1); 
	gfx_point( xc+o*3, yc-1); 
	gfx_point( xc+o*4, yc-1); 
	gfx_point( xc+o*5, yc-1); 
	gfx_point( xc+o*3, yc-4);
	gfx_point( xc+o*1, yc-4);
	gfx_point( xc-o*1, yc-4);
	gfx_point( xc-o*2, yc-3);
	gfx_point( xc-o*6, yc-2);
	gfx_point( xc-o*5, yc-1);
	gfx_point( xc-o*4, yc);
	gfx_point( xc-o*3, yc);
	gfx_point( xc-o*3, yc+1);
	gfx_point( xc-o*2, yc+1);
	gfx_point( xc-o*1, yc+1);
	gfx_point( xc, yc+1);
	gfx_point( xc+o*5, yc+5);
	gfx_point( xc-o*5, yc+8);
	gfx_color(255, 220, 250);
	gfx_point( xc-o*1, yc-3);
	gfx_point( xc-o*1, yc-2);
	gfx_point( xc-o*1, yc-1);
	gfx_point( xc-o*2, yc-1);
	gfx_point( xc-o*2, yc);
	gfx_point( xc, yc-2);
	gfx_point( xc+o*1, yc-2); 
	gfx_point( xc+o*2, yc-2); 
	gfx_point( xc+o*3, yc-2); 
	gfx_point( xc+o*4, yc-2); 
	gfx_point( xc+o*5, yc-2); 
	gfx_point( xc+o*1, yc-3);
	gfx_point( xc+o*3, yc-3);
	gfx_point( xc-o*4, yc-1);
	gfx_point( xc-o*4, yc-2);
	gfx_point( xc-o*4, yc-3);
	gfx_point( xc-o*5, yc-4);
	gfx_point( xc-o*6, yc-3);
	// Pants
	gfx_color( 9, 0, 255);
	gfx_point( xc+o*2, yc+2);
	gfx_point( xc, yc+3);
	gfx_point( xc+o*3, yc+3);
	gfx_point( xc+o*4, yc+4);
	gfx_point( xc-o*5, yc+7);
	gfx_point( xc-o*2, yc+7);
	gfx_point( xc-o*2, yc+8);
	gfx_point( xc-o*1, yc+8);
	gfx_point( xc-o*1, yc+7);
	gfx_point( xc-o*1, yc+6);
	gfx_point( xc-o*1, yc+5);
	gfx_point( xc, yc+8);
	gfx_point( xc, yc+7);
	gfx_point( xc, yc+6);
	gfx_point( xc+o*1, yc+8);
	gfx_point( xc+o*1, yc+7);
	gfx_point( xc+o*1, yc+6);
	gfx_point( xc+o*2, yc+7);
	gfx_point( xc+o*3, yc+6);
	gfx_color( 161, 170, 255);
	gfx_point( xc+o*1, yc+3);
	gfx_point( xc+o*2, yc+3);
	gfx_point( xc+o*2, yc+4);
	gfx_point( xc+o*2, yc+5);
	gfx_point( xc+o*2, yc+6);
	//Hands
	gfx_color( 255, 255, 255);
	gfx_point( xc, yc+4);
	gfx_point( xc, yc+5);
	gfx_point( xc+o*1, yc+4);
	gfx_point( xc+o*1, yc+5);
	gfx_point( xc+o*3, yc+4);
	gfx_point( xc+o*3, yc+5);
	gfx_point( xc-o*4, yc+4);
	gfx_point( xc-o*4, yc+5);
	gfx_point( xc-o*4, yc+6);
	gfx_point( xc-o*3, yc+4);
	gfx_point( xc-o*3, yc+5);
	gfx_point( xc-o*3, yc+6);
	gfx_point( xc-o*2, yc+4);
	//Misc Brown
	gfx_color( 51, 25, 0);
	gfx_point( xc+o*4, yc-3);
	gfx_point( xc+o*5, yc-3);
	gfx_point( xc+o*6, yc-2);
	gfx_point( xc+o*6, yc-1);
	gfx_point( xc-o*5, yc-2);
	gfx_point( xc-o*5, yc-3);
	gfx_point( xc+o*1, yc+2);
	gfx_point( xc, yc+2);
	gfx_point( xc+o*4, yc+7);
	gfx_point( xc+o*4, yc+8);
	gfx_point( xc+o*5, yc+6);
	gfx_point( xc-o*1, yc+2);
	gfx_point( xc-o*1, yc+3);
	gfx_point( xc-o*1, yc+4);
	gfx_point( xc-o*2, yc+2);
	gfx_point( xc-o*3, yc+2);
	gfx_point( xc-o*4, yc+1);
	gfx_point( xc-o*5, yc+2);
	gfx_point( xc-o*5, yc+3);
	gfx_point( xc-o*5, yc+4);
	gfx_point( xc-o*5, yc+5);
	gfx_point( xc-o*5, yc+6);
	gfx_point( xc-o*6, yc+5);
	gfx_point( xc-o*6, yc+6);
	gfx_point( xc-o*6, yc+7);
	gfx_point( xc-o*6, yc+8);
	gfx_point( xc-o*4, yc+7);
	gfx_point( xc-o*3, yc+7);
	gfx_point( xc-o*2, yc+5);
	gfx_point( xc-o*2, yc+6);
}

