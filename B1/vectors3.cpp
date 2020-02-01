#include <vector>
#include "output.hpp"

void vectors3()
{
  int current = -1;
  std::vector<int> vector;

  while (std::cin >> current)
  {
    if (current == 0)
    {
      break;
    }
    vector.push_back(current);
  }
  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Input failed.\n");
  }
  if (vector.empty())
  {
    return;
  }
  if (current != 0)
  {
    throw std::runtime_error("Expected zero at the end.\n");
  }

  if (vector.back() == 1)
  {
    auto it = vector.begin();
    while (it != vector.end())
    {
      it = ((*it) % 2 == 0) ? vector.erase(it) : ++it;
    }
  }
  else if (vector.back() == 2)
  {
    auto it = vector.begin();
    while (it != vector.end())
    {
      it = ((*it) % 3 == 0) ? (vector.insert(++it, 3, 1) + 3) : ++it;
    }
  }

  std::cout << vector;
}
