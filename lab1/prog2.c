#include <stdio.h>

// begin main program
int main( void )
{
	int touchdowns; // Number of touchdowns The Irish score
	int expoints;   // Number of extra points The Irish score
	int fgoals;     // number of field goals The Irish score
	int safeties;   // number of safeties The Irish score
	
	printf( "How many touchdowns did Notre Dame score? \n" ); // TD prompt
	scanf( "%d", &touchdowns ); // read number of touchdowns
	
	printf( "How many extra points did Notre Dame score? \n" ); // Ex pt prompt
	scanf( "%d", &expoints ); // read number of extra points
	
	printf( "How many field goals did Notre Dame make? \n" ); // FG prompt
	scanf( "%d", &fgoals ); // read number of field goals
	
	printf( "How many safeties did Notre Dame get? \n" ); // Safety prompt
	scanf( "%d", &safeties ); // read number of safeties
	
	int score; // variable which will become Notre Dame's score that game
	score = (6*touchdowns) + (expoints) + (3*fgoals) + (2*safeties); // find score
	
	printf( "Notre Dame's score is %d\n", score ); // display score
	
}
