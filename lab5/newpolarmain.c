// Brad Sherman
// Fundamentals of Computing 1
// Lab 5 Part 1
//

#include <stdio.h>
#include "newpolarfn.h"

int main()
{
  double x, y, radius, theta;
  int quad;

  printf("Enter the point's x and y coordinates: ");
  scanf("%lf %lf", &x, &y);

  quad = polar_info(x, y, &radius, &theta);  // you will write the polar_info function

  printf("Point (%.2lf,%.2lf)'s polar coordinates are:\n", x, y);
  printf(" radius: %.2f units\n angle: %.2f degrees\n", radius, theta);
  printf("The point is ");
  switch(quad) {
    case 1: case 2: case 3: case 4:
      printf("in quadrant %d\n", quad);
      break;
    case 0:
      printf("at the origin\n");
      break;
    case -1:
      printf("on the x axis\n");
      break;
    case -2:
      printf("on the y axis\n");
      break;
    default:
      printf("in an unknown location\n");
  }

  return 0;
}
