// Brad Sherman
// Fundamentals of Computing 1
// Lab 3 Part 3
//

#include<stdio.h>

float add(float,float);
float sub(float,float);
float mult(float,float);
float div(float,float);

int main( void ) {
	
	int loop = 1;

	while( loop ) {

		printf( "Welcome to the simple calculator. \n" );
		printf( "\n" );
		printf( "\t1 for addition\n" );
		printf( "\t2 for subtraction\n" );
		printf( "\t3 for multiplication\n" );
		printf( "\t4 for division\n" );
		printf( "\t5 to quit\n" );
		printf( "\n" );

		int choice;
		printf( "What would you like to do? \n" );
		scanf( "%d", &choice );
		
		float x,y;
		float result;
		
		switch ( choice ) {
		case 1:
			printf( "Addition!\n" );
			printf( "Please enter your numbers one by one: \n" );
			scanf( "%f", &x );
			scanf( "%f", &y );
			result = add(x,y);
			printf( "\n" );
			printf( "Your result is %.3f! \n", result );
			printf( "\n" );
			break;
		case 2:
			printf( "Subtraction!\n" );
			printf( "Please enter your numbers one by one: \n" );
			scanf( "%f", &x );
			scanf( "%f", &y );
			result = sub(x,y);
			printf( "\n" );
			printf( "Your result is %.3f! \n", result );
			printf( "\n" );
			break;
		case 3:
			printf ( "Multiplication!\n" );
			printf( "Please enter your numbers one by one: \n" );
			scanf( "%f", &x );
			scanf( "%f", &y );
			result = mult(x,y);
			printf( "\n" );
			printf( "Your result is %.3f! \n", result );
			printf( "\n" );
			break;
		case 4:
			printf( "Division!\n" );
			printf( "Please enter your numbers one by one: \n" );
			scanf( "%f", &x );
			scanf( "%f", &y );
			result = div(x,y);
			printf( "\n" );
			printf( "Your result is %.3f! \n", result );
			printf( "\n" );
			break;
		case 5:
			loop = 0;
			break;
		default:
			printf( "\n" );
			printf( "Sorry, I couldn't understand your input.\n" );
			printf( "\n" );
			continue;
		}
		
	}
}

float add( float x, float y) {
	return (x + y);
}
float sub(float x, float y) {
	return (x - y);
}
float mult(float x, float y) {
	return (x * y);
}
float div( float x, float y) {
	return (x/y);
}
