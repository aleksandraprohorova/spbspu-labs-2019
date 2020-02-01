#include "boost/test/auto_unit_test.hpp"
#include "composite-shape.hpp"

#include <cmath>

#include "circle.hpp"
#include "rectangle.hpp"

#define ACCURACY 1e-10

BOOST_AUTO_TEST_SUITE(CompositeShape)

BOOST_AUTO_TEST_CASE(CompositeShapeInvariantParametersAfterMove)
{

  prohorova::CompositeShape compositeShape;
  
  std::shared_ptr<prohorova::Rectangle> rectangle1 = std::make_shared<prohorova::Rectangle>(20, 40, 3, 6);
  std::shared_ptr<prohorova::Rectangle> rectangle2 = std::make_shared<prohorova::Rectangle>(-20, -40, 1, 1);
  std::shared_ptr<prohorova::Circle> circle1 = std::make_shared<prohorova::Circle>(-20, 40, 3);
  std::shared_ptr<prohorova::Circle> circle2 = std::make_shared<prohorova::Circle>(20, -40, 1);

  const prohorova::point_t newPos{10,15};

  compositeShape.add(rectangle1);
  compositeShape.add(rectangle2);
  compositeShape.add(circle1);
  compositeShape.add(circle2);
  const double area = compositeShape.getArea();
  const prohorova::rectangle_t frameRect = compositeShape.getFrameRect();

  compositeShape.move(newPos);

  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameRect.width, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameRect.height, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area, ACCURACY);
}

BOOST_AUTO_TEST_CASE(CompositeShapeChangeOfParametersAfterScale)
{
  prohorova::CompositeShape compositeShape;
  std::shared_ptr<prohorova::Rectangle> rectangle1 = std::make_shared<prohorova::Rectangle>(0.5, 2.5, 5.5, 6.5);
  std::shared_ptr<prohorova::Rectangle> rectangle2 = std::make_shared<prohorova::Rectangle>(-0.5, -2.5, 1, 1);
  std::shared_ptr<prohorova::Circle> circle1 = std::make_shared<prohorova::Circle>(-0.5, 2.5, 3);
  std::shared_ptr<prohorova::Circle> circle2 = std::make_shared<prohorova::Circle>(0.5, -2.5, 1);

  const double factor = 10;

  compositeShape.add(rectangle1);
  compositeShape.add(rectangle2);
  compositeShape.add(circle1);
  compositeShape.add(circle2);

  const double area = compositeShape.getArea();
  const double newArea = area * factor * factor;
  prohorova::rectangle_t frameRect = compositeShape.getFrameRect();
  const double newWidth = frameRect.width * factor;
  const double newHeight = frameRect.height * factor;

  compositeShape.scale(factor);

  BOOST_CHECK_CLOSE(compositeShape.getPos().x, frameRect.pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getPos().y, frameRect.pos.y, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, newWidth, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, newHeight, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), newArea, ACCURACY);
}
BOOST_AUTO_TEST_CASE(CompositeShapeChangeOfParametersAfterRotate)
{
  prohorova::CompositeShape compositeShape;
  std::shared_ptr<prohorova::Rectangle> rectangle1 = std::make_shared<prohorova::Rectangle>(3.5, 8.5, 1, 1);
  std::shared_ptr<prohorova::Rectangle> rectangle2 = std::make_shared<prohorova::Rectangle>(8.5, 8.5, 1, 1);
  std::shared_ptr<prohorova::Rectangle> rectangle3 = std::make_shared<prohorova::Rectangle>(8.5, 3.5, 1, 1);
  std::shared_ptr<prohorova::Rectangle> rectangle4 = std::make_shared<prohorova::Rectangle>(3.5, 3.5, 1, 1);

  const double angle = 45;

  compositeShape.add(rectangle1);
  compositeShape.add(rectangle2);
  compositeShape.add(rectangle3);
  compositeShape.add(rectangle4);

  const double area = compositeShape.getArea();

  prohorova::rectangle_t frameRect = compositeShape.getFrameRect();
  const double newWidth = frameRect.width * sqrt(2);
  const double newHeight = frameRect.width * sqrt(2);

  compositeShape.rotate(angle);

  BOOST_CHECK_CLOSE(compositeShape.getPos().x, frameRect.pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getPos().y, frameRect.pos.y, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, newWidth, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, newHeight, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area, ACCURACY);

  compositeShape.rotate(-angle);

  BOOST_CHECK_CLOSE(compositeShape.getPos().x, frameRect.pos.x, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getPos().y, frameRect.pos.y, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameRect.width, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameRect.height, ACCURACY);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area, ACCURACY);
  
}
BOOST_AUTO_TEST_CASE(CompositeShapeCopyAndMove)
{
  prohorova::CompositeShape compositeShape1;
  std::shared_ptr<prohorova::Rectangle> rectangle1 = std::make_shared<prohorova::Rectangle>(3, 2, 1, 4);
  std::shared_ptr<prohorova::Rectangle> rectangle2 = std::make_shared<prohorova::Rectangle>(1, 120, 11.5, 10.4);
  std::shared_ptr<prohorova::Circle> circle1 = std::make_shared<prohorova::Circle>(9.3, 1.4, 1.1);
  std::shared_ptr<prohorova::Circle> circle2 = std::make_shared<prohorova::Circle>(1.2, 1.3, 1.4);


  compositeShape1.add(rectangle1);
  compositeShape1.add(rectangle2);
  compositeShape1.add(circle1);
  compositeShape1.add(circle2);

  prohorova::CompositeShape compositeShape2;

  BOOST_CHECK_NO_THROW(prohorova::CompositeShape copiedCompositeShape(compositeShape1));
  BOOST_CHECK_NO_THROW(compositeShape2 = compositeShape1);
  BOOST_CHECK_NO_THROW(prohorova::CompositeShape movedCompositeShape(std::move(compositeShape1)));
  BOOST_CHECK_NO_THROW(compositeShape1 = std::move(compositeShape2));

  prohorova::CompositeShape emptyCompositeShape;
  prohorova::CompositeShape notEmptyCompositeShape;

  BOOST_CHECK_NO_THROW(notEmptyCompositeShape = std::move(emptyCompositeShape));

}
BOOST_AUTO_TEST_CASE(CompositeShapeIncorrectParameters)
{
  prohorova::CompositeShape compositeShape;
  std::shared_ptr<prohorova::Rectangle> rectangle1 = std::make_shared<prohorova::Rectangle>(1, 2, 3, 4);
  std::shared_ptr<prohorova::Rectangle> rectangle2 = std::make_shared<prohorova::Rectangle>(5, 6, 7, 8);
  std::shared_ptr<prohorova::Circle> circle1 = std::make_shared<prohorova::Circle>(9, 10, 11);
  std::shared_ptr<prohorova::Circle> circle2 = std::make_shared<prohorova::Circle>(12, 13, 14);

  compositeShape.add(rectangle1);
  compositeShape.add(rectangle2);
  compositeShape.add(circle1);
  compositeShape.add(circle2);

  BOOST_CHECK_THROW(compositeShape[compositeShape.getSize()], std::out_of_range);
  BOOST_CHECK_THROW(compositeShape[10], std::out_of_range);
  BOOST_CHECK_THROW(compositeShape.erase(compositeShape.getSize()), std::out_of_range);
  BOOST_CHECK_THROW(compositeShape.erase(compositeShape.getSize() - 1, compositeShape.getSize() + 1),
      std::out_of_range);
  BOOST_CHECK_THROW(compositeShape.insert(rectangle2, compositeShape.getSize() + 1), std::out_of_range);
  BOOST_CHECK_THROW(compositeShape.insert(nullptr, 1), std::invalid_argument);
  BOOST_CHECK_THROW(compositeShape.scale(-5), std::invalid_argument);
  BOOST_CHECK_THROW(compositeShape.add(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(compositeShape.replace(rectangle1,compositeShape.getSize() + 1), std::out_of_range);
  BOOST_CHECK_THROW(compositeShape.replace(nullptr, 1), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()
