#include <QtGui>

#include <cstdlib>
#include <cmath>
#include "testing.h"

TestingTsp::TestingTsp() : QObject(), TspSolver() {
  std::srand(std::time(NULL));
  maxSwaps = 500000;
  numCities = 4;
}

void TestingTsp::solve(std::vector<City *> &theCities) {
  maxSize = numCities;
  if (maxSize>theCities.size()) {
    maxSize = (theCities.size()/2);
  }
  
  size_t *origPath = new size_t[maxSize];
  size_t *newPath = new size_t[maxSize];

  double oldDistance;
  double newDistance;

  for (size_t i = 0; i<maxSwaps; ++i) {
    size_t crossPoint = 0;
    origPath[0] = randUInt(0, theCities.size()-1);
    for (size_t j = 1; j<maxSize; ++j) {
      if ((origPath[0]+j) >= theCities.size()) {
	origPath[j] = crossPoint;
	++crossPoint;
      } else {
	origPath[j] = origPath[0]+j;
      }
    }
    newPath[0] = randUInt(0, theCities.size()-1);
    while (contains(origPath, newPath[0])) {
      newPath[0] = randUInt(0, theCities.size()-1);
    }
    for (size_t j = 1; j<maxSize; ++j) {
      if ((newPath[0]+j) >= theCities.size()) {
	newPath[j] = crossPoint;
	++crossPoint;
      } else {
	newPath[j] = newPath[0]+j;
      }
    }

    oldDistance = multiCityDistance(theCities, origPath);
    newDistance = multiCityDistance(theCities, newPath);
    if (newDistance<oldDistance) {
      for (size_t i=0;i<maxSize; ++i) {
	swap(theCities, origPath[i], newPath[i]);
      }
    }
  }
  delete[] origPath;
  delete[] newPath;
}
double TestingTsp:: multiCityDistance(std::vector<City *> &theCities,
				      size_t op[]) {
  double temp=0;
  for (size_t i=0;i<maxSize-1; ++i) {
    temp += theCities[op[i]]->distanceTo(theCities[op[i+1]]);
  }
  return temp;
}
void TestingTsp::getConfiguration(QWidget *parent) {
  // Create a dialog box or do something...
  QMessageBox::critical(parent, tr("Not Yet Implemented"),
			tr("Oops! This solver does not yet have a configuration dialog!!"),
			QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);

}

void TestingTsp::swap(std::vector<City *> &theCities, int p1, int p2) {
  City *temp = theCities[p1];
  theCities[p1] = theCities[p2];
  theCities[p2] = temp;
}

size_t TestingTsp::randUInt(size_t min, size_t max) {
  return ((std::rand()%(max-min)) + min);
}

std::string TestingTsp::getName() {
  return "Testing";
}
std::string TestingTsp::getDescription() {
  return "Solves a TSP using a testing algorithm.";
}

bool TestingTsp::contains(size_t op[], size_t val) {
  for (size_t i=0;i<maxSize; ++i) {
    if (op[i] == val) return true;
  }
  return false;
}

Q_EXPORT_PLUGIN2(testing, TestingTsp)
