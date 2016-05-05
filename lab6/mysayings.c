// Brad Sherman
// Fundamentals of Computing 1
// Lab 6
//
 
#include<stdio.h>
#include<string.h>

int populate(char [][100], FILE *);
void disp_sayings( char[][100], int);
void new_saying( char[][100], int);
void list_saying( char[][100], int );
void new_file( char[][100], int );

int main( int argc, char *argv[]) {
	
	FILE *ifp;
	char infile[30];
	if ( argc == 1 ) {
		printf( "Please enter a startup text file's name: \n" );
		scanf( "%s", infile );
		ifp = fopen( infile, "r" );
	} else if (argc == 2 ) {
		strcpy(infile, argv[1]);		
		ifp = fopen( infile, "r" );
	} else {
		printf( "Incorrect input.\n" );
		printf( "You must type: \"%s\", or \"%s StartupFileName\"\n", argv[0],argv[0] );
		return 1;
	}
	if( !ifp ) {
		printf( "Error opening file %s. \n", infile );
		return 1;
	}
	
	char sayings[100][100];
	int rows = populate( sayings, ifp );
	
	int choice;
	
	while( choice != 5 ) {
		
		printf( "\nWelcome to the sayings manager. \n\n" );
		printf( "1: Display all sayings. \n" );
		printf( "2: Enter a new saying. \n" );
		printf( "3: List sayings that contain a certain word. \n" );
		printf( "4: Save sayings in a new text file. \n" );
		printf( "5: Quit \n" );
		
		printf( "Please choose an option: " );
		scanf( "%d", &choice );
		printf( "\n" );
	
		switch( choice ) {
			case 1:
				disp_sayings(sayings, rows );
				break;
			case 2:
				new_saying( sayings, rows );
				rows++;
				break;
			case 3:
				list_saying( sayings, rows );
				break;
			case 4: 
				new_file( sayings, rows );
				break;
			case 5:
				break;
			default:
				printf( "Sorry, I couldn't understand your input.\n" );
				break;
		}	
	}
}

int populate( char sayings[100][100], FILE *ifp ) {
	
	int i = 0;
	
	for( i = 0; i < 100; i++ ) {
		if( fgets( sayings[i], 100, ifp) == NULL ) break;
	}
	return i;
}

void disp_sayings( char sayings[100][100], int r ) {
	int i, j = 0;
	for( i = 0; i < r; i++ ) {
		j = 0;
		while( sayings[i][j] != '\0'){		
			printf("%c", sayings[i][j] );
			j++;
		} 		
	}
}

void new_saying( char sayings[100][100], int r ) {
	char garbage;
	printf( "Enter the saying you would like to add: \n" );
	scanf( "%c", &garbage );
	fgets( sayings[r], 100, stdin);
}

void list_saying( char sayings[100][100], int r ) {
	printf( "What word would you like to search for? \n" );
	char word[15];
	scanf( "%s", word );
	int i;
	for( i = 0; i < r; i++ ) {
		if( strcasestr(sayings[i], word) ) {
			printf( "%s\n", sayings[i] );
		}
	}
}	

void new_file( char sayings[100][100], int r ) {
	FILE *ofp;
	char outfile[30];

	printf( "Enter the name of the file you would like to save your sayings in: \n" );
	scanf( "%s", outfile );
	
	ofp = fopen(outfile, "w" );

	int i, j = 0;
	for( i = 0; i < r; i++ ) {
		j = 0;
		while( sayings[i][j] != '\0') {
			fprintf( ofp, "%c", sayings[i][j] );
			j++;
		}
	}
}	
