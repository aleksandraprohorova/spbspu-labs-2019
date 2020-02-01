#include "matrix.hpp"
#include <iostream>

#include "rectangle.hpp"

prohorova::Matrix::Matrix():
  rows_(0),
  numberOfElements(0)
{
}
prohorova::Matrix::Matrix(const prohorova::Matrix& rhs):
  figures_(std::make_unique<Shape::pointer[]>(rhs.numberOfElements)),
  rows_(rhs.rows_),
  columns_(new size_t[rhs.rows_]),
  numberOfElements(rhs.numberOfElements)
{
  for (size_t index = 0; index < numberOfElements; index++)
  {
    figures_[index] = rhs.figures_[index];
  }
  for (size_t row =  0; row < rows_; row++)
  {
    columns_[row] = rhs.columns_[row];
  }
}
prohorova::Matrix::Matrix(prohorova::Matrix&& rhs) noexcept:
  figures_(std::move(rhs.figures_)),
  rows_(rhs.rows_),
  columns_(std::move(rhs.columns_)),
  numberOfElements(rhs.numberOfElements)
{
  rhs.rows_ = 0;
  rhs.numberOfElements = 0;
}
prohorova::Matrix& prohorova::Matrix::operator=(const prohorova::Matrix& rhs)
{
  Matrix temp(rhs);
  swap(temp);

  return *this;
}
prohorova::Matrix& prohorova::Matrix::operator=(prohorova::Matrix&& rhs) noexcept
{
  Matrix temp(std::move(rhs));
  swap(temp);
  
  return *this;
}
prohorova::Matrix::ArrayOfPointerToShape prohorova::Matrix::operator[](size_t row) const
{
  if (row >= rows_)
  {
    throw std::out_of_range("Index of element must be greater than zero and not greater than the size.\n");
  }
  size_t currentIndex = 0;
  for (size_t i = 0; i < row; i++)
  {
    currentIndex += columns_[i];
  }
  ArrayOfPointerToShape array(&figures_[currentIndex], columns_[row]);
  return array;
}

void prohorova::Matrix::add(const prohorova::Shape::pointer& figure, size_t layer)
{
  if (layer > rows_)
  {
    throw std::out_of_range("Index of row must be greater than zero and not greater than the size.\n");
  }
  if (!figure)
  {
    throw std::invalid_argument("Invalid pointer to figure can't be added to matrix.\n");
  }
  std::unique_ptr<Shape::pointer[]> tempFigures = std::make_unique<Shape::pointer[]>(numberOfElements + 1);
  /*  по идее исключение может выброситься только при выделении памяти,
          копирование умных указателей без исключений,
            поля объекта меняются только после копирования,
              то есть строгая гарантия соблюдена*/
  size_t currentFigures = 0;
  size_t currentTemp = 0;
  // перемещаем все предыдущие слои
  for (size_t row = 0; row < rows_; row++)
  {
    for (size_t column = 0; column < columns_[row]; column++)
    {
      tempFigures[currentTemp++] = figures_[currentFigures++];
    }
    if (layer == row)
    {
      tempFigures[currentTemp++] = figure;
      ++columns_[row];
    }
  }
  // случай, когда надо создавать новый слой
  if (layer == rows_)
  {
    // если  зашли в эту ветку, значит columns_ еще не менялось
    std::unique_ptr<size_t[]> tempColumns = std::make_unique<size_t[]>(rows_ + 1);
    for (size_t row = 0; row < rows_; row++)
    {
      tempColumns[row] = columns_[row];
    }
    tempFigures[currentTemp] = figure;
    tempColumns[rows_] = 1;
    ++rows_;
    columns_.swap(tempColumns);
  }
  ++numberOfElements;
  figures_.swap(tempFigures);
}

size_t prohorova::Matrix::getRows() const
{
  return rows_;
}

std::ostream& prohorova::operator<<(std::ostream& out, const Matrix& matrix)
{
  for (size_t row = 0; row < matrix.getRows(); row++)
  {
    out << "Layer " << row + 1 << "\n";
    for (size_t column = 0; column < matrix[row].getSize(); column++)
    {
      out << matrix[row][column];
    }
  }
  return out;
}
void prohorova::Matrix::swap(prohorova::Matrix& rhs) noexcept
{
  std::swap(figures_, rhs.figures_);
  std::swap(rows_, rhs.rows_);
  std::swap(columns_, rhs.columns_);
  std::swap(numberOfElements, rhs.numberOfElements);
}

prohorova::Matrix::ArrayOfPointerToShape::ArrayOfPointerToShape(prohorova::Shape::pointer* array, size_t size):
  array_(array),
  size_(size)
{
}
size_t prohorova::Matrix::ArrayOfPointerToShape::getSize() const
{
  return size_;
}
const prohorova::Shape::pointer& prohorova::Matrix::ArrayOfPointerToShape::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Index must not be more than size of array. ");
  }
  return array_[index];
}
