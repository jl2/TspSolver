#ifndef GREEDY_TSP_H
#define GREEDY_TSP_H

#include <QObject>
#include <QWidget>

#include "../../qtsp/tspsolver.h"

class GreedyTsp : public QObject, public TspSolver {
  Q_OBJECT;
  Q_INTERFACES(TspSolver);
  
 public:
  GreedyTsp();
  void solve(std::vector<City *> &cities);
  void getConfiguration(QWidget *parent);
  
  std::string getName();
  std::string getDescription();
 private:
  void swap(std::vector<City *> &theCities, int p1, int p2);
  size_t randUInt(size_t min, size_t max);
};

#endif
