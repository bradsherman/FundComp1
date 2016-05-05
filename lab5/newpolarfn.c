// Brad Sherman
// Fundamentals of Computing 1
// Lab 5 Part 1
//

#include<math.h>

int polar_info( double x, double y, double *radius, double *angle) {
	
	*radius = sqrt((pow(x,2)) + (pow(y,2)));
	
	// Because the range of the atan function is only
	// -90-90 degrees, I had to adjust the angle value
	// for angles in quadrants 2-4 inorder to make all
	// angles from 0-360.
	
	if( y < 0 && x < 0 ) {
		*angle =  ((180/M_PI)*(atan(y/x)) + 180);
		return 3;
	} else if( y < 0 ) {
		*angle =  (360 + ((180/M_PI)*(atan(y/x))));
		if( x > 0 ) return 4;
		if( x == 0 ) return -2;
	} else if( x < 0 ) {
		*angle =  ((180/M_PI)*(atan(y/x)) + 180);
		if( y > 0 ) return 2;
		if( y == 0 ) return -1;
	} else {
		*angle =  ((180/M_PI)*(atan(y/x)));
		if( y == 0 && x == 0 ){
			*angle = 0;
			return 0;
		}
		if( y == 0 ) return -1;
		if( x == 0 ) return -2;
		else return 1;
	}

}	
	
	
