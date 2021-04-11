#include <gtest/gtest.h>
#include "../src/shape.h"
#include "../src/circular_sector.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"
#include <algorithm>

using namespace std;

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST (ShapeTest, first)
{
  ASSERT_TRUE(true);
}

// Test CircularSector
TEST (ShapeTest, CircularSector)
{
  CircularSector c(10.0,180.0);
  ASSERT_NEAR(157.079, c.area(), 0.001);
  ASSERT_NEAR(51.415, c.perimeter(), 0.001);
}

// Test Isosceles Triangle
TEST (ShapeTest, Triangle)
{
    Triangle t(0, 0, 0, 3, 3, 0);
    ASSERT_NEAR(4.5, t.area(), 0.001);
    ASSERT_NEAR(10.242, t.perimeter(), 0.001);   
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
}