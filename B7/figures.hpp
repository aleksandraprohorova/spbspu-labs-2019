#ifndef AP_FIGURES
#define AP_FIGURES

#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(const point_t& center);
  void draw(std::ostream& out) const override;
};

class Triangle: public Shape
{
public:
  Triangle(const point_t& center);
  void draw(std::ostream& out) const override;
};

class Square: public Shape
{
public:
  Square(const point_t& center);
  void draw(std::ostream& out) const override;
};

std::istream& operator>>(std::istream& in, Shape::pointer& shape);

#endif // AP_FIGURES
