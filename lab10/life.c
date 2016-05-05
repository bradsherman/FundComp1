// Brad Sherman
// Fundamentals of Computing 1
// Lab 10 Game of Life
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BOARDSIZE 40

void initializeBoard( char[BOARDSIZE][BOARDSIZE] );
void printBoard( char[BOARDSIZE][BOARDSIZE] );
void newCell( char[BOARDSIZE][BOARDSIZE], int, FILE* );
void removeCell( char[BOARDSIZE][BOARDSIZE], int, FILE* );
void advance( char[BOARDSIZE][BOARDSIZE] );
char applyRules( char[BOARDSIZE][BOARDSIZE], int, int );
void playGame( char[BOARDSIZE][BOARDSIZE] );
void takeAction( char[BOARDSIZE][BOARDSIZE], char, int, FILE* );

int main( int argc, char *argv[] ) { 
	char board[BOARDSIZE][BOARDSIZE];
	initializeBoard(board);
	char c;
	int standard = 0;
	FILE* ifp;

	if( argc == 1 ) {
		// Interactive Mode
		while( c != 'q' ) {
			printf("Welcome to the Interactive Game of Life!\n" ) ;
			printf("Press 'a' to add a new live cell.\n" );
			printf("Press 'r' ro remove a cell.\n" );
			printf("Press 'n' to advance one iteration.\n" );
			printf("Press 'p' to play continuously.\n" );
			printf("	(Press Control-C to stop simulation)\n" );
			printf("Press 'q' to quit.\n\n");

			scanf( "%c", &c );
			takeAction(board, c, standard, ifp );
		}

	} else if( argc == 2 ) {
		// Scene Creation Mode
		char infile[20];
		// Open file 
		strcpy(infile,argv[1]);
		char line[10];
		ifp = fopen(infile,"r");
		// Let functions know how to accept data
		standard = 1;
		while( fscanf( ifp, "%s", line ) != EOF ) {
			c = line[0]; 
			takeAction(board, c, standard, ifp );
		}
	}
}
void takeAction( char board[BOARDSIZE][BOARDSIZE], char c, int standard, FILE *ifp ) {
	switch( c ) {
		case 'a':
			newCell(board, standard,ifp);
			break;
		case 'r':
			removeCell(board, standard,ifp); 
			break;
		case 'n':
			advance(board);
			break;
		case 'p':
			playGame(board);
			break;
		default:
			printf("Please enter a valid option.\n");
	}
	system("clear");
	printBoard(board);
}
void initializeBoard( char board[BOARDSIZE][BOARDSIZE] ) {
	// Make board
	int i,j;
	for( i = 0; i < BOARDSIZE; i++ ) {
		for( j = 0; j < BOARDSIZE; j++ ) {
			board[i][j] = ' ';
		}
	}
}
void printBoard( char board[BOARDSIZE][BOARDSIZE] ) {
	int i,j;
	for( i = 0; i < BOARDSIZE; i++ ) {
		for( j = 0; j < BOARDSIZE; j++ ) {
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
}
void newCell( char board[BOARDSIZE][BOARDSIZE], int standard, FILE *ifp ) {
	// Adds new cell to board with either user or file input
	int i,j;
	if( standard == 0 ) {
		printf("Please enter the coordinates where you would like to add a new cell:\n");
		scanf( "%d %d", &i, &j );
	}else if( standard == 1 ) fscanf(ifp, "%d %d",&i,&j );
	board[i][j] = 'X';
}
void removeCell( char board[BOARDSIZE][BOARDSIZE], int standard, FILE *ifp ) {
	// Remove cell from board 
	int i,j;
	if( standard == 0) {
		printf("Please enter the coordinates where you would like to remove a cell:\n");
		scanf("%d %d", &i, &j );
	}else if( standard == 1 ) fscanf(ifp,"%d %d", &i, &j );
	if( board[i][j] == 'X' ) board[i][j] = ' ';
	
}
void advance( char board[BOARDSIZE][BOARDSIZE] ) {
	// Advances the board one generation by applying the rules
	// one coordinate at a time
	int i,j;
	char board2[BOARDSIZE][BOARDSIZE];
	for( i = 0; i < BOARDSIZE; i++ ) {
		for( j = 0; j < BOARDSIZE; j++ ) {
			board2[i][j] = applyRules(board,i,j);
		}
	}
	for( i = 0; i < BOARDSIZE; i++ ) {
		for( j = 0; j < BOARDSIZE; j++ ) {
			board[i][j] = board2[i][j];
		}
	}
}
char applyRules( char board[BOARDSIZE][BOARDSIZE], int i, int j ) {
	// Apply rules to a single point on the board
	int neighbors[8][2] = { {-1,-1}, {0,-1}, {1,-1}, {-1,0}, {1,0}, {-1,1}, {0,1}, {1,1}};
	int x,y,k;
	int liveNeighbors = 0;
	for( k = 0; k < 8; k++ ) {
		x = i + neighbors[k][0];
		y = j + neighbors[k][1];
		if( board[x][y] == 'X' ) liveNeighbors++;
	}
	if( board[i][j] == 'X' ) {
		if( liveNeighbors < 2 ) return ' ';
		else if( liveNeighbors == 2 || liveNeighbors == 3 ) return 'X';
		else if( liveNeighbors > 3 ) return ' ';
	}else if( board[i][j] == ' ' ) {
		if( liveNeighbors == 3 ) return 'X';
		else return ' ';
	}
}
void playGame( char board[BOARDSIZE][BOARDSIZE] ) {
	// Play game forever
	int i,j;
	int wait = 100000;
	char board2[BOARDSIZE][BOARDSIZE];
	while( 1 ) {
		for( i = 0; i < BOARDSIZE; i++ ) {
			for( j = 0; j < BOARDSIZE; j++ ) {
				board2[i][j] = applyRules(board,i,j);
			}
		}
		for( i = 0; i < BOARDSIZE; i++ ) {
			for( j = 0; j < BOARDSIZE; j++ ) {
				board[i][j] = board2[i][j];
			}
		}
		system("clear");
		printBoard(board);
		usleep(wait);
	}
}
