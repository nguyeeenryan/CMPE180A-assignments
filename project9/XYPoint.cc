#include "XYPoint.h"

// implementations for XYpoint class

// default to point 0,0
XYpoint::XYpoint() {
  x_ = 0;
  y_ = 0;
}

// constructor that takes in 2 arguments for x and y coordinates
XYpoint::XYpoint(double x, double y) {
  x_ = x;
  y_ = y;
}

// set and return coordinate values
void XYpoint::setX (double x) { x_ = x ;}
void XYpoint::setY (double y) { y_ = y ;}

double XYpoint::getX() const { return x_; }
double XYpoint::getY() const { return y_; }
