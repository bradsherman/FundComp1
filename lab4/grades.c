// Brad Sherman
// Fundamentals of Computing 1
// Lab 4 Part 1
//


#include<stdio.h>
#include<math.h>

int main( void ) {
	
	int dev[50];
	int i = 0;
	int num = 0;
	double sum = 0;
	double average = 0;
	double devSum = 0;
	double stddev = 0;
	scanf( "%d", &num );

	while( num >= 0 ) {
		sum = sum + num;
		dev[i] = num;
		scanf( "%d", &num );
		i = i + 1;
	}
	
	int length = i;	
	average = sum/length;
	int k = 0;

	for(k = 0; k < length; k++) {
                dev[k] = pow((dev[k]-average),2);;
                devSum = devSum + dev[k];
                stddev = sqrtf((devSum)/( length-1 ));
	}

	printf( "The mean of the grades is %.3lf.\n", average );
	printf( "The standard deviation of the grades is %.3lf.\n", stddev );





}
	
