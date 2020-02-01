#include "boost/test/auto_unit_test.hpp"

#include "rectangle.hpp"
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(shape)

BOOST_AUTO_TEST_CASE(intersects)
{
  std::shared_ptr<prohorova::Rectangle> rectangle1 = std::make_shared<prohorova::Rectangle>(3, 4, 4, 4);
  std::shared_ptr<prohorova::Circle> circle1 = std::make_shared<prohorova::Circle>(1, 2, 1);
  std::shared_ptr<prohorova::Rectangle> rectangle2 = std::make_shared<prohorova::Rectangle>(5, 2, 2, 2);
  std::shared_ptr<prohorova::Circle> circle2 = std::make_shared<prohorova::Circle>(7, 3, 1.5);

  BOOST_CHECK_EQUAL(rectangle1->intersects(circle1), true);
  BOOST_CHECK_EQUAL(rectangle1->intersects(rectangle2), true);
  BOOST_CHECK_EQUAL(rectangle1->intersects(circle2), false);
  BOOST_CHECK_EQUAL(circle1->intersects(rectangle2), false);
  BOOST_CHECK_EQUAL(circle1->intersects(circle2), false);
  BOOST_CHECK_EQUAL(rectangle2->intersects(circle2), true);
  BOOST_CHECK_EQUAL(rectangle2->intersects(rectangle2), false);
}

BOOST_AUTO_TEST_SUITE_END()
