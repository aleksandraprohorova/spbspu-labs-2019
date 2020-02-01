#include <iostream>

void functors1();
void functors2();
int main(int argc, char* argv[])
{
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
        if (argc != 2)
        {
          std::cerr << "Invalid number of arguments.\n";
          return 1;
        }
        functors1();
        break;
      }
      case 2:
      {
        if (argc != 2)
        {
          std::cerr << "Invalid number of arguments.\n";
          return 1;
        }
        functors2();
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
