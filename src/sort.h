#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include "shape.h"
#include <vector>
#include <math.h>
using namespace std;
class Sort{
  public:
    Sort(std::vector<Shape*>* v): _v(v){}
    // The argument ** Accept comparison ** can accept lambda, function, and object
    template<typename Compare>
    // sort area
    void sortArea(Compare compare)// you can use std:sort in this function
    {
      std:sort(_v->begin(), _v->end(), compare);
    }
    // sort perimeter
    template<typename Compare>  
    void sortPerimeter(Compare compare)// you can use std:sort in this function
    {
      std:sort(_v->begin(), _v->end(), compare);
    }
    //sort sum of squares
    template<typename Compare>
    void sortSumOfSquares(Compare compare)// you can use std:sort in this function
    {
      std:sort(_v->begin(), _v->end(), compare);
    }
    //quickSort
    template<typename Compare>
    void quickSort(Compare compare)
    {
      sortShape(compare,0, _v->size()-1);
    }
    
  private:
    std::vector<Shape*>* _v;
    // quickSort partition
    template<typename Compare>
    int partition (Compare compare, int start, int end) 
    {
      int i = start -1;
      for(std::vector<Shape*>::iterator it = _v->begin()+ start; it != _v->begin()+end;it++)
      {
        if(compare(*it, *(_v->begin() + end)))
        {
          i++;
          std::iter_swap(_v->begin() + i,it);
        }
      }
      i++;
      std::iter_swap(_v->begin() + i,_v->begin() + end);
      return i;
    }
    
    template<typename Compare>
    void sortShape(Compare compare, int start, int end)
    {
      if(start < end)
      {
        int pivot = partition(compare,start,end);
        sortShape(compare,start,pivot-1);
        sortShape(compare,pivot+1,end);
      }
    }

};

// implement following call back function
// compare area (ascending)
bool areaAscendingComparison(Shape *a, Shape *b)
{
  return a->area() < b-> area();
};
// compare area (descending)
bool areaDescendingComparison(Shape *a, Shape *b)
{
  return a->area() > b-> area();
};

// compare perimeter (ascending)
bool perimeterAscendingComparison(Shape *a, Shape *b)
{
  return a->perimeter() < b-> perimeter();
};
// compare perimeter (descending)
bool perimeterDescendingComparison(Shape *a, Shape *b)
{
  return a->perimeter() > b-> perimeter();
};



//AscendingComparison
class AscendingComparison{
  public:
    AscendingComparison(string status):_status(status){}
    bool operator()(Shape* a,Shape* b)
    {
      if (_status == "area") return a->area() < b->area();
      else if(_status == "perimeter") return a->perimeter() < b->perimeter();
      else if(_status == "sumOfSquares") return a->sumOfSquares() < b->sumOfSquares();
    }
    
  private:
    string _status;
};
// DescendingComparison
class DescendingComparison{
  public:
    DescendingComparison(string status):_status(status){}
    bool operator()(Shape* a,Shape* b)
    {
      if (_status == "area") return a->area() > b->area();
      else if(_status == "perimeter") return a->perimeter() > b->perimeter();
      else if(_status == "sumOfSquares") return a->sumOfSquares() > b->sumOfSquares();
    }
  private:
    string _status;
};
#endif