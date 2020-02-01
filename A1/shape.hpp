#ifndef AP_A1_SHAPE

#define AP_A1_SHAPE

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t  getFrameRect() const = 0;
  virtual void move(const point_t& /*newPos*/) = 0;
  virtual void move(double /*dx*/,double /*dy*/) = 0;
  virtual void show() const = 0;
};
#endif // AP_A1_SHAPE
