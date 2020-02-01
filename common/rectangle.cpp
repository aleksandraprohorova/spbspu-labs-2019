#include "rectangle.hpp"
#include <iostream>
#include <cmath>

#define TO_RADIANS  M_PI / 180

prohorova::Rectangle::Rectangle(const point_t& pos, double width, double height):
  rect_(rectangle_t{pos, width, height}),
  angle_(0)
{
  if ((rect_.width <= 0) || (rect_.height <= 0))
  {
    throw std::invalid_argument("Parameters must be positive numbers.\n");
  }
}
prohorova::Rectangle::Rectangle(double posX, double posY, double width, double height):
  Rectangle(point_t{posX, posY}, width, height)
{
}
double prohorova::Rectangle::getArea() const
{
  return getHeight() * getWidth();
}
prohorova::rectangle_t prohorova::Rectangle::getFrameRect() const
{
  double width = rect_.height * fabs(sin(angle_ * TO_RADIANS)) + rect_.width * fabs(cos(angle_ * TO_RADIANS));
  double height = rect_.width * fabs(sin(angle_ * TO_RADIANS)) + rect_.height * fabs(cos(angle_ * TO_RADIANS));
  return {rect_.pos, width, height};
}
void prohorova::Rectangle::move(const point_t& newPos)
{
  rect_.pos = newPos;
}
void prohorova::Rectangle::move(double dx, double dy)
{
  rect_.pos = point_t{getPos().x + dx, getPos().y + dy};
}
void prohorova::Rectangle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Factor of scaling must be a positive number.\n");
  }
  rect_.width *= factor;
  rect_.height *= factor;
}
std::unique_ptr<prohorova::Shape> prohorova::Rectangle::clone() const
{
  return std::make_unique<Rectangle>(Rectangle(*this));
}
double prohorova::Rectangle::getWidth() const
{
  return rect_.width;
}
double prohorova::Rectangle::getHeight() const
{
  return rect_.height;
}
double prohorova::Rectangle::getAngle() const
{
  return angle_;
}

prohorova::point_t prohorova::Rectangle::getPos() const
{
  return rect_.pos;
}
void prohorova::Rectangle::rotate(double angle)
{
  angle_ += angle;

  /*  здесь можно было бы брать остаток от деления на 360 или даже 180,
          но на вычисления это не повлияет, и ведь если я поворачиваю прямоугольник на 450 градусов,
            то наверное я знаю, что делаю и зачем-то мне это нужно
  */
}

std::ostream& prohorova::Rectangle::show(std::ostream& out) const
{
  out << "Rectangle. Width = " << rect_.width << ", height = " << rect_.height;
  out << ", position of centre = (" << rect_.pos.x << " , " << rect_.pos.y << "), ";
  out << "area = " << getArea();
  rectangle_t frame = getFrameRect();
  out << "\n\tFrame rectangle: centre(" << frame.pos.x << ", " << frame.pos.y << ")";
  out << ", width = " << frame.width << ", height = " << frame.height << ".\n";

  return out;
}
