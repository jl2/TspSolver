#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include "citylist.h"

class QWidget;

class TspSolver {
 public:
  //  TspSolver();
  virtual ~TspSolver() { }
  virtual std::string getName()=0;
  virtual std::string getDescription()=0;
  
  virtual void solve(std::vector<City *> &cities)=0;
  virtual void getConfiguration(QWidget *parent=0)=0;
};

Q_DECLARE_INTERFACE(TspSolver,
		    "net.jlarocco.TspSolver/1.0")
     
#endif


