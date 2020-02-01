#include "shape.hpp"

bool prohorova::Shape::intersects(const prohorova::Shape::pointer& anotherShape) const
{
  if (this == anotherShape.get())
  {
    return false;
  }

  rectangle_t frameRect1 = getFrameRect();
  rectangle_t frameRect2 = anotherShape->getFrameRect();

  double rightEdgeX1 = frameRect1.getRightEdge();
  double leftEdgeX1 = frameRect1.getLeftEdge();

  double rightEdgeX2 = frameRect2.getRightEdge(); 
  double leftEdgeX2 = frameRect2.getLeftEdge();

  double downEdgeY1 = frameRect1.getDownEdge();
  double topEdgeY1 = frameRect1.getTopEdge();

  double downEdgeY2 = frameRect2.getDownEdge(); 
  double topEdgeY2 = frameRect2.getTopEdge();

  return ((rightEdgeX1 > leftEdgeX2) && (leftEdgeX1 < rightEdgeX2) &&
      (downEdgeY1 > topEdgeY2) && (topEdgeY1 < downEdgeY2));
}

std::ostream& prohorova::operator<<(std::ostream& out, const Shape& shape)
{
  shape.show(out);
  return out;
}
std::ostream& prohorova::operator<<(std::ostream& out, const Shape* shape)
{
  return (out << (*shape));
}
std::ostream& prohorova::operator<<(std::ostream& out, const Shape::pointer shape)
{
  return (out <<  (*shape));
}
