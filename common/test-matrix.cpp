#include "boost/test/auto_unit_test.hpp"

#include "matrix.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(matrix)

BOOST_AUTO_TEST_CASE(matrixWork)
{
  std::shared_ptr<prohorova::Rectangle> rectangle1 = std::make_shared<prohorova::Rectangle>(3, 4, 4, 4);
  std::shared_ptr<prohorova::Rectangle> rectangle2 = std::make_shared<prohorova::Rectangle>(5, 6, 2, 2);
  std::shared_ptr<prohorova::Rectangle> rectangle3 = std::make_shared<prohorova::Rectangle>(5, 2, 2, 2);
  std::shared_ptr<prohorova::Circle> circle1 = std::make_shared<prohorova::Circle>(8.5, 3, 1);
  std::shared_ptr<prohorova::Circle> circle2 = std::make_shared<prohorova::Circle>(0, 0, 10);
  std::shared_ptr<prohorova::Circle> circle3 = std::make_shared<prohorova::Circle>(0.5, 0.6, 0.7);

  prohorova::Matrix matrix;
  matrix.add(rectangle1, 0);
  matrix.add(rectangle2, 1);
  matrix.add(rectangle3, 1);
  matrix.add(circle1, 2);
  matrix.add(circle2, 2);
  matrix.add(circle3, 3);

  BOOST_CHECK_EQUAL(matrix.getRows(), 4);
  BOOST_CHECK_EQUAL(matrix[0].getSize(), 1);
  BOOST_CHECK_EQUAL(matrix[1].getSize(), 2);
  BOOST_CHECK_EQUAL(matrix[2].getSize(), 2);
  BOOST_CHECK_EQUAL(matrix[3].getSize(), 1);

}

BOOST_AUTO_TEST_CASE(matrixIncorrectParameters)
{
  std::shared_ptr<prohorova::Rectangle> rectangle1 = std::make_shared<prohorova::Rectangle>(3, 4, 4, 4);
  std::shared_ptr<prohorova::Rectangle> rectangle2 = std::make_shared<prohorova::Rectangle>(5, 6, 2, 2);
  std::shared_ptr<prohorova::Rectangle> rectangle3 = std::make_shared<prohorova::Rectangle>(5, 2, 2, 2);
  std::shared_ptr<prohorova::Circle> circle1 = std::make_shared<prohorova::Circle>(8.5, 3, 1);
  std::shared_ptr<prohorova::Circle> circle2 = std::make_shared<prohorova::Circle>(0, 0, 10);
  std::shared_ptr<prohorova::Circle> circle3 = std::make_shared<prohorova::Circle>(0.5, 0.6, 0.7);

  prohorova::Matrix matrix;
  matrix.add(rectangle1, 0);
  matrix.add(rectangle2, 1);
  matrix.add(rectangle3, 1);
  matrix.add(circle1, 2);
  matrix.add(circle2, 2);
  matrix.add(circle3, 3);
   
  BOOST_CHECK_THROW(matrix[5][1], std::out_of_range);
  BOOST_CHECK_THROW(matrix[1][7], std::out_of_range);
  BOOST_CHECK_THROW(matrix[matrix.getRows()][matrix[0].getSize() + 1], std::out_of_range);

}
BOOST_AUTO_TEST_SUITE_END()
