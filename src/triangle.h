#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"
#include<math.h>
#include <sstream>
#include <string>
using namespace std;

class Triangle:public Shape
{
public:
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3): _x1(x1), _y1(y1), _x2(x2), _y2(y2), _x3(x3), _y3(y3)
    {
        // calculate each side of Triangle
        side1 = sqrt(pow(_x1 - _x2,2) + pow(_y1 - _y2,2));
        side2 = sqrt(pow(_x2 - _x3,2) + pow(_y2 - _y3,2));
        side3 = sqrt(pow(_x1 - _x3,2) + pow(_y1 - _y3,2));
        s = (side1 + side2 + side3)/2;

        // determine is Triangle or not
        if(!isIsoscelesTriangle())
        {
            throw std::string("Not a IsoscelesTriangle.");
        }
    }
    // give you three points (x1,y1), (x2,y2), (x3,y3) to calculate area and perimeter
    // calculate area
    double area() const
    {
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }
    // calculate perimeter
    double perimeter() const
    {
        return side1 + side2 + side3;
    }
    // calculate sum of squares
    double sumOfSquares() const
    {
        return pow(area(),2) + pow(perimeter(),2);
    }
    // determine is Isosceles or is not Triangle
    bool isIsoscelesTriangle()
    {
        if ((side1 == side2 || side2 == side3 || side1 == side3)&& !(((side1 + side2) == side3) || ((side2 + side3) == side1) || ((side1 + side3) == side2))) return true;
        else return false;
    }

private:
    double _x1;
    double _y1;
    double _x2;
    double _y2;
    double _x3;
    double _y3;
    double side1;
    double side2;
    double side3;
    double s;
};
#endif