#include <gtest/gtest.h>
#include "../src/shape.h"
#include "../src/circular_sector.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"
#include "../src/sort.h"
#include "../src/terminal.h"
#include <algorithm>

using namespace std;

// init
vector<Shape*>* testInitialize() {
  std::vector<Shape*>* shapes = new std::vector<Shape*>();
  shapes->push_back(new CircularSector(10,180));
  shapes->push_back(new Triangle(0, 0, 0, 3, 3, 0));
  shapes->push_back(new Ellipse(5,3));
  return shapes;
}
// Test CircularSector
TEST (ShapeTest, CircularSector)
{
  CircularSector c(10.0,180.0);
  ASSERT_NEAR(157.079, c.area(), 0.001);
  ASSERT_NEAR(51.415, c.perimeter(), 0.001);
  ASSERT_NEAR(27317.608,c.sumOfSquares(),0.001);
}

// Test Isosceles Triangle
TEST (ShapeTest, Triangle)
{
  Triangle t(0, 0, 0, 3, 3, 0);
  ASSERT_NEAR(4.5, t.area(), 0.001);
  ASSERT_NEAR(10.242, t.perimeter(), 0.001);   
  ASSERT_NEAR(125.161, t.sumOfSquares(), 0.001);   
}

// Test not Isosceles Triangle
TEST (ShapeTest, isIsoscelesTriangle)
{
  try {
      Triangle t(0, 0, 0, 3, 4, 0);
  } catch(string exception) {
      ASSERT_EQ(std::string("Not a IsoscelesTriangle."), exception);
  }
}
// Test Ellipse
TEST (ShapeTest, Ellipse)
{
  Ellipse e(5,3);
  ASSERT_NEAR(47.123, e.area(), 0.001);
  ASSERT_NEAR(26.849, e.perimeter(), 0.001);
  ASSERT_NEAR(2941.559, e.sumOfSquares(), 0.001);
}

//----------Area----------
// Test SortAreaAscendingByFunction
TEST (SortTest, SortAreaAscendingByFunction)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortArea(areaAscendingComparison);
  ASSERT_NEAR(4.5,(*shapes)[0]->area(),0.001);
  ASSERT_NEAR(47.123,(*shapes)[1]->area(),0.001);
  ASSERT_NEAR(157.079,(*shapes)[2]->area(),0.001);
}

// Test SortAreaAscendingByObject
TEST (SortTest, SortAreaAscendingByObject)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortArea(AscendingComparison("area"));
  ASSERT_NEAR(4.5,(*shapes)[0]->area(),0.001);
  ASSERT_NEAR(47.123,(*shapes)[1]->area(),0.001);
  ASSERT_NEAR(157.079,(*shapes)[2]->area(),0.001);
}

// Test SortAreaAscendingByLambda
TEST (SortTest, SortAreaAscendingByLambda)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortArea([](Shape* a,Shape* b){return a->area() < b->area();});
  ASSERT_NEAR(4.5,(*shapes)[0]->area(),0.001);
  ASSERT_NEAR(47.123,(*shapes)[1]->area(),0.001);
  ASSERT_NEAR(157.079,(*shapes)[2]->area(),0.001);
}

// Test SortAreaDescendingByFunction 
TEST (SortTest, SortAreaDescendingByFunction)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortArea(areaDescendingComparison);
  ASSERT_NEAR(157.079,(*shapes)[0]->area(),0.001);
  ASSERT_NEAR(47.123,(*shapes)[1]->area(),0.001);
  ASSERT_NEAR(4.5,(*shapes)[2]->area(),0.001);
}

// Test SortAreaDescendingByObject
TEST (SortTest, SortAreaDescendingByObject)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortArea(DescendingComparison("area"));
  ASSERT_NEAR(157.079,(*shapes)[0]->area(),0.001);
  ASSERT_NEAR(47.123,(*shapes)[1]->area(),0.001);
  ASSERT_NEAR(4.5,(*shapes)[2]->area(),0.001);
}

// Test SortAreaDescendingByLambda
TEST (SortTest, SortAreaDescendingByLambda)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortArea([](Shape* a,Shape* b){return a->area() > b->area();});
  ASSERT_NEAR(157.079,(*shapes)[0]->area(),0.001);
  ASSERT_NEAR(47.123,(*shapes)[1]->area(),0.001);
  ASSERT_NEAR(4.5,(*shapes)[2]->area(),0.001);
}

//----------Perimeter----------
// Test SortPerimeterAscendingByFunction
TEST (SortTest, SortPerimeterAscendingByFunction)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortPerimeter(perimeterAscendingComparison);
  ASSERT_NEAR(10.242,(*shapes)[0]->perimeter(),0.001);
  ASSERT_NEAR(26.849,(*shapes)[1]->perimeter(),0.001);
  ASSERT_NEAR(51.415,(*shapes)[2]->perimeter(),0.001);
}

// Test SortPerimeterAscendingByObject
TEST (SortTest, SortPerimeterAscendingByObject)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortPerimeter(AscendingComparison("perimeter"));
  ASSERT_NEAR(10.242,(*shapes)[0]->perimeter(),0.001);
  ASSERT_NEAR(26.849,(*shapes)[1]->perimeter(),0.001);
  ASSERT_NEAR(51.415,(*shapes)[2]->perimeter(),0.001);
}

// Test SortAreaAscendingByLambda
TEST (SortTest, SortPerimeterAscendingByLambda)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortPerimeter([](Shape* a,Shape* b){return a->perimeter() < b->perimeter();});
  ASSERT_NEAR(10.242,(*shapes)[0]->perimeter(),0.001);
  ASSERT_NEAR(26.849,(*shapes)[1]->perimeter(),0.001);
  ASSERT_NEAR(51.415,(*shapes)[2]->perimeter(),0.001);
}

// Test SortPerimeterDescendingByFunction 
TEST (SortTest, SortPerimeterDescendingByFunction)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortPerimeter(perimeterDescendingComparison);
  ASSERT_NEAR(51.415,(*shapes)[0]->perimeter(),0.001);
  ASSERT_NEAR(26.849,(*shapes)[1]->perimeter(),0.001);
  ASSERT_NEAR(10.242,(*shapes)[2]->perimeter(),0.001);
}

// Test SortPerimeterDescendingByObject
TEST (SortTest, SortPerimeterDescendingByObject)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortPerimeter(DescendingComparison("perimeter"));
  ASSERT_NEAR(51.415,(*shapes)[0]->perimeter(),0.001);
  ASSERT_NEAR(26.849,(*shapes)[1]->perimeter(),0.001);
  ASSERT_NEAR(10.242,(*shapes)[2]->perimeter(),0.001);
}

// Test SortPerimeterDescendingByLambda
TEST (SortTest, SortPerimeterDescendingByLambda)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortPerimeter([](Shape* a,Shape* b){return a->perimeter() > b->perimeter();});
  ASSERT_NEAR(51.415,(*shapes)[0]->perimeter(),0.001);
  ASSERT_NEAR(26.849,(*shapes)[1]->perimeter(),0.001);
  ASSERT_NEAR(10.242,(*shapes)[2]->perimeter(),0.001);
}

//----------SumOfSquares----------
// Test SortSumOfSquaresAscendingByLambda
TEST (SortTest, SortSumOfSquaresAscendingByLambda)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortSumOfSquares([](Shape* a,Shape* b){return a->sumOfSquares() < b->sumOfSquares();});
  ASSERT_NEAR(125.161,(*shapes)[0]->sumOfSquares(),0.001);
  ASSERT_NEAR(2941.559,(*shapes)[1]->sumOfSquares(),0.001);
  ASSERT_NEAR(27317.608,(*shapes)[2]->sumOfSquares(),0.001);
}
// Test SortSumOfSquaresDescendingByLambda
TEST (SortTest, SortSumOfSquaresDescendingByLambda)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->sortSumOfSquares([](Shape* a,Shape* b){return a->sumOfSquares() > b->sumOfSquares();});
  ASSERT_NEAR(27317.608,(*shapes)[0]->sumOfSquares(),0.001);
  ASSERT_NEAR(2941.559,(*shapes)[1]->sumOfSquares(),0.001);
  ASSERT_NEAR(125.161,(*shapes)[2]->sumOfSquares(),0.001);
}

//----------quickSort----------
//Test quickSort
TEST (SortTest, SortAreaAscendingByQuickSort)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->quickSort(areaAscendingComparison);
  ASSERT_NEAR(4.5,(*shapes)[0]->area(),0.001);
  ASSERT_NEAR(47.123,(*shapes)[1]->area(),0.001);
  ASSERT_NEAR(157.079,(*shapes)[2]->area(),0.001);
}

// Test QuickSortAreaAscendingByLambda
TEST (SortTest, QuickSortAreaAscendingByLambda)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->quickSort([](Shape* a,Shape* b){return a->area() < b->area();});
  ASSERT_NEAR(4.5,(*shapes)[0]->area(),0.001);
  ASSERT_NEAR(47.123,(*shapes)[1]->area(),0.001);
  ASSERT_NEAR(157.079,(*shapes)[2]->area(),0.001);
}
// Test SortSumOfSquaresAreaDescendingByLambda
TEST (SortTest, QuickSortAreaDescendingByLambda)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->quickSort([](Shape* a,Shape* b){return a->area() > b->area();});
  ASSERT_NEAR(157.079,(*shapes)[0]->area(),0.001);
  ASSERT_NEAR(47.123,(*shapes)[1]->area(),0.001);
  ASSERT_NEAR(4.5,(*shapes)[2]->area(),0.001);
}
// Test QuickSortPerimeterDescendingByObject
TEST (SortTest, QuickSortPerimeterDescendingByObject)
{
  std::vector<Shape*>* shapes = testInitialize();
  Sort* sort = new Sort(shapes);
  sort->quickSort(DescendingComparison("perimeter"));
  ASSERT_NEAR(51.415,(*shapes)[0]->perimeter(),0.001);
  ASSERT_NEAR(26.849,(*shapes)[1]->perimeter(),0.001);
  ASSERT_NEAR(10.242,(*shapes)[2]->perimeter(),0.001);
}

TEST(TerminalTest, InvalidArgument) {
    Terminal* test = new Terminal("Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc !@#$%%");
    ASSERT_EQ("[6.000000, 22.340214, 94.247780]", test->showResult());
}

TEST(TerminalTest, InputLowercase) {
    Terminal* t = new Terminal("Ellipse (6,5) triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc");
    ASSERT_EQ("[22.340214, 94.247780]", t->showResult());
}

TEST(TerminalTest, InputWithSpace) {
    Terminal* t = new Terminal("Ellipse (6  ,   5) Triangle (3  ,0    ,  0  , 2,  -3,0) CircularSector (8  ,  40) area inc");
    ASSERT_EQ("[6.000000, 22.340214, 94.247780]", t->showResult());
}

TEST(TerminalTest, AreaDescending) {
    Terminal* test = new Terminal("Triangle (-2,0,0,3,2,0) Triangle (-2,0,0,6,2,0) area dec");
    ASSERT_EQ("[12.000000, 6.000000]", test->showResult());
}

TEST(TerminalTest, AreaAscending) {
    Terminal* test = new Terminal("Triangle (-2,0,0,3,2,0) Triangle (-2,0,0,6,2,0) area inc");
    ASSERT_EQ("[6.000000, 12.000000]", test->showResult());
}

TEST(TerminalTest, SumOfSquaresAscending) {
    Terminal* test = new Terminal("Ellipse (3, 4) CircularSector (10, 60) Triangle (0, 0, 6, 0, 3, 3) sumOfSquares inc");
    ASSERT_EQ("[290.823376, 1867.815786, 3670.098070]", test->showResult());
}

TEST(TerminalTest, InvalidArgumentNumber) {
    Terminal* test = new Terminal("Triangle (-2,0,0,3,2,0,1) Triangle (-2,0,0,6,2,0) area inc");
    ASSERT_EQ("[12.000000]", test->showResult());
    Terminal* test2 = new Terminal("Ellipse (6,5) Triangle (3,0,0) CircularSector (8,40) area inc");
    ASSERT_EQ("[22.340214, 94.247780]", test2->showResult());
}

TEST(TerminalTest, UnusefulInput) {
    try {
        Terminal* test = new Terminal("Ellipse(6,5) triangle(-3,0,0,2,3,0) CircularSector(8,40) area");
    } catch (string exception) {
        ASSERT_EQ(string("Unuseful User Input!"), exception);
    }
    try {
        Terminal* test2 = new Terminal("Ellipse(6,5) triangle(-3,0,0,2,3,0) CircularSector(8,40) inc");
    } catch (string exception) {
        ASSERT_EQ(string("Unuseful User Input!"), exception);
    }
    try {
        Terminal* test3 = new Terminal("Ellipse(6,5) triangle(3,0,0,2,-3,0) CircularSector(8,40)");
    } catch (string exception) {
        ASSERT_EQ(string("Unuseful User Input!"), exception);
    }
    try {
        Terminal* test4 = new Terminal("area inc");
    } catch (string exception) {
        ASSERT_EQ(string("Unuseful User Input!"), exception);
    }
    try {
        Terminal* test5 = new Terminal("inc");
    } catch (string exception) {
        ASSERT_EQ(string("Unuseful User Input!"), exception);
    }
    try {
        Terminal* test6 = new Terminal("");
    } catch (string exception) {
        ASSERT_EQ(string("Unuseful User Input!"), exception);
    }
}
