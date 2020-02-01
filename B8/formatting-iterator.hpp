#ifndef AP_FORMATTING_ITERATOR
#define AP_FORMATTING_ITERATOR

#include <string>
#include <ostream>
#include <memory>

#include "token.hpp"

class FormattingIterator: public std::iterator<std::output_iterator_tag, token_t>
{
public:
  FormattingIterator(std::ostream& out, size_t lineWidth);
  FormattingIterator& operator*();
  void operator=(const token_t& token);
  void operator++(){}
  void operator++(int){}
private:
  class Impl;
  std::shared_ptr<Impl> pimpl_;
};

#endif // AP_FORMATTING_ITERATOR
