#include <algorithm>
#include <list>
#include <iostream>
#include <iterator>

#include "figures.hpp"

void functors2()
{
  std::list<Shape::pointer> figures;
  Shape::pointer tmp;
  std::cin >> std::noskipws;

  while (std::cin >> tmp)
  {
    figures.push_back(tmp);
  }
  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Input failed.\n");
  }
  std::cout << "Original:\n";
  std::copy(figures.begin(), figures.end(), std::ostream_iterator<Shape::pointer>(std::cout));

  auto compareFromLeftToRight = [](const Shape::pointer& lhs, const Shape::pointer& rhs) { return lhs->isMoreLeft(*rhs);};
  figures.sort(compareFromLeftToRight);
  std::cout << "Left-Right:\n";
  std::copy(figures.begin(), figures.end(), std::ostream_iterator<Shape::pointer>(std::cout));

  auto compareFromRightToLeft = [&](const Shape::pointer& lhs, const Shape::pointer& rhs) {return compareFromLeftToRight(rhs, lhs);};
  figures.sort(compareFromRightToLeft);
  std::cout << "Right-Left:\n";
  std::copy(figures.begin(), figures.end(), std::ostream_iterator<Shape::pointer>(std::cout));

  auto compareFromTopToBottom = [](const Shape::pointer& lhs, const Shape::pointer& rhs) { return lhs->isUpper(*rhs);};
  figures.sort(compareFromTopToBottom);
  std::cout << "Top-Bottom:\n";
  std::copy(figures.begin(), figures.end(), std::ostream_iterator<Shape::pointer>(std::cout));

  auto compareFromBottomToTop = [&](const Shape::pointer& lhs, const Shape::pointer& rhs) {return compareFromTopToBottom(rhs, lhs);};
  figures.sort(compareFromBottomToTop);
  std::cout << "Bottom-Top:\n";
  std::copy(figures.begin(), figures.end(), std::ostream_iterator<Shape::pointer>(std::cout));
}
