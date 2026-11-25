#ifndef XYPoint_h
#define XYPoint_h

class XYpoint {
 public:
  // default constructor and constructor with args
  XYpoint();
  XYpoint(double x, double y);

  void setX (double x);
  void setY (double y);

  double getX() const;
  double getY() const;
  
 private:
  double x_;
  double y_;
};

#endif
