#ifndef AP_SORTING

#define AP_SORTING

#include <functional>

#include "strategy.hpp"

template <typename Element>
std::function<bool (Element, Element)> orderToComparator(const std::string& order)
{
  if (order == "ascending")
  {
    return [](Element a, Element b) { return a < b; };
  }
  if (order == "descending")
  {
    return [](Element a, Element b) { return a > b; };
  }
  throw std::invalid_argument("\"ascending\" or \"descending\" must be provided.\n");
}

template <template <typename> typename Strategy = StrategyIterators, typename Container>
void sorting(Container& collection, std::function<bool (typename Container::value_type, typename Container::value_type)> compare)
{
  auto outer = Strategy<Container>::begin(collection);
  auto end = Strategy<Container>::end(collection);

  while (outer != end)
  {
    auto inner = outer;
    while (inner != end)
    {
      typename Strategy<Container>::valueType& previous = Strategy<Container>::get(collection, inner);
      typename Strategy<Container>::valueType& current = Strategy<Container>::get(collection, outer);

      if (compare(previous, current))
      {
        std::swap(previous, current);
      }
      inner++;
    }
    outer++;
  }
}
#endif // AP_SORTING
