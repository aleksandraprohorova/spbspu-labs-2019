#ifndef AP_A1_SHAPE

#define AP_A1_SHAPE

#include <memory>
#include "base-types.hpp"

namespace prohorova
{
  class Shape
  {
  public:
    using pointer = std::shared_ptr<Shape>;
    // не просто птр, потому что вдруг понадобится std::unique_ptr на Shape

    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& /*newPos*/) = 0;
    virtual void move(double /*dx*/, double /*dy*/) = 0;
    virtual void scale(double /*factor*/) = 0;
    virtual point_t getPos() const = 0;
    virtual void rotate(double /*angle in degrees*/) = 0;
    virtual std::unique_ptr<Shape> clone() const = 0;
    
    virtual std::ostream& show(std::ostream& /*out*/) const = 0;

    bool intersects(const pointer& /*another figure*/) const;

  };


  /*  есть ощущение, что здесь что-то не так, но зато оно работает,
          не получилось перегрузить << без вспомогательного метода show()
  */
  std::ostream& operator<<(std::ostream& /*out*/, const Shape& /*reference to Shape*/);
  std::ostream& operator<<(std::ostream& /*out*/, const Shape* /*pointer to Shape*/);
  std::ostream& operator<<(std::ostream& /*out*/, const Shape::pointer /*smart pointer Shape*/);
}

#endif // AP_A1_SHAPE
