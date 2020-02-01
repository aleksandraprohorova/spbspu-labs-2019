#include "figures.hpp"

#include <algorithm>
#include <functional>

#include "manipulator.hpp"

Circle::Circle(const point_t& center):
  Shape(center)
{
}
void Circle::draw(std::ostream& out) const
{
  out << "CIRCLE " << center_ << "\n";
}
Triangle::Triangle(const point_t& center):
  Shape(center)
{
}
void Triangle::draw(std::ostream& out) const
{
  out << "TRIANGLE " << center_ << "\n";
}
Square::Square(const point_t& center):
  Shape(center)
{
}
void Square::draw(std::ostream& out) const
{
  out << "SQUARE " << center_ << "\n";
}
static Shape::pointer createCircle(const point_t& center)
{
  return std::make_shared<Circle>(center);
}
static Shape::pointer createTriangle(const point_t& center)
{
  return std::make_shared<Triangle>(center);
}
static Shape::pointer createSquare(const point_t& center)
{
  return std::make_shared<Square>(center);
}
std::istream& operator>>(std::istream& in, Shape::pointer& shape)
{
  point_t center;

  constexpr static struct
  {
    const char* name;
    Shape::pointer (*createFigure)(const point_t& center);
  }
  accordance[] = { {"CIRCLE", &createCircle},
                   {"TRIANGLE", &createTriangle},
                   {"SQUARE", &createSquare} };

  in >> std::ws;
  std::string typeOfFigure;
  char tmp;
  while(std::isalpha(in.peek()))
  {
    in.get(tmp);
    typeOfFigure += tmp;
  }
  auto accordanceElement = std::find_if(accordance, std::end(accordance),
      [&](const auto& accordanceElement){return accordanceElement.name == typeOfFigure;});
  if (accordanceElement == std::end(accordance))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in >> blank >> center;
  if (!in.eof() && in.fail())
  {
    return in;
  }
  shape = accordanceElement->createFigure(center);
  return in;
}
