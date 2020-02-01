#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>

#include "statistics.hpp"

int main()
{
  std::list<int> numbers(std::istream_iterator<int>(std::cin), std::istream_iterator<int>());
  if (!std::cin.eof() && std::cin.fail())
  {
    std::cerr << "Input failed.\n";
    return 1;
  }
  std::cout << std::for_each(numbers.begin(), numbers.end(), get_statistics());
  return 0;
}
