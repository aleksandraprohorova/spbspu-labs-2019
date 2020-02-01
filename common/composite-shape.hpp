#ifndef AP_COMPOSITE_SHAPE
#define AP_COMPOSITE_SHAPE

#include <memory>
#include "shape.hpp"

namespace prohorova
{
  class CompositeShape:public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape& /*composite shape*/);
    CompositeShape(CompositeShape&& /*rvalue*/) noexcept;

    ~CompositeShape() = default;

    CompositeShape& operator=(const CompositeShape& /*rhs*/) ;
    CompositeShape& operator=(CompositeShape&& /*rvalue*/) noexcept;

    const pointer& operator[](size_t /*index of figure*/) const;

    void add(const pointer& /*shared ptr to figure*/);
    void clear();
    std::unique_ptr<Shape> clone() const override;
    void erase(size_t /*index of figure to delete*/);
    void erase(size_t /*[first figure to delete*/, size_t /*last figure not to delete)*/);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    size_t getSize() const;
    point_t getPos() const override;
    void insert(const pointer& /*figure to insert*/, size_t /*index of element*/);
    void move(const point_t& /*newPos*/) override;
    void move(double /*dx*/, double /*dy*/) override;
    void replace(const pointer& /*pointer to newFigure*/, size_t /*index of figure to replace*/);
    void rotate(double /*angle in degrees*/) override;
    void scale(double /*factor*/) override;
    std::ostream& show(std::ostream& /*out*/) const override;

    void swap(CompositeShape& /*rhs*/) noexcept;

  private:
    std::unique_ptr<pointer[]> figures_;

    size_t size_;
  };
}
#endif
