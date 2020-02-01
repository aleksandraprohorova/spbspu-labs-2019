#include "composite-shape.hpp"
#include <iostream>
#include <cmath>

prohorova::CompositeShape::CompositeShape():
  size_(0)
{
}
prohorova::CompositeShape::CompositeShape(const CompositeShape& rhs):
  figures_(std::make_unique<pointer[]>(rhs.size_)),
  size_(rhs.size_)
{ 
  for (size_t i = 0; i < size_; i++)
  {
    figures_[i] = rhs.figures_[i];
  }
}
prohorova::CompositeShape::CompositeShape(CompositeShape&& rhs) noexcept:
  figures_(std::move(rhs.figures_)),
  size_(rhs.size_)
{
  rhs.size_ = 0;
}
prohorova::CompositeShape& prohorova::CompositeShape::operator=(const CompositeShape& rhs)
{
  CompositeShape temp(rhs);
  swap(temp);
  
  return *this;
}
prohorova::CompositeShape& prohorova::CompositeShape::operator=(CompositeShape&& rhs) noexcept
{
 
  CompositeShape temp(std::move(rhs)); 
  /*  вот здесь вроде как должен(зачеркнуто) точно должен вызываться конструктор перемещения, в 
          котором есть обнуление rhs.size_ */
  swap(temp);

  return *this;
}
const prohorova::Shape::pointer& prohorova::CompositeShape::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Index of element must be greater than zero and not greater than the size.\n");
  }
  return figures_[index];
}
void prohorova::CompositeShape::add(const pointer& figure)
{
  if (!figure)
  {
    throw std::invalid_argument("Pointer to added figure is invalid.\n");
  }

  std::unique_ptr<pointer[]> newFigures = std::make_unique<pointer[]>(size_ + 1);

  for (size_t i = 0; i < size_; i++)
  {
    newFigures[i] = figures_[i];
  }
  newFigures[size_] = figure;

  figures_.swap(newFigures);
  size_++;
}
void prohorova::CompositeShape::clear()
{
  size_ = 0;
  figures_.reset();
}
std::unique_ptr<prohorova::Shape> prohorova::CompositeShape::clone() const
{
  return std::make_unique<CompositeShape>(CompositeShape(*this));
}
void prohorova::CompositeShape::erase(size_t index)
{
  erase(index, index + 1);
}
void prohorova::CompositeShape::erase(size_t first, size_t last)
{
  if (last <= first)
  {
    throw std::invalid_argument("Index of last element must be greater than index of first element.\n");
  }
  if (last > size_)
  {
    throw std::out_of_range("Index of element must be greater than zero and not greater than the size.\n");
  }
  std::unique_ptr<pointer[]> newFigures = std::make_unique<pointer[]>(size_ -  last + first);
  for (size_t i = 0; i < first; i++)
  {
    newFigures[i] = figures_[i];
  }
  for (size_t i = last; i < size_; i++)
  {
    newFigures[i - last + first] = figures_[i];
  }

  figures_.swap(newFigures);
  size_ += first - last;
}
double prohorova::CompositeShape::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < size_; i++)
  {
    area += figures_[i]->getArea();
  }
  return area;
}
prohorova::rectangle_t prohorova::CompositeShape::getFrameRect() const
{
  if (!figures_)
  {
    return {0, 0, 0, 0};
  }
  rectangle_t frameRect = figures_[0]->getFrameRect();

  double xMin = frameRect.getLeftEdge();
  double xMax = frameRect.getRightEdge();
  double yMin = frameRect.getTopEdge();
  double yMax = frameRect.getDownEdge();

  for (size_t i = 1; i < size_; i++)
  {
    rectangle_t frameRect = figures_[i]->getFrameRect();

    xMin = std::min(frameRect.getLeftEdge(), xMin);
    xMax = std::max(frameRect.getRightEdge(), xMax);
    yMin = std::min(frameRect.getTopEdge(), yMin);
    yMax = std::max(frameRect.getDownEdge(), yMax);
  }
  return rectangle_t{point_t{(xMin + xMax) / 2, (yMin + yMax) / 2}, xMax - xMin, yMax - yMin};
}
prohorova::point_t prohorova::CompositeShape::getPos() const
{
  return getFrameRect().pos;
}
size_t prohorova::CompositeShape::getSize() const
{
  return size_;
}
void prohorova::CompositeShape::insert(const pointer& figure, size_t index)
{
  if (index > size_)
  {
    throw std::out_of_range("Index of element must be greater than zero and not greater than the size.\n");
  }
  if (!figure)
  {
    throw std::invalid_argument("Inserted figure is invalid.\n");
  }

  std::unique_ptr<pointer[]> newFigures = std::make_unique<pointer[]>(size_ + 1);
  for (size_t i = 0; i < index; i++)
  {
    newFigures[i] = figures_[i];
  }
  newFigures[index] = figure;
  for (size_t i = index ; i < size_; i++)
  {
    newFigures[i + 1] = figures_[i];
  }

  figures_.swap(newFigures);
  size_++;
}

void prohorova::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; i++)
  {
    figures_[i]->move(dx,dy);
  }
}

void prohorova::CompositeShape::move(const point_t& newPos)
{
  point_t pos = getPos();
  move(newPos.x - pos.x, newPos.y - pos.y);
}
void prohorova::CompositeShape::replace(const pointer& figure, size_t index)
{
  if (index > size_)
  {
    throw std::out_of_range("Index of element must be greater than zero and not greater than the size.\n");
  }
  if (!figure)
  {
    throw std::invalid_argument("Figure in CompositeShape can't be nullptr.\n");
  }
  figures_[index] = figure;
}
void prohorova::CompositeShape::rotate(double angle)
{
  point_t pos = getFrameRect().pos;

  for (size_t i = 0; i < size_; i++)
  {
    point_t posFigure = figures_[i]->getPos();
    figures_[i]->rotate(angle);

    /*  расстояние от центра фигуры до центра составной фигуры =
            координаты фигуры в системе отсчета, связанной с центром составной фигуры.
              (функция getDistance() не подходит, так как не учитывает знаки)
     */
    double distanceX = posFigure.x - pos.x;
    double distanceY = posFigure.y - pos.y;

    double sinAngle = sin(toRadians(angle));
    double cosAngle = cos(toRadians(angle));

    /*  умножение на матрицу поворота, чтобы получить новые координаты
            в системе отсчета, связанной с центром составной фигуры*/

    double newX = distanceX * cosAngle + distanceY * sinAngle;
    double newY = - distanceX * sinAngle + distanceY * cosAngle;

    // возвращаемся в нормальную систему координат
    newX += pos.x;
    newY += pos.y;

    figures_[i]->move(point_t{newX, newY});
  }
}
void prohorova::CompositeShape::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Factor of scaling must be a positive number.\n");
  }
  point_t posCentre = getPos();
  for (size_t i = 0; i < size_; i++)
  {  
    point_t posFigure = figures_[i]->getPos();
    double dx = posCentre.x - posFigure.x;
    double dy = posCentre.y - posFigure.y;
    
    dx = dx * (1 - factor);
    dy = dy * (1 - factor);
    
    figures_[i]->move(dx, dy);
    figures_[i]->scale(factor);
  }
}
std::ostream& prohorova::CompositeShape::show(std::ostream& out) const
{
  double area = getArea();
  out << "Composite Shape. Size = " << getSize() << ". Area = " << area;
  rectangle_t frameRect = getFrameRect();
  out << "\n\tFrame rectangle: centre(" << frameRect.pos.x << ", " << frameRect.pos.y << ")";
  out << ", width = " << frameRect.width << ", height = " << frameRect.width << ".\n";
  out << "Figures: \n";
  for (size_t i = 0; i < size_; i++)
  {
    out << figures_[i].get();
  }
  return out;
}

void prohorova::CompositeShape::swap(CompositeShape& rhs) noexcept
{
  std::swap(figures_, rhs.figures_);
  std::swap(size_, rhs.size_);
}
