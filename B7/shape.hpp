#ifndef AP_SHAPE
#define AP_SHAPE

#include <iostream>
#include <memory>

#include "point.hpp"

class Shape
{
public:
  using pointer = std::shared_ptr<Shape>;
  Shape(const point_t& center);
  ~Shape() = default;

  bool isMoreLeft(const Shape& other) const;
  bool isUpper(const Shape& other) const;

  virtual void draw(std::ostream& out) const = 0;

protected:
  point_t center_;
};

std::ostream& operator<<(std::ostream& out, const Shape::pointer& shape);
#endif // AP_SHAPE
