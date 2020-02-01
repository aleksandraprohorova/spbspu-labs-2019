#include "phone-book-handler.hpp"

#include <sstream>
#include <algorithm>
#include <iostream>

namespace
{
  const char* invalidCommand = "<INVALID COMMAND>\n";
  const char* invalidBookmark = "<INVALID BOOKMARK>\n";
  const char* invalidStep = "<INVALID STEP>\n";
  const char* empty = "<EMPTY>\n";
}

CommandAddRecord::CommandAddRecord(const PhoneBook::value_type& record):
  record_(record)
{
}
void CommandAddRecord::execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream&)
{
  phoneBook.pushBack(record_);
  if ((phoneBook.size() == 1) && (bookmarks["current"] == phoneBook.end()))
  {
    ++bookmarks["current"];
  }
}

CommandStoreBookmark::CommandStoreBookmark(const std::string& markName, const std::string& newMarkName):
  markName_(markName),
  newMarkName_(newMarkName)
{
}
void CommandStoreBookmark::execute(PhoneBook&, bookmarksType& bookmarks, std::ostream& out)
{
  auto bookmark = bookmarks.find(markName_);
  if (bookmark != bookmarks.end())
  {
    bookmarks.insert(std::make_pair(newMarkName_, bookmark->second));
  }
  else
  {
    out << invalidBookmark;
  }
}

CommandInsertBeforeBookmark::CommandInsertBeforeBookmark(const std::string& markName, const PhoneBook::value_type& record):
  markName_(markName),
  record_(record)
{
}
void CommandInsertBeforeBookmark::execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out)
{
  auto bookmark = bookmarks.find(markName_);
  if (bookmark != bookmarks.end())
  {
    phoneBook.insert(bookmark->second, record_);
    if (bookmark->second == phoneBook.end())
    {
      --bookmark->second;
    }
  }
  else
  {
    out << invalidBookmark;
  }
}

CommandInsertAfterBookmark::CommandInsertAfterBookmark(const std::string& markName, const PhoneBook::value_type& record):
  markName_(markName),
  record_(record)
{
}
void CommandInsertAfterBookmark::execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out)
{
  auto bookmark = bookmarks.find(markName_);
  if (bookmark != bookmarks.end())
  {
    auto pos = (bookmark->second == phoneBook.end()) ? bookmark->second : std::next(bookmark->second);
    phoneBook.insert(pos, record_);
    if (bookmark->second == phoneBook.end())
    {
      --bookmark->second;
    }
  }
  else
  {
    out << invalidBookmark;
  }
}

CommandDeleteRecord::CommandDeleteRecord(const std::string& markName):
  markName_(markName)
{
}
void CommandDeleteRecord::execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out)
{
  auto bookmark = bookmarks.find(markName_);
  if (bookmark != bookmarks.end())
  {
    auto deleted = bookmark->second;

    for (auto it = bookmarks.begin(); it != bookmarks.end(); ++it)
    {
      if ((it != bookmark) && (it->second == deleted))
      {
        it->second = std::next(deleted);
        if ((it->second == phoneBook.end() && (phoneBook.begin() != phoneBook.end())))
        {
          it->second = std::prev(it->second);
        }
      }
    }
    bookmark->second = std::next(bookmark->second);
    phoneBook.erase(deleted);
    if ((bookmark->second == phoneBook.end() && !phoneBook.empty()))
    {
      --bookmark->second;
    }
  }
  else
  {
    out << invalidBookmark;
  }
}

CommandShowRecord::CommandShowRecord(const std::string& markName):
  markName_(markName)
{
}
void CommandShowRecord::execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out)
{
  auto bookmark = bookmarks.find(markName_);
  if (bookmark != bookmarks.end())
  {
    if (bookmark->second != phoneBook.end())
    {
      phoneBook.show(bookmark->second);
    }
    else
    {
      out << empty;
    }
  }
  else
  {
    out << invalidBookmark;
  }
}

CommandMoveBookmark::CommandMoveBookmark(const std::string& markName, std::string steps):
  markName_(markName),
  steps_(steps)
{
}
void CommandMoveBookmark::execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out)
{

  auto bookmark = bookmarks.find(markName_);
  if (bookmark != bookmarks.end())
  {
    if (steps_ == "first")
    {
      bookmark->second = phoneBook.begin();
      return;
    }
    if (steps_ == "last")
    {
      bookmark->second = std::prev(phoneBook.end());
      return;
    }
    char* end = nullptr;
    int steps = std::strtol(steps_.c_str(), &end, 10);

    if (*end)
    {
      out << invalidStep;
      return;
    }
    int maxStep = steps > 0 ? std::distance(bookmark->second, phoneBook.end()) + 1 :
        std::distance(phoneBook.begin(), bookmark->second) + 1;
    if (abs(steps) < maxStep)
    {
      std::advance(bookmark->second, steps);
    }
    else
    {
      out << invalidStep;
    }
  }
  else
  {
    out << invalidBookmark;
  }
}

void CommandInvalid::execute(PhoneBook&, bookmarksType&, std::ostream& out)
{
  out << invalidCommand;
}
