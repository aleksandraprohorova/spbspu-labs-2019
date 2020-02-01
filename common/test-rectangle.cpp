#include "boost/test/auto_unit_test.hpp"

#include "rectangle.hpp"

#define ACCURACY 1e-10

BOOST_AUTO_TEST_SUITE(figureRectangle)

BOOST_AUTO_TEST_CASE(RectangleInvariantParametersAfterMove)
{
  const prohorova::point_t pos{1, 1};
  const double width = 1.0 / 256;
  const double height = 3;
  const double dx = 1.5;
  const double dy = 2.5;

  prohorova::Rectangle testRectangle{pos, width, height};
  const double area = testRectangle.getArea();

  testRectangle.move(dx, dy);

  BOOST_CHECK_CLOSE(testRectangle.getWidth(), width, ACCURACY);
  BOOST_CHECK_CLOSE(testRectangle.getHeight(), height, ACCURACY);
  BOOST_CHECK_CLOSE(testRectangle.getArea(), area, ACCURACY);
}

BOOST_AUTO_TEST_CASE(RectangleChangeOfParametersAfterScale)
{
  const prohorova::point_t pos{10.123, 20.0001};
  const double width = 3.0 / 1024;
  const double height = 3e-20;
  const double factor = 1.0 / 3;
  const double newWidth = 1.0 / 1024;
  const double newHeight = 1e-20;

  prohorova::Rectangle testRectangle{pos, width, height};
  const double area = testRectangle.getArea();
  const double newArea = area * factor * factor;

  testRectangle.scale(factor);

  BOOST_CHECK_CLOSE(testRectangle.getWidth(), newWidth, ACCURACY);
  BOOST_CHECK_CLOSE(testRectangle.getHeight(), newHeight, ACCURACY);
  BOOST_CHECK_CLOSE(testRectangle.getArea(), newArea, ACCURACY);
}
BOOST_AUTO_TEST_CASE(RectangleChangeOfParametersAfterRotate)
{
  const prohorova::point_t pos{4, 4};
  const double width = 3;
  const double height = 4;
  const double angle = 450;
  const double newWidthOfFrameRect = height;
  const double newHeightOfFrameRect = width;

  prohorova::Rectangle testRectangle{pos, width, height};
  const double area = testRectangle.getArea();

  testRectangle.rotate(angle);

  prohorova::rectangle_t newFrameRect = testRectangle.getFrameRect();

  BOOST_CHECK_CLOSE(newFrameRect.width, newWidthOfFrameRect, ACCURACY);
  BOOST_CHECK_CLOSE(newFrameRect.height, newHeightOfFrameRect, ACCURACY);
  BOOST_CHECK_CLOSE(testRectangle.getArea(), area, ACCURACY);
}

BOOST_AUTO_TEST_CASE(RectangleIncorrectParameters)
{
  const prohorova::point_t pos {1, 1};
  const double correctWidth = 3;
  const double correctHeight = 5;
  const double incorrectWidth = -3;
  const double incorrectHeight = 0;
  const double incorrectFactor = -228;
  prohorova::Rectangle testRectangle{pos, correctWidth, correctHeight};

  BOOST_CHECK_THROW(prohorova::Rectangle incorrectWidthRectangle(pos, incorrectWidth, correctHeight),
      std::invalid_argument);
  BOOST_CHECK_THROW(prohorova::Rectangle incorrectHeightRectangle(pos, correctWidth, incorrectHeight),
      std::invalid_argument);
  BOOST_CHECK_THROW(prohorova::Rectangle incorrectWidthAndHeightRectangle(pos, incorrectWidth, incorrectHeight),
      std::invalid_argument);
  BOOST_CHECK_THROW(testRectangle.scale(incorrectFactor), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
