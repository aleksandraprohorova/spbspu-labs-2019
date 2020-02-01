#ifndef AP_POINT
#define AP_POINT

#include <iostream>

struct point_t
{
  int x;
  int y;
};
std::ostream& operator<<(std::ostream& out, const point_t& point);
std::istream& operator>>(std::istream& in, point_t& point);

#endif  // AP_POINT
