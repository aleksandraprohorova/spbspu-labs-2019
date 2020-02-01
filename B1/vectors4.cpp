#include <vector>
#include <cstdlib>
#include <ctime>

#include "sorting.hpp"
#include "output.hpp"

void fillRandom(double* array, int size)
{
  for (int i = 0; i < size; ++i)
  {
    array[i] = (-10 + rand() % 21) / 10.0;
  }
}

void vectors4(const char* order, int size)
{
  if (size < 0)
  {
    throw std::invalid_argument("Size of array must be a positive number.\n");
  }
  if (!size)
  {
    return;
  }
  auto compare = orderToComparator<double>(order);

  std::vector<double> vector(size, 0);
  fillRandom(&vector[0], size);

  std::cout << vector;

  sorting(vector, compare);

  std::cout << vector;
}
