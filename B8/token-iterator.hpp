#ifndef AP_TOKEN_ITERATOR
#define AP_TOKEN_ITERATOR

#include <string>
#include <istream>

#include "token.hpp"

class TokenIterator: public std::iterator<std::input_iterator_tag, token_t>
{
public:
  TokenIterator();
  TokenIterator(std::istream& in);

  const token_t& operator*() const;
  bool operator==(const TokenIterator& other);
  bool operator!=(const TokenIterator& other);
  TokenIterator& operator++();
  TokenIterator operator++(int);

private:
  std::istream* in_;
  token_t currentToken_;
  std::string dataForNextToken_;
  size_t line_;
  size_t column_;
  char decimalPoint_;

  char getNextSymbol();
};

#endif // AP_TOKEN_ITERATOR
