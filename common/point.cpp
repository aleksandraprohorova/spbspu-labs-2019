#include "point.hpp"
#include "manipulator.hpp"

#include <boost/io/ios_state.hpp>

std::ostream& operator<<(std::ostream& out, const point_t& point)
{
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}
static std::istream& operator>>(std::istream& in, char delimiter)
{
  if (in.peek() != delimiter)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.get();
  return in;
}
std::istream& operator>>(std::istream& in, point_t& point)
{
  boost::io::ios_flags_saver state(in, ~std::ios_base::skipws);
  if (in.iword(SKIP_BLANK_INDEX) == SKIP_BLANK)
  {
    in >> blank;
  }
  int x;
  int y;
  in >> '(' >> blank >> x >> blank >> ';' >> blank >> y >> blank >> ')';
  if (in.fail())
  {
    if (in.eof())
    {
      in.clear(in.rdstate() & ~std::ios_base::eofbit);
    }
    return in;
  }
  point = {x, y};
  return in;
}
