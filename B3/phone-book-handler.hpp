#ifndef AP_PHONE_BOOK_HANDLER
#define AP_PHONE_BOOK_HANDLER

#include <unordered_map>
#include <memory>

#include "phone-book.hpp"

using bookmarksType = std::unordered_map<std::string, PhoneBook::iterator>;

class PhoneBookCommand
{
public:
  virtual ~PhoneBookCommand() = default;
  virtual void execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out) = 0;
};

std::istream& operator>>(std::istream& in, std::unique_ptr<PhoneBookCommand>& command);

class CommandAddRecord: public PhoneBookCommand
{
public:
  CommandAddRecord(const PhoneBook::value_type& record);
  void execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out) override;
private:
  PhoneBook::value_type record_;
};

class CommandStoreBookmark: public PhoneBookCommand
{
public:
  CommandStoreBookmark(const std::string& markName, const std::string& newMarkName);
  void execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out) override;
private:
  std::string markName_;
  std::string newMarkName_;
};

class CommandInsertBeforeBookmark: public PhoneBookCommand
{
public:
  CommandInsertBeforeBookmark(const std::string& markName, const PhoneBook::value_type& record);
  void execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out) override;
private:
  std::string markName_;
  PhoneBook::value_type record_;
};
class CommandInsertAfterBookmark: public PhoneBookCommand
{
public:
  CommandInsertAfterBookmark(const std::string& markName, const PhoneBook::value_type& record);
  void execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out) override;
private:
  std::string markName_;
  PhoneBook::value_type record_;
};

class CommandDeleteRecord: public PhoneBookCommand
{
public:
  CommandDeleteRecord(const std::string& markName);
  void execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out) override;
private:
  std::string markName_;
};

class CommandShowRecord: public PhoneBookCommand
{
public:
  CommandShowRecord(const std::string& markName);
  void execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out) override;
private:
  std::string markName_;
};

class CommandMoveBookmark: public PhoneBookCommand
{
public:
  CommandMoveBookmark(const std::string& markName, std::string steps);
  void execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out) override;
private:
  std::string markName_;
  std::string steps_;
};

class CommandInvalid: public PhoneBookCommand
{
public:
  void execute(PhoneBook& phoneBook, bookmarksType& bookmarks, std::ostream& out) override;
};

#endif // AP_PHONE_BOOK_HANDLER
