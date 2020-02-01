#include <memory>
#include <sstream>
#include <algorithm>

#include "phone-book-handler.hpp"

std::istream& blank(std::istream& in);

struct quoted_string_t
{
  std::string& value;
};
std::istream& operator>>(std::istream& in, quoted_string_t quotedString)
{
  quotedString.value.clear();
  if (in.peek() != '"')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.get();
  char tmp;

  while (in.peek() != '"')
  {
    if ((in.peek() == '\n') || (in.peek() == in.eof()))
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    in.get(tmp);
    if (tmp == '\\')
    {
      in.get(tmp);
      quotedString.value.push_back(tmp);
    }
    else
    {
      quotedString.value.push_back(tmp);
    }
  }
  in.get();
  in >> blank;
  return in;
}

quoted_string_t quoted(std::string& str)
{
  return quoted_string_t{str};
}

std::istream& operator>>(std::istream& in, PhoneBook::value_type& record)
{
  std::string numberString;
  std::string name;
  in >> blank >> numberString >> blank;

  char* end = nullptr;
  std::strtol(numberString.c_str(), &end, 10);

  if (*end)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  std::string tmp;

  in >> quoted(name);

  if (in.fail())
  {
    return in;
  }

  if (in.good())
  {
    record = std::make_pair(numberString, name);
  }
  return in;
}


std::unique_ptr<PhoneBookCommand> createAddRecord(std::istream& args)
{
  PhoneBook::value_type newRecord;
  args >> newRecord >> blank;

  if (args.bad())
  {
    throw std::runtime_error("Input failed.\n");
  }
  if (args.fail())
  {
    args.clear();
    args.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::make_unique<CommandInvalid>();
  }
  return std::make_unique<CommandAddRecord>(newRecord);
}
std::unique_ptr<PhoneBookCommand> createStoreBookmark(std::istream& args)
{
  std::string markName;
  std::string newMarkName;
  args >> blank >> markName >> blank >> newMarkName >> blank;

  if (args.bad())
  {
    throw std::runtime_error("Input failed.\n");
  }
  if (args.fail())
  {
    args.clear();
    args.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::make_unique<CommandInvalid>();
  }
  return std::make_unique<CommandStoreBookmark>(markName, newMarkName);
}

std::unique_ptr<PhoneBookCommand> createInsert(std::istream& args)
{
  PhoneBook::value_type newRecord;
  std::string placeOfInsert;
  std::string markName;

  args >> blank >> placeOfInsert >> blank >> markName >> newRecord  >> blank;

  if (args.bad())
  {
    throw std::runtime_error("Input failed.\n");
  }
  if (args.fail())
  {
    args.clear();
    args.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::make_unique<CommandInvalid>();
  }
  if (placeOfInsert == "before")
  {
    return std::make_unique<CommandInsertBeforeBookmark>(markName, newRecord);
  }
  if (placeOfInsert == "after")
  {
    return std::make_unique<CommandInsertAfterBookmark>(markName, newRecord);
  }
  return std::make_unique<CommandInvalid>();
}

std::unique_ptr<PhoneBookCommand> createDeleteRecord(std::istream& args)
{
  std::string markName;
  args >> blank >> markName >> blank;
  if (args.bad())
  {
    throw std::runtime_error("Input failed.\n");
  }
  if (args.fail())
  {
    args.clear();
    args.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::make_unique<CommandInvalid>();
  }
  return std::make_unique<CommandDeleteRecord>(markName);
}
std::unique_ptr<PhoneBookCommand> createShowRecord(std::istream& args)
{
  std::string markName;
  args >> blank >> markName >> blank;
  if (args.bad())
  {
    throw std::runtime_error("Input failed.\n");
  }
  if (args.fail())
  {
    args.clear();
    args.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::make_unique<CommandInvalid>();
  }
  return std::make_unique<CommandShowRecord>(markName);
}
std::unique_ptr<PhoneBookCommand> createMoveBookmark(std::istream& args)
{
  std::string markName;
  std::string steps;

  args >> blank >> markName >> blank >> steps >> blank;

  if (args.bad())
  {
    throw std::runtime_error("Input failed.\n");
  }
  if (args.fail())
  {
    args.clear();
    args.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::make_unique<CommandInvalid>();
  }

  return std::make_unique<CommandMoveBookmark>(markName, steps);
}

std::istream& operator>>(std::istream& in, std::unique_ptr<PhoneBookCommand>& command)
{
  static const struct
  {
    using creatorType = std::unique_ptr<PhoneBookCommand> (*) (std::istream& args);
    const char* name;
    creatorType createCommand;
  } accordance[] = { {"add", &createAddRecord},
                     {"store", &createStoreBookmark},
                     {"insert", &createInsert},
                     {"delete", &createDeleteRecord},
                     {"show", &createShowRecord},
                     {"move", &createMoveBookmark}
                   };

  std::string commandName;
  in >> commandName;

  auto accordanceElement = std::find_if(accordance, std::end(accordance),
      [&](const auto& accordanceElement){ return (accordanceElement.name == commandName); });

  if (accordanceElement != std::end(accordance))
  {
    command = accordanceElement->createCommand(in);
    return in;
  }
  command = std::make_unique<CommandInvalid>();
  return in;
}
