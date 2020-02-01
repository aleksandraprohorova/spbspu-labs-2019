#include <iostream>

#include "phone-book-handler.hpp"

std::unique_ptr<PhoneBookCommand> getCommand(std::istream& in);

void iterators1()
{
  std::string line;
  PhoneBook phoneBook;
  bookmarksType bookmarks;
  bookmarks.insert(std::make_pair("current", phoneBook.end()));

  std::cin >> std::noskipws;

  std::unique_ptr<PhoneBookCommand> command;
  while (std::cin >> std::ws >> command)
  {
    command->execute(phoneBook, bookmarks, std::cout);
  }

}
