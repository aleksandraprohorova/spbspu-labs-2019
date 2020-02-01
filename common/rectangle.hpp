#ifndef AP_A1_RECTANGLE

#define AP_A1_RECTANGLE

#include "shape.hpp"

namespace prohorova
{
  class Rectangle:public Shape
  {
  public:
    Rectangle(const point_t& /*pos*/, double /*width*/, double /*height*/);
    Rectangle(double /*posX*/, double /*posY*/, double /*width*/, double /*height*/);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& /*newPos*/) override;
    void move(double /*dx*/, double /*dy*/) override;
    void scale(double /*factor*/) override;
    point_t getPos() const override;
    void rotate(double /*angle in degrees*/) override;

    std::unique_ptr<Shape> clone() const override;

    double getWidth() const;
    double getHeight() const;
    double getAngle() const;

    std::ostream& show(std::ostream& /*out*/) const;

  private:
    rectangle_t rect_;
    double angle_;
  };
}

#endif // AP_A1_RECTANGLE
