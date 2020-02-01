#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "data-struct.hpp"
#include "manipulator.hpp"

int main()
{
  try
  {
    std::cin >> std::noskipws;
    std::vector<DataStruct> vector(std::istream_iterator<DataStruct>(std::cin), std::istream_iterator<DataStruct>());
    if (!std::cin.eof() && std::cin.fail())
    {
      std::cerr << "Input failed.\n";
      return 1;
    }
    auto comparator = [](const DataStruct& lhs, const DataStruct& rhs)
    {
      if (lhs.key1 != rhs.key1)
      {
        return (lhs.key1 < rhs.key1);
      }
      if (lhs.key2 != rhs.key2)
      {
        return (lhs.key2 < rhs.key2);
      }
      return (lhs.str.size() < rhs.str.size());
    };
    std::sort(vector.begin(), vector.end(), comparator);
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(std::cout));
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
