// Brad Sherman
// Fundamentals of Computing 1
// Lab 5 Review
//

#include<stdio.h>
#include "polarfn.h"

int main( void ) {

        printf( "Please enter a point in Cartesian Coordinates to be converted \n" );
        printf( "to Polar Coordinates. \n" );

        float  x,y;

        printf( "X Coordinate: " );
        scanf( "%f", &x );

        printf( "Y Coordinate: " );
        scanf( "%f", &y );

        printf( "Your coordinate will be given in the form (radius, degrees).\n" );
        printf( "\n" );

        float theta;
        float radius;
        int quad;

        theta = getPangle( x, y);
        radius = getPradius( x, y);
        quad = findQuad(x,y);

        if(x == 0 && y == 0) {
                printf( "Your Polar Coordinate is (0, 0) and lies at the origin.\n" );
        } else if( x == 0 && y != 0) {
                printf( "Your Polar Coordinate is (%.2f, %.2f) and lies on the y-axis.\n",radius,theta);
        } else if( x != 0 && y == 0) {
                printf( "Your Polar Coordinate is (%.2f, %.2f) and lies on the x-axis.\n",radius,theta);
        } else {
                printf( "Your Polar Coordinate is (%.2f, %.2f) and lies in quadrant %d.\n",radius,theta,quad);
        }
}

