#include <QMainWindow>
#include "tspdrawer.h"
#include <cmath>
#include <iostream>

TspDrawer::TspDrawer(QWidget *parent, double xmin, double ymin,
		     double xmax, double ymax) : QGLWidget(parent),
						 min_x(xmin), min_y(ymin),
						 max_x(xmax), max_y(ymax),
						 drawable(false) {
  setFormat(QGLFormat(QGL::DoubleBuffer));
}
void TspDrawer::initializeGL() {
  qglClearColor(Qt::white);
  glShadeModel(GL_SMOOTH);
}

void TspDrawer::resizeGL(int width, int height) {
  glViewport(0,0, (GLsizei) width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(min_x, max_x,
	     min_y, max_y);
  glMatrixMode(GL_MODELVIEW);

  glClear(GL_COLOR_BUFFER_BIT);
}

void TspDrawer::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT);

  glLoadIdentity();
  glPushMatrix();
  glLoadIdentity();

  glColor3f(0.0,0.0,0.0);

  if (drawable) {
    if (theCities.size()) {
      glBegin(GL_LINE_LOOP);
      {
	for (size_t i = 0; i<theCities.size(); ++i) {
	  glVertex2f(theCities[i]->getX(),
		     theCities[i]->getY());
	}
      }
      glEnd();
    }
  }
  glFlush();
}

void TspDrawer::setDimensions(double xmin, double ymin, double xmax, double ymax) {
  min_x = xmin;
  min_y = ymin;
  max_x = xmax;
  max_y = ymax;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(min_x, max_x,
	     min_y, max_y);
  glMatrixMode(GL_MODELVIEW);

  glClear(GL_COLOR_BUFFER_BIT);
  updateGL();
}

void TspDrawer::setCities(std::vector<City *> cities) {
  theCities = cities;
  updateGL();
}
void TspDrawer::setDrawable(bool d) {
  drawable=d;
  updateGL();
}
