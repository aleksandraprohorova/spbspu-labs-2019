#ifndef AP_A1_RECTANGLE

#define AP_A1_RECTANGLE

#include "shape.hpp"

class Rectangle:public Shape
{
public:
  Rectangle(const point_t& /*pos*/,double /*width*/,double /*height*/);
  Rectangle(double /*posX*/, double /*posY*/, double /*width*/,double /*height*/);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& /*newPos*/) override;
  void move(double /*dx*/,double /*dy*/) override;
  void show() const override;

  double getWidth() const;
  double getHeight() const;
  point_t getPos() const;

private:
  rectangle_t rect_;
};
#endif // AP_A1_RECTANGLE
