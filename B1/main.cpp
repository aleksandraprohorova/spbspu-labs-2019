#include <exception>
#include <iostream>
#include <cstdlib>

void vectors1(const char* order);
void vectors2(const char* file);
void vectors3();
void vectors4(const char* order, int size);

int main(int argc, char* argv[])
{
  srand(time(0));
  try
  {
    if (argc <= 1)
    {
      std::cerr << "Invalid number of arguments.\n";
      return 1;
    }
    char* end = nullptr;
    int task = std::strtol(argv[1], &end, 10);

    if (*end)
    {
      std::cerr << "Invalid number of task.\n";
      return 1;
    }
    switch (task)
    {
      case 1:
      {
        if (argc != 3)
        {
          std::cerr << "Invalid number of arguments.\n";
          return 1;
        }
        vectors1(argv[2]);
        break;
      }
      case 2:
      {
        if (argc != 3)
        {
          std::cerr << "Invalid number of arguments.\n";
          return 1;
        }
        vectors2(argv[2]);
        break;
      }
      case 3:
      {
        if (argc != 2)
        {
          std::cerr << "Invalid number of arguments.\n";
          return 1;
        }
        vectors3();
        break;
      }
      case 4:
      {
        if (argc != 4)
        {
          std::cerr << "Invalid number of arguments.\n";
          return 1;
        }
        char* end2 = nullptr;
        int number = std::strtol(argv[3], &end2, 10);
        if (*end2)
        {
          std::cerr << "Invalid number of elements.\n";
          return 1;
        }
        vectors4(argv[2], number);
        break;
      }
      default:
      {
        std::cerr << "Invalid number of task.\n";
        return 1;
      }
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
