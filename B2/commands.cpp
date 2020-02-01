#include <iostream>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <sstream>

#include "queue-with-priority.hpp"

void executeCommandAdd(QueueWithPriority<std::string>& queue,
    const QueueWithPriority<std::string>::ElementPriority& priority, const std::string& value)
{
  queue.putElementToQueue(value, priority);
}

void executeCommandGet(QueueWithPriority<std::string>&queue, std::ostream& out)
{
  if (queue.empty())
  {
    out << "<EMPTY>\n";
    return;
  }
  queue.handleElement([&](std::string element) { out << element << "\n"; });
}
void executeCommandAccelerate(QueueWithPriority<std::string>& queue)
{
  queue.accelerate();
}

void executeCommandInvalid(
      std::ostream& out)
{
  out << "<INVALID COMMAND>" << "\n";
}
