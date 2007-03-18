#include <QtGui>

#include <cstdlib>
#include <cmath>
#include "threeopt.h"

ThreeOptTsp::ThreeOptTsp() : QObject(), TspSolver() {
  std::srand(std::time(NULL));
  maxSwaps = 5000000;
}

void ThreeOptTsp::solve(std::vector<City *> &theCities) {
  size_t a, b, c;
  size_t d, e, f;
  double oldDistance;
  double newDistance;
  for (size_t i = 0; i<maxSwaps; ++i) {
    b = randUInt(0, theCities.size()-1);
    if (b==0) {
      a = theCities.size()-1;
      c=1;
    } else if (b==theCities.size()-1) {
      a = b-1;
      c=0;
    } else {
      a = b-1;
      c = b+1;
    }

    e = randUInt(0, theCities.size()-1);
    while ( (e==a) || (e == b) || (e ==c))
      e = randUInt(0, theCities.size()-1);
    if (e==0) {
      d = theCities.size()-1;
      f=1;
    } else if (e==theCities.size()-1) {
      d = e-1;
      f=0;
    } else {
      d = e-1;
      f = e+1;
    }
    
    oldDistance = threeCityDistance(theCities, a,b,c) + threeCityDistance(theCities, d,e,f);
    newDistance = threeCityDistance(theCities, a,e,c) + threeCityDistance(theCities, d,b,f);
    if (newDistance<oldDistance) {
      swap(theCities, b,e);
    }
  }
}
double ThreeOptTsp:: threeCityDistance(std::vector<City *> &theCities, size_t a, size_t b, size_t c) {
  double temp1 = theCities[a]->distanceTo(theCities[b]);
  double temp2 = theCities[b]->distanceTo(theCities[c]);
  return (temp1+temp2);
}
void ThreeOptTsp::getConfiguration(QWidget *parent) {
  // Create a dialog box or do something...
  QMessageBox::critical(parent, tr("Not Yet Implemented"),
			tr("Oops! This solver does not yet have a configuration dialog!!"),
			QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);

}

void ThreeOptTsp::swap(std::vector<City *> &theCities, int p1, int p2) {
  City *temp = theCities[p1];
  theCities[p1] = theCities[p2];
  theCities[p2] = temp;
}

size_t ThreeOptTsp::randUInt(size_t min, size_t max) {
  return ((std::rand()%(max-min)) + min);
}

std::string ThreeOptTsp::getName() {
  return "Three Opt";
}
std::string ThreeOptTsp::getDescription() {
  return "Solves a TSP using a three opt. algorithm.";
}

Q_EXPORT_PLUGIN2(threeopt, ThreeOptTsp)
