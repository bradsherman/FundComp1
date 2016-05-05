// Brad Sherman
// Fundamentals of Computing 1
// Lab 4 Part 3
//


#include<stdio.h>
#include "ndwins.h"
#include "ndloss.h"
#include "ndties.h"

void undefeated( int, int[200][4] );
void onetieseason( int, int[200][4] );
void minwins( int, int[200][4] );
void minlosses( int, int[200][4] );
void findrecord( int, int[200][4] );

int main( void ) {

	int row = 0;
	int ndfootball[200][4];
	int count = 0;
	int year = 1900;
	
	// Make 2D array with year, wins, losses, ties
	while( wins[row] >= 0 ) {
		ndfootball[row][0] = year;
		year = year + 1;
	
		ndfootball[row][1] = wins[row];
		ndfootball[row][2] = losses[row];
		ndfootball[row][3] = ties[row];
		count = count + 1;
		row = row + 1;
	}
//	This block is kept so I can easily print
//	the ndfootball array to make sure it is 
//	being made correctly.
//	int k = 0;

//	for( k = 0; k < count; k++ ) {
//		printf( "%3d", ndfootball[k][0] );
//		printf( "%3d", ndfootball[k][1] );
//		printf( "%3d", ndfootball[k][2] );
//		printf( "%3d\n", ndfootball[k][3] );
//		
//	}

	int choice;
	
	while( choice != 6 ) {
		printf( "\n" );
		printf( "Please pick an option to learn more about Notre Dame Football.\n" );
		printf( "1: Display years with an undefeated season.\n" );
		printf( "2: Display years with at least one tie.\n" );
		printf( "3: Display years with at least \"x\" wins.\n" );
		printf( "4: Display years with more than \"x\" losses.\n" );
		printf( "5: Display the record for a given year.\n" );
		printf( "6: Exit \n" );

		int j,m = 0;

		printf( "What would you like to do?\n" );
		scanf( "%d", &choice );

		switch( choice ) {
			case 1:
				undefeated(count,ndfootball);
				break;
			case 2: 
				onetieseason(count,ndfootball);
				break;
			case 3:
				minwins(count,ndfootball); 
				break;
			case 4:
				minlosses(count,ndfootball);	
				break;
			case 5:
				findrecord(count,ndfootball);
				break;
			case 6:
				break;
			default:
				printf( "I'm sorry, I didn't understand your answer. Please try again.\n" );
				break;
		}

	}
}

// Each of these functions is fairly similar, except for what they
// are looking for and what they return. Column Indexes are as 
// follows: [0] = year, [1] = wins, [2] = losses, and 
// [3] = ties.

void undefeated(int count, int ndfootball[200][4]) {
	int j,m = 0;
	printf( "Notre Dame was undefeated in the years: \n" );

	for( j = 0; j < count; j++ ) {
		if( ndfootball[j][2] == 0 ) {
			m++;
			if( m % 5 == 0 ) {
				printf( "%5d\n", ndfootball[j][0]);
			}
			else{
				printf( "%5d", ndfootball[j][0]);
			}
		}
	}
}

void onetieseason( int count, int ndfootball[200][4]) {
	int j,m = 0;
	printf( "The seasons with at least one tie are: \n" );

       	for( j = 0; j < count; j++ ) {
               	if( ndfootball[j][3] > 0 ) {
                       	m++;
                        if( m % 5 == 0 ) {
       	                        printf( "%5d\n", ndfootball[j][0]);
               	        }
                       	else{
	                        printf( "%5d", ndfootball[j][0]);
                        }
                }
        }
	printf( "\n" );
}

void minwins( int count, int ndfootball[200][4]) {
	
	printf( "Please choose the minimum number of wins: \n" );
	int x,j, m = 0;
	scanf( "%d", &x );
	for( j = 0; j < count; j++ ) {
		if( ndfootball[j][1] >= x ) {
			m++;
			if( m % 5 == 0 ) {
				printf( "%5d\n", ndfootball[j][0]);
			}
			else {
				printf( "%5d", ndfootball[j][0]);
			}
		}
	}
	printf("\n");

}

void minlosses( int count, int ndfootball[200][4]) {
	printf( "Please choose the minimum number of losses: \n" );
	int x,j,m = 0;
	scanf( "%d", &x );
	for( j = 0; j < count; j++ ) {
		if( ndfootball[j][2] >= x ) {
			m++;
			if( m % 5 == 0 ) {
				printf( "%5d\n", ndfootball[j][0]);
			}
			else {
				printf ("%5d", ndfootball[j][0]);
			}
		}
	}
	printf( "\n" );
}

void findrecord( int count, int ndfootball[200][4]) {
	printf( "Please enter the year you wish to see the record for: \n" );
	int year,j;
	scanf( "%d", &year );
	for( j = 0; j < count; j++ ) {
		if( ndfootball[j][0] == year) {
			printf( "In %d, Notre Dame's record was %d-%d-%d. \n", year, ndfootball[j][1], ndfootball[j][2],ndfootball[j][3]);
		}
	}
}



