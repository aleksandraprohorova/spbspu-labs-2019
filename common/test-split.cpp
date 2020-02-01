#include "boost/test/auto_unit_test.hpp"

#include "split.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(split)

BOOST_AUTO_TEST_CASE(splitWork)
{
  prohorova::CompositeShape compositeShapeToSplit;

  std::shared_ptr<prohorova::Rectangle> rectangle1 = std::make_shared<prohorova::Rectangle>(3, 4, 4, 4);
  std::shared_ptr<prohorova::Rectangle> rectangle2 = std::make_shared<prohorova::Rectangle>(5, 6, 2, 2);
  std::shared_ptr<prohorova::Rectangle> rectangle3 = std::make_shared<prohorova::Rectangle>(5, 2, 2, 2);
  std::shared_ptr<prohorova::Circle> circle1 = std::make_shared<prohorova::Circle>(8.5, 3, 1);
  std::shared_ptr<prohorova::Circle> circle2 = std::make_shared<prohorova::Circle>(0, 0, 10);

  compositeShapeToSplit.add(rectangle1);
  compositeShapeToSplit.add(rectangle2);
  compositeShapeToSplit.add(rectangle3);
  compositeShapeToSplit.add(circle1);

  prohorova::Matrix matrix = prohorova::split(compositeShapeToSplit);

  BOOST_CHECK_EQUAL(matrix.getRows(), 2);
  BOOST_CHECK_EQUAL(matrix[0].getSize(), 2);
  BOOST_CHECK_EQUAL(matrix[1].getSize(), 2);

  compositeShapeToSplit.erase(1);
  matrix = prohorova::split(compositeShapeToSplit);
  BOOST_CHECK_EQUAL(matrix.getRows(), 2);
  BOOST_CHECK_EQUAL(matrix[0].getSize(), 2);
  BOOST_CHECK_EQUAL(matrix[1].getSize(), 1);

  compositeShapeToSplit.insert(circle2, 1);
  matrix = prohorova::split(compositeShapeToSplit);
  BOOST_CHECK_EQUAL(matrix.getRows(), 3);
  BOOST_CHECK_EQUAL(matrix[0].getSize(), 2);
  BOOST_CHECK_EQUAL(matrix[1].getSize(), 1);
  BOOST_CHECK_EQUAL(matrix[2].getSize(), 1);
}

BOOST_AUTO_TEST_SUITE_END()
