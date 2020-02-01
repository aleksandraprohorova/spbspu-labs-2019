#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <list>

#include "shape.hpp"
#include "manipulator.hpp"

void algorithms2()
{
  std::cin >> std::skipws;
  std::list<Shape> shapes(std::istream_iterator<Shape>(std::cin), std::istream_iterator<Shape>());

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Input failed.\n");
  }

  int numberOfVertices = std::accumulate(shapes.begin(), shapes.end(), 0,
      [](int sum, const Shape& shape) {return sum += shape.points.size();});

  int numberOfTriangles = std::count_if(shapes.begin(), shapes.end(),
      [](const Shape& shape) {return shape.points.size() == 3;});

  int numberOfSquares = std::count_if(shapes.begin(), shapes.end(), isSquare);
  int numberOfRectangles = std::count_if(shapes.begin(), shapes.end(), isRectangle);

  std::cout << "Vertices: " << numberOfVertices << "\n"
            << "Triangles: " << numberOfTriangles << "\n"
            << "Squares: " << numberOfSquares << "\n"
            << "Rectangles: " << numberOfRectangles << "\n";

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [](const Shape& shape) {return shape.points.size() == 5;}), shapes.end());

  std::vector<point_t> points;
  std::for_each(shapes.begin(), shapes.end(), [&points](const Shape& shape) {points.push_back(shape.points[0]);});
  std::cout << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<point_t>(std::cout, " "));
  std::cout << "\n";

  auto compare = [](const Shape& lhs, const Shape& rhs)
  {
    if (lhs.points.size() != rhs.points.size())
    {
      return (lhs.points.size() < rhs.points.size());
    }
    if (lhs.points.size() ==  4)
    {
      bool isRectangleLhs = isRectangle(lhs);
      return ((isRhombus(lhs) && isRectangleLhs) || ((isRectangleLhs && !(isSquare(rhs)))));
    }
    return false;
  };
  shapes.sort(compare);
  std::cout << "Shapes:" << "\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(std::cout));
}
