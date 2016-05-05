// Brad Sherman
// Fundamentals of Computing 1
// lab 2 part 2
// Create an amortization table with user designated principal, interest rate,
// and monthly payment values

#include <stdio.h>

int main( void ) {
	
	printf( "Welcome to the Mortgage Calculator!\n" );
	
	double principal;
	double intrate;
	double payment;
	
	// Take input and make sure each input value is valid
	
	printf( "Please input the amount you would like to loan: \n" );
	scanf( "%lf", &principal );
	
	while( principal <= 0 ) {
	printf( "Please enter a valid loan amount.\n" );
	scanf( "%lf", &principal );
	}
	
	printf( "Please input the interest rate you will accept: \n" );
	scanf( "%lf", &intrate );
	
	while( intrate <= 0 ) {
	printf( "Please enter a valid interest rate.\n" );
	scanf( "%lf", &intrate );
	}
	
	printf( "Please input the monthly payment you would like to pay: \n" );
	scanf( "%lf", &payment );
	
	while( payment <= 0 || (( principal*(intrate/1200)) > payment )) {
	printf( "You either entered a negative monthly payment, or one that \n" );
	printf( "is too small. Please enter a valid monthly payment.\n" );
	scanf( "%lf", &payment );
	}

	double balance = principal;
	double interest = 0;
	double total = principal;
	int month = 0;
	
	printf( "Month     " );
	printf( "Payment     ");
	printf( "Interest       " );
	printf( "Balance   \n" );
	
	// This while loop updates each variable for each month and then
	// displays it neatly in the amortization table.
	
	while( balance > 0 ){
	month = month + 1;
	interest = balance*(intrate/1200); // 1200 comes from 100*12
	total = total + interest;
	balance = balance + interest - payment;
	if( balance < 0 ) {
	balance = 0;
	}
	
	printf( "%-7d  ", month );
	printf( "$%8.2lf    ", payment );
	printf( "$%8.2lf    ", interest );
	printf( "$%10.2lf\n", balance );
	}
	int years;
	int months;
	years = month/12;
	months = month%12;
	printf( "You paid a total of $%.2lf over %d years and %d months.\n", total, years, 
	months );
}
