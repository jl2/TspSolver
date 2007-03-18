#ifndef CITY_INCLUDE_H
#define CITY_INCLUDE_H

class City {
 public:
  City(double x=0.0, double y=0.0);
  virtual ~City() {}
  double getX() { return xPos; };
  double getY() { return yPos; };
  virtual double distanceTo(City *city);
 private:
  double xPos;
  double yPos;
};

#endif
