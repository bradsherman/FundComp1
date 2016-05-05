// Brad Sherman
// Fundamentals of Computing 1
// Lab 4 Extra Credit
//



# include<stdio.h>


int main( void ) {

	printf( "Please enter your game board(s) to see if any kings are in check: \n" );
	
	int i,j,dot = 0;
	char game[8][8];
	char piece[1];
	
	for( i = 0; i < 8; i++) {
		for( j = 0; j < 8; j++) {
			scanf( "%c", &piece);
			if( piece == "." ) {
				dot++;
			}
			game[i][j] = piece;
		}	
	}

	while(dot != 64) {

		for( i = 0; i < 8; i++) {
			for( j = 0; j < 8; j++) {
				scanf( "%c", &piece);
				if( piece == "." ) {
					dot++;
				}
				game[i][j] = piece;
			}	
		}
		
		
		
	}
}	
