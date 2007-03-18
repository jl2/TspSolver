#ifndef THREE_OPT_TSP_H
#define THREE_OPT_TSP_H

#include <QObject>
#include <QWidget>

#include "../../qtsp/tspsolver.h"

class ThreeOptTsp : public QObject, public TspSolver {
  Q_OBJECT;
  Q_INTERFACES(TspSolver);
  
 public:
  ThreeOptTsp();
  void solve(std::vector<City *> &cities);
  void getConfiguration(QWidget *parent);
  
  std::string getName();
  std::string getDescription();
  
 private:
  void swap(std::vector<City *> &theCities, int p1, int p2);
  size_t randUInt(size_t min, size_t max);
  double threeCityDistance(std::vector<City *> &theCities, size_t a, size_t b, size_t c);
  size_t maxSwaps;
};

#endif
