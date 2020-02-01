#include <iostream>
#include <list>

void sequences2()
{
  std::list<int> list;
  int size = 0;
  const int maxSize = 21;
  int tmp = 0;
  while (std::cin >> tmp, !std::cin.eof())
  {
    if (!std::cin.eof() && std::cin.fail())
    {
      throw std::runtime_error("Input failed.\n");
    }
    ++size;
    if (size == maxSize)
    {
      throw std::invalid_argument("No more than 20 numbers can be processed.\n");
    }
    if ((tmp < 1) || (tmp > 20))
    {
      throw std::invalid_argument("Number is not in range from 1 to 20.\n");
    }
    list.push_back(tmp);
  }
  if (list.empty())
  {
    return;
  }
  auto front = list.begin();
  auto back = std::prev(list.end());

  for (int i = 0; i < size / 2; ++i)
  {
    std::cout << *front++ << " " << *back-- << " ";
  }
  if (front == back)
  {
    std::cout << *front;
  }
  std::cout << "\n";
}
