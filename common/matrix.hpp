#ifndef AP_A4_MATRIX

#define AP_A4_MATRIX

#include <memory>
#include "shape.hpp"

namespace prohorova
{
  class Matrix
  {
  public:
    class ArrayOfPointerToShape
    {
    public:
      ArrayOfPointerToShape(Shape::pointer* /*array*/,  size_t /*size*/);
      const Shape::pointer& operator[](size_t /*index*/) const;
      size_t getSize() const;

    private:
      Shape::pointer* array_;
      size_t size_;
    };

    Matrix();

    Matrix(const Matrix& /*rhs*/);
    Matrix(Matrix&& /*rhs*/) noexcept;

    ~Matrix() = default;

    Matrix& operator=(const Matrix& /*rhs*/);
    Matrix& operator=(Matrix&& /*rhs*/) noexcept;
    ArrayOfPointerToShape operator[](size_t /*index*/) const;

    void add(const Shape::pointer& /*figure to add*/, size_t /*layer*/);

    size_t getRows() const;

    void swap(Matrix& /*rhs*/) noexcept;

  private:
    std::unique_ptr<Shape::pointer[]> figures_;
    
    size_t rows_;
    std::unique_ptr<size_t[]> columns_;

    size_t numberOfElements;

  };

  std::ostream& operator<<(std::ostream& /*out*/, const Matrix& /*matrix*/);
}
#endif // AP_A4_MATRIX
