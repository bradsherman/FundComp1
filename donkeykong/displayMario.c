//Display Mario

#include <string.h>
#include "mario.h"
#define NUM_COLORS 16

const unsigned char BlackPalette[NUM_COLORS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void SetColor(unsigned char, unsigned char );
void SetPalette(const unsigned char);

int main( void ) {
	asm
	ld a, #0
	call #0xBC0E
	endasm
	
	asm
	ld b, #0 ;black
	ld c, b
	call #0xBC38
	endasm
	
	SetPalette(BlackPalette);
	
	memcpy(0xC000, MarioScreen, 0x3FFF);
	
	SetPalette(MarioPalette);
	
	while(1) {};
}
void SetColor( unsigned char nColorIndex, unsigned char nPaletteIndex ) {
	asm{
	ld a, 4 (ix)
	ld b, 5 (ix)
	ld c, b
	call #0xBC32 ;SCR SET INK
	}#pragma endasm
}
void SetPalette( const unsigned char *pPalette) {
	unsigned char nColor = 0;
	for( nColor = 0; nColor < NUM_COLORS; nColor++ ) {
		SetColor( nColor, pPalette[nColor] );
}
