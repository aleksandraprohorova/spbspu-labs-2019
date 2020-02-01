#include <algorithm>
#include <list>
#include <iostream>
#include <iterator>
#include <cmath>

void functors1()
{
  std::list<double> numbers(std::istream_iterator<double>(std::cin), std::istream_iterator<double>());

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Input failed.\n");
  }
  std::transform(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "), [](double& number) { return number * M_PI; });
  std::cout << "\n";
}
