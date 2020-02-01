#include "shape.hpp"

Shape::Shape(const point_t& center):
  center_(center)
{
}

bool Shape::isMoreLeft(const Shape& other) const
{
  return (center_.x < other.center_.x);
}
bool Shape::isUpper(const Shape& other) const
{
  return (center_.y > other.center_.y);
}

std::ostream& operator<<(std::ostream& out, const Shape::pointer& shape)
{
  if (shape)
  {
    shape->draw(out);
  }
  return out;
}
