// Brad Sherman
// Fundamentals of Computing 1
// Exam 2 Review
//

#include<stdio.h>
#include<string.h>

typedef struct Employee_s {
	char id[5];
	char name[20];
	double hours;
	double wage;
	double pay;
} Employee;

int main( int argc, char *argv[] ) {
	FILE *ifp;
	char infile[30];
	if( argc == 1 ) {
		printf( "Please enter the data file at the command line.\n" );
		return 1;
	} else if( argc == 2 ) {
		strcpy( infile, argv[1] );
		ifp = fopen( infile, "r" );
	} else {
		printf( "Incorrect input.\n" );
		printf( "Please type: \"%s\" DataFileName\n", argv[0] );
		return 1;
	}
	if( !ifp ) {
		printf( "Error opening file %s.\n", infile );
		return 1;
	}
	
	Employee employees[100];
	int i = 0;

	while( !feof(ifp) ) {
		fscanf( ifp, "%s" "%s" "%lf" "%lf", employees[i].id, employees[i].name, employees[i].hours, employees[i].wage );
		i++;
	}
}	 
