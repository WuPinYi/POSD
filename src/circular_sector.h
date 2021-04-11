#ifndef CIRCULARSECTOR_H
#define CIRCULARSECTOR_H

#include "shape.h"
#include<math.h>
#include <sstream>
using namespace std;

class CircularSector:public Shape
{
 public:
     CircularSector(double radius, double degree): _radius(radius), _degree(degree)
     {

     }
     // calculate area
     double area() const
     {
         return M_PI * _radius * _radius * _degree / 360;
     }
     // calculate perimeter
     double perimeter() const
     {
         return 2 * M_PI * _radius * _degree / 360 + 2 * _radius; 
     }
private:
    double _radius;
    double _degree;
};

#endif