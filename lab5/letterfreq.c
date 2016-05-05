// Brad Sherman
// Fundamentals of Computing 1
// Lab 5 Part 2
//

#include<stdio.h>
#include<ctype.h>

int main( void ) {
	
	FILE *ifp;
	char infile[20];
	
	printf("Please enter a text file's name: \n" );
	scanf( "%s", infile );

	// Check to make sure file is successfully opened.	
	ifp = fopen( infile, "r" );
	if( !ifp ){
		printf("Error opening file %s. \n", infile );
		return 1;
	}
	
	int freq[26] = {0}; // array of frequency of each letter
	char c; // takes on each character of the file one at a time
	char d; // becomes the actual letter that is read in
	int chars = 0; 
	int spaces = 0;

	while( fscanf( ifp, "%c", &c ) != EOF ) {
		
		chars++;		
		
		if( isspace(c) ) {
			spaces++;
		} else if( islower(c)) {
			// toupper(c) - 'A' is the distance from A that 
			// the letter is so it gives us the numeric value 
			// of that letter's distance from A
			d = toupper(c) - 'A';
			freq[d]++;
		} else {
			d = c - 'A';
			freq[d]++;
		}

	}
	
	int i = 0;
	int sum = 0;
	for( i = 0; i < 26; i++ ) {
		printf( "The letter %c appears %7d times.\n", i+'A', freq[i] );
		sum += freq[i];
	}
	
	double spacep;
	spacep  = 100*(double)spaces/chars;

	printf( "There were %d letters.\n", sum );
	printf( "There were %d total characters.\n", chars );
	printf( "There were %d white space characters.\n", spaces );
	printf( "The space percentage was %2.1lf% \n", spacep ); 

}
		
		
