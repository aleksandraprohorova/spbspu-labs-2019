#include <iostream>
#include <string>
#include <sstream>
#include <functional>

#include "queue-with-priority.hpp"

using handleQueueCommand = std::function<void (QueueWithPriority<std::string>&, std::ostream&)>;

handleQueueCommand parseArguments(std::istream& in);

void sequences1()
{
  QueueWithPriority<std::string> queue;

  std::string tmp;
  while (getline(std::cin, tmp))
  {
    if (!std::cin.eof() && std::cin.fail())
    {
      throw std::runtime_error("Input failed.\n");
    }
    std::stringstream in(tmp);
    parseArguments(in)(queue, std::ref(std::cout));
  }
}
