#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

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
  
  return 0;
}
