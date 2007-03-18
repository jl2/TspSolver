#include <QApplication>

#include "qtsp.h"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QTsp tsp;
  tsp.showMaximized();
  return app.exec();
}
