#include <QtGui>
#include <QtOpenGL>
#include <QGLWidget>

#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>
#include "city.h"

class TspDrawer : public QGLWidget {
  Q_OBJECT;

 public:
  TspDrawer(QWidget *parent = 0, double xmin=-1.0, double ymin=-1.0,
	    double xmax=1.0, double ymax=1.0);
  void setDimensions(double xmin, double ymin, double xmax, double ymax);
  void setCities(std::vector<City *> cities);
  void setDrawable(bool d);
 protected:
  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();

 private:
  GLuint listName;
  std::vector<City *> theCities;
  double min_x, min_y;
  double max_x, max_y;
  bool drawable;
};
