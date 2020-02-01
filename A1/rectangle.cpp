#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t &pos,double width,double height):
  rect_(rectangle_t{pos,width,height})
{
  if(rect_.width <= 0)
  {
    std::cerr << "Width of rectangle must be a positive number.\n";
  }
  if(rect_.height <= 0)
  {
    std::cerr << "Height of rectangle must be a positive number.\n";
  }
}
Rectangle::Rectangle(double posX,double posY,double width,double height):
  Rectangle(point_t{posX,posY}, width, height)
{ 
}
double Rectangle::getArea() const
{
  return getHeight() * getWidth();
}
rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}
void Rectangle::move(const point_t &newPos)
{
  rect_.pos = newPos;
}
void Rectangle::move(double dx,double dy)
{
  rect_.pos = point_t{getPos().x + dx,getPos().y + dy};
}
void Rectangle::show() const
{
  std::cout << "Rectangle. Width = " << getWidth() << ", height = " << getHeight();
  std::cout << ", position of centre = (" << getPos().x << " , " << getPos().y << "), ";
  std::cout << "area = " << getArea();
  rectangle_t frame = getFrameRect();
  std::cout << "\n\tFrame rectangle: centre(" << frame.pos.x << ", " << frame.pos.y << ")";
  std::cout << ", width = " << frame.width << ", height = " << frame.width << ".\n";
}
double Rectangle::getWidth() const
{
  return rect_.width;
}
double Rectangle::getHeight() const
{
  return rect_.height;
}
point_t Rectangle::getPos() const
{
  return rect_.pos;
}
