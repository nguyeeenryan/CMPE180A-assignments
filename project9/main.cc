
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "XYPoint.h"
#include "Shape.h"

using namespace std;

// Helper function to compare floating-point numbers
bool approximatelyEqual(double a, double b) {
    return abs(a - b) < 0.0001;
}

// Helper function to test area calculations
void testArea(const string& name, Shape* shape,
              double expected) {
    double actual = shape->area();

    cout << name << ": ";

    if (approximatelyEqual(actual, expected)) {
        cout << "PASS";
    } else {
        cout << "FAIL";
    }

    cout << " | Expected: " << expected
         << " | Actual: " << actual << endl;
}

// Helper function to test sorting
void testSorting(const string& name,
                 vector<Shape*>& shapes,
                 const vector<double>& expected) {

    ShapeSorter(shapes);

    bool passed = shapes.size() == expected.size();

    if (passed) {
        for (size_t i = 0; i < shapes.size(); i++) {
            if (!approximatelyEqual(
                    shapes[i]->area(), expected[i])) {
                passed = false;
                break;
            }
        }
    }

    cout << name << ": "
         << (passed ? "PASS" : "FAIL") << endl;

    cout << "Sorted areas: ";

    for (Shape* s : shapes) {
        cout << s->area() << " ";
    }

    cout << endl << endl;
}

int main() {

    cout << fixed << setprecision(4);

    // 1. CIRCLE AREA TESTS
    cout << "--- Circle Tests ---" << endl;

    Circle c1(XYpoint(0, 0), 5);
    Circle c2(XYpoint(3, 4), 2);
    Circle c3(XYpoint(-2.5, -3.5), 3.5);

    testArea("Circle radius 5", &c1,
             78.539816);

    testArea("Circle radius 2", &c2,
             12.566371);

    testArea("Circle decimal radius", &c3,
             38.484510);


    // 2. TRIANGLE AREA TESTS
    cout << endl << "--- Triangle Tests ---" << endl;

    Triangle t1(
        XYpoint(0, 0),
        XYpoint(4, 0),
        XYpoint(0, 3)
    );

    Triangle t2(
        XYpoint(-2, -2),
        XYpoint(2, -2),
        XYpoint(0, 2)
    );

    Triangle t3(
        XYpoint(0.5, 0.5),
        XYpoint(3.5, 0.5),
        XYpoint(2, 2.5)
    );

    testArea("Right triangle", &t1, 6);

    testArea("Negative coordinates", &t2, 8);

    testArea("Decimal coordinates", &t3, 3);


    // 3. RECTANGLE AREA TESTS
    cout << endl << "--- Rectangle Tests ---" << endl;

    Rectangle r1(
        XYpoint(0, 0),
        XYpoint(6, 0),
        XYpoint(6, 4),
        XYpoint(0, 4)
    );

    Rectangle r2(
        XYpoint(-1.5, -1.5),
        XYpoint(2.5, -1.5),
        XYpoint(2.5, 1.5),
        XYpoint(-1.5, 1.5)
    );

    // Rotated rectangle
    Rectangle r3(
        XYpoint(0, 0),
        XYpoint(2, 2),
        XYpoint(0, 4),
        XYpoint(-2, 2)
    );

    testArea("Standard rectangle", &r1, 24);

    testArea("Decimal coordinates", &r2, 12);

    testArea("Rotated rectangle", &r3, 8);


    // 4. MIXED SHAPE SORTING
    cout << endl << "--- ShapeSorter Tests ---" << endl;

    vector<Shape*> shapes = {
        &c1, &t1, &r1, &c2, &t2, &r2
    };

    cout << "Before sorting:" << endl;

    for (Shape* s : shapes) {
        cout << s->area() << " ";
    }

    cout << endl << endl;

    testSorting(
        "Mixed shape sorting",
        shapes,
        {6, 8, 12, 12.566371, 24, 78.539816}
    );


    // 5. EQUAL AREA TEST
    cout << "--- Equal Area Test ---" << endl;

    Circle equalCircle(XYpoint(0, 0), 2);

    Triangle equalTriangle(
        XYpoint(0, 0),
        XYpoint(4, 0),
        XYpoint(0, 2 * 3.141592653589793 / 4)
    );

    // The triangle above has area 2*pi/2 = pi,
    // while the circle has area 4*pi.
    // Use a separate shape with area 4*pi instead.

    Triangle equalTriangle2(
        XYpoint(0, 0),
        XYpoint(4 * 3.141592653589793, 0),
        XYpoint(0, 2)
    );

    vector<Shape*> equalShapes = {
        &equalCircle, &equalTriangle2
    };

    testSorting(
        "Equal area sorting",
        equalShapes,
        {12.566371, 12.566371}
    );


    // 6. EMPTY VECTOR TEST
    cout << "--- Empty Vector Test ---" << endl;

    vector<Shape*> emptyShapes;

    ShapeSorter(emptyShapes);

    cout << "Empty vector: "
         << (emptyShapes.empty() ? "PASS" : "FAIL")
         << endl << endl;


    // 7. SINGLE SHAPE TEST
    cout << "--- Single Shape Test ---" << endl;

    vector<Shape*> singleShape = {&c1};

    ShapeSorter(singleShape);

    cout << "Single shape: "
         << (singleShape.size() == 1 &&
             approximatelyEqual(
                 singleShape[0]->area(), c1.area())
             ? "PASS" : "FAIL")
         << endl << endl;



    return 0;
}
