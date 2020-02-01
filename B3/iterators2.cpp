#include <iostream>
#include <iterator>
#include "container-factorial.hpp"

void iterators2()
{
  ContainerFactorial container;

  std::copy(container.begin(), container.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  std::copy(std::make_reverse_iterator(container.end()),
      std::make_reverse_iterator(container.begin()),
        std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
}
