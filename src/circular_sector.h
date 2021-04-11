#ifndef CIRCULAR_SECTOR_H
#define CIRCULAR_SECTOR_H

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
    // calculate sum of squares
    double sumOfSquares() const
    {
        return pow(area(),2) + pow(perimeter(),2);
    }
private:
    double _radius;
    double _degree;
};

#endif