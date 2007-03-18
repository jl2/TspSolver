#include <QtGui>

#include <cstdlib>
#include "greedy.h"

GreedyTsp::GreedyTsp() : QObject(), TspSolver() {
  std::srand(std::time(NULL));
}

void GreedyTsp::solve(std::vector<City *> &theCities) {
  swap(theCities, 0, randUInt(0,theCities.size()-1));
  for (size_t i = 0; i < theCities.size()-1; ++i) {
    size_t minIdx = i+1;
    double minLen = theCities[i]->distanceTo(theCities[i+1]);
    for (size_t j = i+1; j < theCities.size()-1; ++j) {
      if (theCities[i]->distanceTo(theCities[j]) < minLen) {
	minLen = theCities[i]->distanceTo(theCities[j]);
	minIdx = j;
      }
    }
    swap(theCities, i+1, minIdx);
  }
}

void GreedyTsp::getConfiguration(QWidget *parent=0) {
  // Create a dialog box or something...
  QMessageBox::critical(parent, tr("No Configuration Options"),
			tr("This solver does not have any configuration options!"),
			QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
}

void GreedyTsp::swap(std::vector<City *> &theCities, int p1, int p2) {
  City *temp = theCities[p1];
  theCities[p1] = theCities[p2];
  theCities[p2] = temp;
}

size_t GreedyTsp::randUInt(size_t min, size_t max) {
  return ((std::rand()%(max-min)) + min);
}

std::string GreedyTsp::getName() {
  return "Greedy";
}
std::string GreedyTsp::getDescription() {
  return "Solves a TSP using a greedy algorithm choosing the closest city to the current one.";
}

Q_EXPORT_PLUGIN2(greedy, GreedyTsp)
