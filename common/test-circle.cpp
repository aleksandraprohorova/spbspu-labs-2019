#include "boost/test/auto_unit_test.hpp"

#include "circle.hpp"

#define ACCURACY 1e-10

BOOST_AUTO_TEST_SUITE(figureCircle)

BOOST_AUTO_TEST_CASE(CircleInvariantParametersAfterMove)
{
  const prohorova::point_t pos{1.0 / 3, 1.0 / 7};
  const double radius = 2e-7;
  const double dx = 1.5;
  const double dy = 2.5;

  prohorova::Circle testCircle{pos, radius};
  const double area = testCircle.getArea();

  testCircle.move(dx, dy);

  BOOST_CHECK_CLOSE(testCircle.getRadius(), radius, ACCURACY);
  BOOST_CHECK_CLOSE(testCircle.getArea(), area, ACCURACY);
}

BOOST_AUTO_TEST_CASE(CircleInvariantParametersAfterRotate)
{
  const prohorova::point_t pos{1.0 / 3, 1.0 / 7};
  const double radius = 2e-7;

  const double angle = 20;

  prohorova::Circle testCircle{pos, radius};
  const double area = testCircle.getArea();

  testCircle.rotate(angle);

  BOOST_CHECK_CLOSE(testCircle.getRadius(), radius, ACCURACY);
  BOOST_CHECK_CLOSE(testCircle.getArea(), area, ACCURACY);
}

BOOST_AUTO_TEST_CASE(CircleChangeOfParametersAfterScale)
{
  const prohorova::point_t pos{10.0002, 12.0 / 13};
  const double radius = 7e-30;
  const double factor = 1e-10;
  const double newRadius = 7e-40;
  prohorova::Circle testCircle{pos, radius};

  const double area = testCircle.getArea();
  const double newArea = area * factor * factor;

  testCircle.scale(factor);

  BOOST_CHECK_CLOSE(testCircle.getRadius(), newRadius, ACCURACY);
  BOOST_CHECK_CLOSE(testCircle.getArea(), newArea, ACCURACY);
}

BOOST_AUTO_TEST_CASE(CircleIncorrectParameters)
{
  const prohorova::point_t pos{-1, -1};
  const double incorrectRadius = -1;
  const double correctRadius = 1;
  const double incorrectFactor = -2.5;
  prohorova::Circle testCircle{pos, correctRadius};
  
  BOOST_CHECK_THROW(prohorova::Circle incorrectRectangle(pos, incorrectRadius), std::invalid_argument);
  BOOST_CHECK_THROW(testCircle.scale(incorrectFactor), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()
