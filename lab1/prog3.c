#include <stdio.h>

// begin main function execution
int main( void )
{
	
	printf( "Welcome to the Tip Calculator! \n" );
	
	float bill; // variable that store the amount of the bill
	float tip; // variable for the % tip
	
	printf( "How much was your bill? \n" ); // ask for the bill total
	scanf( "%f", &bill ); // read the user input for the bill
	if ( bill < 0 ){
		printf( "That is not a valid answer. \n" ); // checking that the bill is not negative
		return 0;
	}
	printf( "What percent  would you like to tip? \n" ); // find out the tip
	scanf( "%f", &tip ); // read the tip amount
	if ( tip < 0 ){
		printf( "That is not a valid answer. \n" ); // make sure the tip is not negative
		return 0;
	}
	float total; // declare variable for total bill
	total = bill*(1+(tip/100));
	
	printf( "Thank you! Your total bill is $%.2f \n", total ); // display total bill
}
