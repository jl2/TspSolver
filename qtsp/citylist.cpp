
#include <fstream>
#include <cmath>

#include "convert.h"

#include "citylist.h"

CityList::CityList(std::string fname) {
  std::string nextLine;
  std::ifstream inf;

  min_X = 9e99;
  max_X = -9e99;
  min_Y = 9e99;
  max_Y = -9e99;
  double curX;
  double curY;
    
  inf.open(fname.c_str());

  while (std::getline(inf, nextLine)) {
    theCities.
      push_back(
		new City(curX = convertTo<double>(nextLine.substr(0,
							      nextLine.find(" ")),
					      false),
		     curY = convertTo<double>(nextLine.substr(nextLine.find(" ")+1, nextLine.size()))));
    if (curX < min_X) min_X = curX;
    if (curX > max_X) max_X = curX;
    if (curY < min_Y) min_Y = curY;
    if (curY > max_Y) max_Y = curY;
  }
  inf.close();
}

CityList::~CityList() {
  for (std::vector<City *>::iterator iter = theCities.begin();
       iter != theCities.end();
       ++iter) {
    delete (*iter);
  }
  theCities.resize(0);
}

void CityList::saveToFile(std::string fname) {
  std::ofstream outf;
  outf.open(fname.c_str());

  for (std::vector<City *>::iterator iter = theCities.begin();
       iter != theCities.end();
       ++iter) {
    outf << (*iter)->getX() << " " << (*iter)->getY() << "\n";
  }
  outf.close();
}

size_t CityList::getNumCities() {
  return theCities.size();  
}

double CityList::getCurrentLength() {
  double totalLength = 0.0;
  double sqx = 0.0;
  double sqy = 0.0;
  for (std::vector<City>::size_type i = 0; i < theCities.size()-1; ++i) {
    sqx = (theCities[i+1]->getX()-theCities[i]->getX());
    sqy = (theCities[i+1]->getY()-theCities[i]->getY());
    totalLength += std::sqrt(sqx*sqx + sqy*sqy);
  }
  sqx = (theCities[theCities.size()-1]->getX()-theCities[0]->getX());
  sqy = (theCities[theCities.size()-1]->getY()-theCities[0]->getY());
  totalLength += std::sqrt(sqx*sqx + sqy*sqy);
  return totalLength;
}

std::vector<City *> &CityList::getCities() {
  return theCities;  
}

void CityList::getDimensions(double &minX, double &minY,
			     double &maxX, double &maxY) {
  minX = min_X;
  minY = min_Y;
  maxX = max_X;
  maxY = max_Y;
  
}
  
