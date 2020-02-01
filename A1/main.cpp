#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  Circle circle1{point_t{1,2},4};
  Circle circle2{-2.1234, 3.4567, 1};
  Rectangle rectangle1{point_t{3,4},2,3};
  Rectangle rectangle2{1.2,-2.3,1,1};
  Shape* correctFigures[] = {&circle1, &circle2, &rectangle1, &rectangle2};
  int size = sizeof(correctFigures)/sizeof(Shape);
  std::cout << "Starting values: \n";
  for(int i = 0;i < size;i++)
  {
    correctFigures[i]->show();
  }
  std::cout << "\nMoving all figures for dx = 10, dy = 20:\n";
  for(int i = 0;i<size;i++)
  {
    correctFigures[i]->move(10,20);
    correctFigures[i]->show();
  }
  std::cout << "\nMoving all figures to the point (0,0):\n";
  for(int i = 0;i<size;i++)
  {
    correctFigures[i]->move(point_t{0,0});
    correctFigures[i]->show();
  }
  return 0;
}
