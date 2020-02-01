#include "container-factorial.hpp"

ContainerFactorial::iterator ContainerFactorial::begin() const
{
  return iterator(1);
}

ContainerFactorial::iterator ContainerFactorial::end() const
{
  return iterator(11);
}

ContainerFactorial::const_iterator ContainerFactorial::cbegin() const
{
  return const_iterator(1);
}

ContainerFactorial::const_iterator ContainerFactorial::cend() const
{
  return const_iterator(11);
}

size_t ContainerFactorial::size() const
{
  return std::distance(begin(), end());
}
size_t ContainerFactorial::max_size() const
{
  return size();
}
bool ContainerFactorial::empty() const
{
  return (begin() != end());
}
