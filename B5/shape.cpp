#include "shape.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <boost/io/ios_state.hpp>
#include "manipulator.hpp"

std::ostream& operator<<(std::ostream& out, const Shape& shape)
{
  out << shape.points.size() << " ";
  std::copy(shape.points.begin(), shape.points.end(), std::ostream_iterator<point_t>(out, " "));
  out << "\n";
  return out;
}
std::istream& operator>>(std::istream& in, Shape& shape)
{
  boost::io::ios_flags_saver state(in);
  in >> skipBlank;

  size_t size = 0;
  in >> size;
  if (in.fail())
  {
    return in;
  }
  std::vector<point_t> tmp;
  std::copy_n(std::istream_iterator<point_t>(in), size, std::back_inserter(tmp));
  if (in.fail())
  {
    return in;
  }
  shape.points = tmp;
  return in;
}

bool isRectangle(const Shape& shape)
{
  if (shape.points.size() != 4)
  {
    return false;
  }
  std::vector<int> v1 = {shape.points[0].x - shape.points[1].x, shape.points[0].y - shape.points[1].y};
  std::vector<int> v2 = {shape.points[1].x - shape.points[2].x, shape.points[1].y - shape.points[2].y};
  std::vector<int> v3 = {shape.points[2].x - shape.points[3].x, shape.points[2].y - shape.points[3].y};
  std::vector<int> v4 = {shape.points[3].x - shape.points[0].x, shape.points[3].y - shape.points[0].y};

  return !(std::inner_product(v1.begin(), v1.end(), v2.begin(), 0) == 0 &&
      std::inner_product(v2.begin(), v2.end(), v3.begin(), 0) == 0 &&
        std::inner_product(v3.begin(), v3.end(), v4.begin(), 0));
};
bool isRhombus(const Shape& shape)
{
  std::vector<int> v1 = {shape.points[0].x - shape.points[2].x, shape.points[0].y - shape.points[2].y};
  std::vector<int> v2 = {shape.points[1].x - shape.points[3].x, shape.points[1].y - shape.points[3].y};
  return !(std::inner_product(v1.begin(), v1.end(), v2.begin(), 0));
};
bool isSquare(const Shape& shape)
{
  return (isRectangle(shape) && isRhombus(shape));
};
