#ifndef AP_SHAPE
#define AP_SHAPE

#include <vector>
#include "point.hpp"

struct Shape
{
  std::vector<point_t> points;
};
std::ostream& operator<<(std::ostream& out, const Shape& shape);
std::istream& operator>>(std::istream& in, Shape& shape);

bool isRectangle(const Shape& shape);
bool isRhombus(const Shape& shape);
bool isSquare(const Shape& shape);

#endif // AP_SHAPE
