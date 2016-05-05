// Brad Sherman
// Fundamentals of Computing 1
// Lab 5 Review
//

#include<math.h>

float getPangle(float x, float y ) {
	// Because the range of the atan function
	// is only -90-90 degrees, each of these
	// cases are to make sure all possible angles
	// are displayed from 0-360.
        if( y < 0 && x < 0 ) {
               	// Makes sure angles in the 
               	// 3rd quadrant are from 180-270 degrees
		return ((180/M_PI)*(atan(y/x)) + 180);
        } else if( y < 0 ) {
		// Makes sure angles in the 4th quadrant are
		// from 270-360 degrees.
                return (360 + ((180/M_PI)*(atan(y/x))));
        } else if( x < 0 ) {
		// Makes sure angles in the 2nd quadrant
		// are from 90-180 degrees.
                return ((180/M_PI)*(atan(y/x)) + 180);
        } else {
                return ((180/M_PI)*(atan(y/x)));
        }
}
float getPradius(float x, float y ) {
        return sqrt((pow(x,2)) + (pow(y,2)));
}
int findQuad(float x, float y ) {
        if(x > 0 && y > 0) {
                return 1;
        } if(x > 0 && y < 0) {
                return 4;
        } if(x < 0 && y > 0) {
                return 2;
        } if(x < 0 && y < 0) {
                return 3;
        }
}

