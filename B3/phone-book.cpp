#include "phone-book.hpp"

#include <iostream>

PhoneBook::iterator PhoneBook::insert(iterator pos, const value_type& record)
{
  return records_.insert(pos, record);
}
void PhoneBook::pushBack(const value_type& record)
{
  records_.push_back(record);
}
void PhoneBook::replace(iterator pos, const value_type& record)
{
  *pos = record;
}
PhoneBook::iterator PhoneBook::erase(iterator pos)
{
  return records_.erase(pos);
}
void PhoneBook::show(iterator pos) const
{
  std::cout << pos->first << " " << pos->second << "\n";
}
PhoneBook::iterator PhoneBook::begin()
{
  return records_.begin();
}
PhoneBook::iterator PhoneBook::end()
{
  return records_.end();
}
PhoneBook::const_iterator PhoneBook::cbegin() const
{
  return records_.cbegin();
}
PhoneBook::const_iterator PhoneBook::cend() const
{
  return records_.cend();
}

int PhoneBook::size() const
{
  return records_.size();
}
bool PhoneBook::empty() const
{
  return records_.empty();
}
