#include "container-factorial.hpp"

#include <stdexcept>

#include <iostream>

ContainerFactorial::iterator::iterator(int index):
  index_(index)
{
  if (index_ > upperBound)
  {
    throw std::out_of_range("Index can't be more than upperBound.\n");
  }
  if (index_ <= 0)
  {
    throw std::out_of_range("Index must be positive number.\n");
  }
  value_ = 1;
  for (int i = 2; i <= index_; ++i)
  {
    value_ = value_ * i;
  }
}

int ContainerFactorial::iterator::operator*()
{
  return value_;
}
bool ContainerFactorial::iterator::operator==(const iterator& other) const
{
  return (index_ == other.index_);
}
bool ContainerFactorial::iterator::operator!=(const iterator& other) const
{
  return !(*this == other);
}
ContainerFactorial::iterator& ContainerFactorial::iterator::operator++()
{
  if (index_ == upperBound)
  {
    throw std::out_of_range("Index can't be more than upperBound.\n");
  }
  ++(index_);
  value_ *= index_;
  return (*this);
}
ContainerFactorial::iterator& ContainerFactorial::iterator::operator--()
{
  if (index_ == 0)
  {
    throw std::out_of_range("Index can't be less than zero.\n");
  }
  value_ /= index_;
  --(index_);
  return (*this);
}

ContainerFactorial::iterator ContainerFactorial::iterator::operator++(int)
{
  iterator temp(*this);
  this->operator++();
  return --temp;
}
ContainerFactorial::iterator ContainerFactorial::iterator::operator--(int)
{
  iterator temp(*this);
  this->operator--();
  return temp;
}
