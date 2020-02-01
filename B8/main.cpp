#include <iostream>
#include <list>
#include <algorithm>

#include "token-iterator.hpp"
#include "formatting-iterator.hpp"

#include "check-token.hpp"

int main(int argc, char* argv[])
{
  if ((argc != 1) && (argc != 3))
  {
    std::cerr << "Invalid number of arguments.\n";
    return 1;
  }
  char* end = nullptr;
  size_t lineWidth = 40;
  if (argc == 3)
  {
    std::string str = argv[1];
    if (str != "--line-width")
    {
      std::cerr << "Invalid argument.\n";
      return 1;
    }
    lineWidth = std::strtol(argv[2], &end, 10);
    if (*end || (lineWidth <= 24))
    {
      std::cerr << "Invalid value of --line-width.\n";
      return 1;
    }
  }
  std::cin >> std::noskipws;
  try
  {
    std::transform(TokenIterator(std::cin), {}, FormattingIterator(std::ref(std::cout), lineWidth), check_token());
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
