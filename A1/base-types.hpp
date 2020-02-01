#ifndef AP_BASE_TYPES

#define AP_BASE_TYPES

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
};
#endif // AP_BASE_TYPES
