#ifndef CITY_LIST_H
#define CITY_LIST_H

#include <vector>
#include <string>

#include "city.h"

class CityList {
 public:
  CityList(std::string fname);
  ~CityList();
  void saveToFile(std::string fname);
  size_t getNumCities();
  double getCurrentLength();
  std::vector<City *> &getCities();

  void getDimensions(double &minX, double &minY,
		     double &maxX, double &maxY);
  
 protected:
  std::vector<City *> theCities;
  double min_X;
  double min_Y;
  double max_X;
  double max_Y;
};

#endif
