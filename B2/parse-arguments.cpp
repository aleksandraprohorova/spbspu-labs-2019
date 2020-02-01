#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <algorithm>

#include "queue-with-priority.hpp"

using namespace std::placeholders;

using handleQueueCommand = std::function<void (QueueWithPriority<std::string>&, std::ostream&)>;

void executeCommandAdd(QueueWithPriority<std::string>&,
    const QueueWithPriority<std::string>::ElementPriority&, const std::string&);
void executeCommandGet(QueueWithPriority<std::string>&, std::ostream&);
void executeCommandAccelerate(QueueWithPriority<std::string>&);
void executeCommandInvalid(std::ostream&);

handleQueueCommand parseArgumentsAdd(std::istream& in)
{
  std::string priority;
  std::string value;

  in >> priority >> std::ws;

  getline(in, value);

  if (value.empty())
  {
    return std::bind(executeCommandInvalid, _2);
  }

  static const struct
  {
    const char* name;
    QueueWithPriority<std::string>::ElementPriority priority;
  } priorities[] = { {"low", QueueWithPriority<std::string>::ElementPriority::LOW},
      {"normal", QueueWithPriority<std::string>::ElementPriority::NORMAL},
        {"high", QueueWithPriority<std::string>::ElementPriority::HIGH} };

  auto priorityElement = std::find_if(priorities, std::end(priorities),
      [&](const decltype(priorities[0])& element) { return (element.name == priority); });
  if (priorityElement == std::end(priorities))
  {
    return std::bind(executeCommandInvalid, _2);
  }

  return std::bind(executeCommandAdd, _1, priorityElement->priority, value);
}

handleQueueCommand parseArgumentsGet(std::istream& in)
{
  in >> std::ws;
  if (!in.eof())
  {
    return std::bind(executeCommandInvalid, std::ref(std::cout));
  }
  return std::bind(executeCommandGet, _1, _2);
}

handleQueueCommand parseArgumentsAccelerate(std::istream& in)
{
  using namespace std::placeholders;

  in >> std::ws;
  if (!in.eof())
  {
    return std::bind(executeCommandInvalid, _2);
  }
  return std::bind(executeCommandAccelerate, _1);
}

handleQueueCommand parseArguments(std::istream& in)
{
  static const struct
  {
    using parserType = handleQueueCommand (*)(std::istream& in);
    const char* name;
    parserType parse;
  } parsers[] = { {"add", &parseArgumentsAdd},
      {"get", &parseArgumentsGet}, {"accelerate", &parseArgumentsAccelerate} };

  std::string tmp;
  in >> tmp;

  auto parserElement = std::find_if(parsers, std::end(parsers),
      [&](const decltype(parsers[0])& element) { return (element.name == tmp); });

  if (parserElement == std::end(parsers))
  {
    return std::bind(executeCommandInvalid, _2);
  }
  else
  {
    return parserElement->parse(in);
  }
}
