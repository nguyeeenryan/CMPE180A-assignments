#ifndef SHAPE_H
#define SHAPE_H

#include "XYPoint.h"
#include <vector>

// abstract base class
class Shape {
public:
    virtual double area() const = 0;

    virtual ~Shape() = default;
};

// circle class
class Circle : public Shape {
public:
    Circle(XYpoint center, double radius);

    double area() const override;

private:
    XYpoint center_;
    double radius_;
};

// triangle class
class Triangle : public Shape {
public:
    Triangle(XYpoint p1, XYpoint p2, XYpoint p3);

    double area() const override;

private:
    XYpoint p1_;
    XYpoint p2_;
    XYpoint p3_;
};

// rectangle class
class Rectangle : public Shape {
public:
    Rectangle(XYpoint p1, XYpoint p2,
              XYpoint p3, XYpoint p4);

    double area() const override;

private:
    XYpoint p1_;
    XYpoint p2_;
    XYpoint p3_;
    XYpoint p4_;
};

// sort shapes by area
void ShapeSorter(std::vector<Shape*>& shapes);

#endif
