#include "city.h"
#include <cmath>


City::City(double x, double y) : xPos(x), yPos(y) {
}

double City::distanceTo(City *city) {
  register double tempx = xPos-city->xPos;
  register double tempy = yPos-city->yPos;
  return std::sqrt(tempx*tempx + tempy*tempy);
}
