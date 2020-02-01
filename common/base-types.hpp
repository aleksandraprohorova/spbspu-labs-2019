#ifndef AP_BASE_TYPES

#define AP_BASE_TYPES

#include <cmath>

namespace prohorova
{
  struct point_t
  {
    double x;
    double y;
  };
  struct rectangle_t
  {
    point_t pos;
    double width;
    double height;

    double getRightEdge() const
    {
      return pos.x + width / 2;
    }

    double getLeftEdge() const
    {
      return pos.x - width / 2;
    }

    double getTopEdge() const
    {
      return pos.y - height / 2;
    }

    double getDownEdge() const
    {
      return pos.y + height / 2;
    }
  };

  double toRadians(double /*angle*/);
}
#endif // AP_BASE_TYPES
