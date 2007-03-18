#ifndef TESTING_TSP_H
#define TESTING_TSP_H

#include <QObject>
#include <QWidget>

#include "../../qtsp/tspsolver.h"

class TestingTsp : public QObject, public TspSolver {
  Q_OBJECT;
  Q_INTERFACES(TspSolver);
  
 public:
  TestingTsp();
  void solve(std::vector<City *> &cities);
  void getConfiguration(QWidget *parent);
  
  std::string getName();
  std::string getDescription();
  
 private:
  void swap(std::vector<City *> &theCities, int p1, int p2);
  size_t randUInt(size_t min, size_t max);
  double multiCityDistance(std::vector<City *> &theCities, size_t op[]);
  bool contains(size_t op[], size_t val);
  size_t maxSwaps;
  size_t numCities;
  size_t maxSize;
};

#endif
