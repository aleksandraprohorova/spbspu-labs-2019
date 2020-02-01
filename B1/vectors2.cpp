#include <fstream>
#include <vector>
#include <stdlib.h>
#include <memory>
#include <boost/scope_exit.hpp>

#include "output.hpp"

void vectors2(const char* file)
{
  std::ifstream in(file);

  if (!in.is_open())
  {
    throw std::runtime_error("Couldn't open the file.\n");
  }

  int capacity = 10;

  std::unique_ptr<char[], decltype(&free)> array(static_cast<char*>(calloc(capacity, 1)), free);

  if (!array)
  {
    throw std::runtime_error("Couldn't allocate memory.\n");
  }

  int size = 0;

  while (in)
  {
    in.read(&array[size], capacity - size);
    size += in.gcount();
    if (size == capacity)
    {
      capacity *= 2;
      std::unique_ptr<char[], decltype(&free)> tmp(static_cast<char*>(realloc(array.get(),  capacity)), free);
      if (!tmp)
      {
        throw std::runtime_error("Couldn't allocate memory.\n");
      }
      array.release();
      std::swap(array, tmp);
    }
    if (!in.eof() && in.fail())
    {
      throw std::runtime_error("Input failed.\n");
    }
  }
  if (!size)
  {
    return;
  }
  std::vector<char> vector(&array[0], &array[size]);

  for (auto symbol: vector)
  {
    std::cout << symbol;
  }
}
