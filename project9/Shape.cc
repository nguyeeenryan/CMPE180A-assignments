#include "Shape.h"
#include <cmath>
#include <algorithm>

// circle 
Circle::Circle(XYpoint center, double radius) {
    center_ = center;
    radius_ = radius;
}

double Circle::area() const {
    return std::acos(-1.0) * radius_ * radius_;
}

// triangle 
Triangle::Triangle(XYpoint p1, XYpoint p2, XYpoint p3) {
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;
}

double Triangle::area() const {
    double result =
        p1_.getX() * (p2_.getY() - p3_.getY()) +
        p2_.getX() * (p3_.getY() - p1_.getY()) +
        p3_.getX() * (p1_.getY() - p2_.getY());

    return std::abs(result) / 2.0;
}

// rectangle 
Rectangle::Rectangle(XYpoint p1, XYpoint p2,
                     XYpoint p3, XYpoint p4) {
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;
    p4_ = p4;
}

double Rectangle::area() const {
    double result =
        p1_.getX() * p2_.getY() +
        p2_.getX() * p3_.getY() +
        p3_.getX() * p4_.getY() +
        p4_.getX() * p1_.getY() -
        p1_.getY() * p2_.getX() -
        p2_.getY() * p3_.getX() -
        p3_.getY() * p4_.getX() -
        p4_.getY() * p1_.getX();

    return std::abs(result) / 2.0;
}

// shapeSorter 
void ShapeSorter(std::vector<Shape*>& shapes) {
    std::sort(shapes.begin(), shapes.end(),
        [](Shape* a, Shape* b) {
            return a->area() < b->area();
        }
    );
}
