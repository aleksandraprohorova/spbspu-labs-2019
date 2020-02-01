#include <vector>
#include <forward_list>

#include "sorting.hpp"
#include "output.hpp"

void vectors1(const char* order)
{
  auto comparator = orderToComparator<int>(order);

  std::vector<int> vectorBrackets;

  int current = 0;
  while (std::cin >> current, !std::cin.eof())
  {
    if (!std::cin.eof() && std::cin.fail())
    {
      throw std::runtime_error("Input failed.\n");
    }
    vectorBrackets.push_back(current);
  }
  if (vectorBrackets.empty())
  {
    return;
  }

  std::vector<int> vectorAt(vectorBrackets);
  std::forward_list<int> list(vectorBrackets.begin(), vectorBrackets.end());

  sorting<StrategyBrackets>(vectorBrackets, comparator);
  sorting<StrategyAt>(vectorAt, comparator);
  sorting<StrategyIterators>(list, comparator);

  std::cout << vectorBrackets << vectorAt << list;
}
