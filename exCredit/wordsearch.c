// Brad Sherman
// Fundamentals of Computing 1
// Fall Break Extra Credit
// Word Search
//

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

void populate( char[50][50], int, int );
void popWords( char[20][50], int );
void findMatch( char[50][50], char[20][50], int, int, int, FILE * );

int main( void ) {
	char cases[5];
	fgets( cases, 5, stdin );
	int numCases = cases[0] - 48;

	int c = 1;

	FILE *ofp;
	char outfile[11] = "output.txt";
	ofp = fopen( outfile, "w" );
	
	while( c <= numCases ) {
		char garbage[5];
		scanf( "%c", garbage );

		char dims[6];
		fgets( dims, 6, stdin);
		int rows,cols;
		sscanf( dims, "%d%d", &rows, &cols );	
	
		char block[50][50];	
		int len = cols + 1;
		populate( block, rows, len);
	
		int numWords;
		scanf( "%d", &numWords );
		char garbage2[5];
		scanf( "%c", garbage2 );
		char words[20][50];
		popWords( words, numWords );
		
		findMatch( block, words, rows, cols, numWords, ofp );
		fprintf( ofp, "\n" );
		c++;	
	}
	fclose(ofp);
	FILE *ifp;
	char infile[11] = "output.txt";
	ifp = fopen( infile, "r" );
	if( !ifp ) printf( "Error printing output.\n" );
	char line[10];
	while( fgets( line, 10, ifp ) ) {
		printf( "%s", line );
	}
	fclose(ifp);

}

void populate( char block[50][50], int rows, int len ) {
	int i,j;
	char garbage[5];
        for( i = 0; i < rows; i++ ) {
	        fgets( block[i], len, stdin );
 	    	scanf( "%c", garbage );
		for( j = 0; j < len; j++ ) {
        	        block[i][j] = tolower(block[i][j]);
        	}
	}	
}

void popWords( char words[20][50], int numWords ) {
	int i,j;
	char garbage[5];
	for( i = 0; i < numWords; i++ ) {
		fgets( words[i], 50, stdin );
		for( j = 0; j < 50; j++ ) {
			words[i][j] = tolower(words[i][j]);
		}
	}
}

void findMatch( char block[50][50], char words[20][50], int rows, int cols, int numWords, FILE *ofp ) {
	// I know this code is really bad with all the nested for loops, but 
	// I did not have time to think of a better way to look for words.
	int i,j,w;
	int s[8][2] = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
	for( w = 0; w < numWords; w++ ) {
		int length = strlen(words[w])-1;
		for( i = 0; i < rows; i++ ) {
			for( j = 0; j < cols; j++ ) {
				if( block[i][j] == words[w][0] ) {
					int a,b,k, mult;
					for( k = 0; k < 8; k++ ) {
						a = s[k][0];
						b = s[k][1];
						if( i+mult*a < 0 || i+mult*b < 0 || i+mult*a > rows || i+mult*b > cols ) continue;
						for( mult = 0; mult <= length; mult++ ) {
							if( block[i+mult*a][j+mult*b] != words[w][mult] ) break;
						}
					
						if( mult == length ) {
							fprintf( ofp, "%d %d\n", (i+1), (j+1) );
//							printf( "%d %d\n", (i+1), (j+1) );
							break;
						}
					}
				}				
			}				
		}
	}
}

