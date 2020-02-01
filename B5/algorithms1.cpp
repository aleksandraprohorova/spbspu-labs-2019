#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <iterator>

void algorithms1()
{
  std::unordered_set<std::string> words(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>());
  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Input failed.\n");
  }
  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
