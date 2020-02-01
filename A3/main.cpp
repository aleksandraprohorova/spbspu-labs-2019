#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
int main()
{
  prohorova::Circle circle1{prohorova::point_t{1, 2}, 4};
  prohorova::Circle circle2{-2.1234, 3.4567, 1};
  prohorova::Rectangle rectangle1{prohorova::point_t{3, 4}, 2, 3};
  prohorova::Rectangle rectangle2{1.2, -2.3, 1, 1};
  prohorova::Shape* correctFigures[] = {&circle1, &circle2, &rectangle1, &rectangle2};

  std::cout << "Starting values: \n";
  for (prohorova::Shape* figure: correctFigures)
  {
    std::cout << figure;
  }

  const double dx = 10;
  const double dy = 20;
  std::cout << "\nMoving all figures for dx = " << dx << ", dy = " << dy << ":\n";
  for (prohorova::Shape* figure: correctFigures)
  {
    figure->move(dx,dy);
    std::cout << figure;
  }

  const prohorova::point_t newPos{0, 0};
  std::cout << "\nMoving all figures to the point: (" << newPos.x << ", " <<  newPos.y << ")"  << "\n";
  for (prohorova::Shape* figure: correctFigures)
  {
    figure->move(newPos);
    std::cout << figure;
  }

  const double factor = 1.5;
  std::cout << "\n Scaling all figures by factor " << factor << ":\n";
  for (prohorova::Shape* figure: correctFigures)
  {
    figure->scale(factor);
    std::cout << figure;
  }

  prohorova::CompositeShape compositeShape;

  std::shared_ptr<prohorova::Rectangle> rectangle3(new prohorova::Rectangle{1, 2, 3, 4});
  std::shared_ptr<prohorova::Rectangle> rectangle4(new prohorova::Rectangle{1, 1, 1, 1});
  std::shared_ptr<prohorova::Rectangle> rectangle5(new prohorova::Rectangle{1.0 / 3, 1.0 / 4, 1.0 / 5, 1.0 / 6});
  std::shared_ptr<prohorova::Rectangle> rectangle6(new prohorova::Rectangle{-1, -1, 20, 20});
  std::shared_ptr<prohorova::Circle> circle3(new prohorova::Circle{1, 2, 3});
  std::shared_ptr<prohorova::Circle> circle4(new prohorova::Circle{1, 1, 1});
  std::shared_ptr<prohorova::Circle> circle5(new prohorova::Circle{1.0 / 9, 1.0 / 11, 1.0 / 12});
  std::shared_ptr<prohorova::Circle> circle6(new prohorova::Circle{-1, -1, 100});

  compositeShape.add(rectangle3);
  compositeShape.add(rectangle4);
  compositeShape.add(rectangle5);
  compositeShape.add(rectangle6);

  std::cout << compositeShape;

  std::cout << "\nAdd 4 rectangles:\n" << compositeShape;

  compositeShape.insert(circle3, 1);
  compositeShape.insert(circle4, 3);
  compositeShape.insert(circle5, 5);
  compositeShape.insert(circle6, 7);
  std::cout << "\nInsert 4 circles:\n" << compositeShape;

  compositeShape.move({100,1000});
  std::cout << "\n Move composite shape to the point{100, 1000}:\n" << compositeShape;

  compositeShape.erase(0);
  compositeShape.erase(1);
  compositeShape.erase(2);
  compositeShape.erase(3);
  std::cout << "\nErase 4 rectangles:\n" << compositeShape;

  compositeShape.scale(0.5);
  std::cout << "\nScale by 0.5:\n" << compositeShape;

  prohorova::CompositeShape anotherCompositeShape(compositeShape);
  anotherCompositeShape = compositeShape;
  anotherCompositeShape = std::move(compositeShape);
  
  return 0;
}
