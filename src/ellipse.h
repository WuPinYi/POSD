#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"
#include<math.h>
#include <sstream>
using namespace std;

class Ellipse:public Shape
{
public:
    Ellipse(double semiMajorAxes,double semiMinorAxes): _semiMajorAxes(semiMajorAxes), _semiMinorAxes(semiMinorAxes)
    {

    }
    // calculate area
    double area() const{
        return M_PI * _semiMajorAxes * _semiMinorAxes;
    }
    // calculate perimeter 
    // perimeter formula: 2π * semiMinorAxes + 4(semiMajorAxes-semiMinorAxes)
    double perimeter() const{
        return 2 * M_PI * _semiMinorAxes + 4 * (_semiMajorAxes-_semiMinorAxes);
    } 
    // calculate sum of squares
    double sumOfSquares() const
    {
        return pow(area(),2) + pow(perimeter(),2);
    }
private:
    double _semiMajorAxes;
    double _semiMinorAxes;
};
#endif