#include "token-iterator.hpp"

#include <iostream>
#include <boost/scope_exit.hpp>

TokenIterator::TokenIterator():
  in_(nullptr)
{
}

TokenIterator::TokenIterator(std::istream& in):
  in_(&in),
  line_(1),
  column_(0)
{
  const auto& facet = std::use_facet<std::numpunct<char>>(in_->getloc());
  decimalPoint_ = facet.decimal_point();
  operator++();
}

char TokenIterator::getNextSymbol()
{
  char tmp = dataForNextToken_.empty() ? in_->get() : dataForNextToken_.back();
  if (!dataForNextToken_.empty())
  {
    dataForNextToken_.pop_back();
  }
  return tmp;
}

const token_t& TokenIterator::operator*() const
{
  if (!in_)
  {
    throw std::logic_error("Istream is nullptr.");
  }
  return currentToken_;
}
bool TokenIterator::operator==(const TokenIterator& other)
{
  return (in_ == other.in_);
}
bool TokenIterator::operator!=(const TokenIterator& other)
{
  return !(*this == other);
}
TokenIterator& TokenIterator::operator++()
{
  if (!in_)
  {
    throw std::logic_error("Invalid istream");
  }

  currentToken_.kind = token_t::INVALID;
  currentToken_.line = line_;
  currentToken_.column = column_;
  currentToken_.data.clear();

  std::string& data = currentToken_.data;
  token_t::KindOfToken& currentKind_ = currentToken_.kind;

  BOOST_SCOPE_EXIT(&currentToken_)
  {
    if ((currentToken_.kind == token_t::DASH) && (currentToken_.data.size() != 3))
    {
      currentToken_.kind = token_t::INVALID;
    }
  }
  BOOST_SCOPE_EXIT_END

  while (!in_->eof() || !dataForNextToken_.empty())
  {
    char tmp = getNextSymbol();
    ++column_;
    if (std::isspace(tmp))
    {
      if (tmp == '\n')
      {
        column_ = 0;
        ++line_;
      }
      if (tmp == '\r')
      {
        column_ = 0;
      }
      if (!data.empty())
      {
        dataForNextToken_ = tmp;
        return *this;
      }
    }
    else if (std::isalpha(tmp))
    {
      switch (currentKind_)
      {
        case token_t::INVALID:
        {
          currentKind_ = token_t::WORD;
          data += tmp;
          break;
        }
        case token_t::WORD:
        {
          data += tmp;
          break;
        }
        case token_t::DASH:
        {
          dataForNextToken_ = tmp;
          return *this;
        }
        case token_t::PUNCTUATION_MARK:
        {
          dataForNextToken_ = tmp;
          return *this;
        }
        case token_t::NUMBER:
        {
          currentToken_.kind = token_t::INVALID;
          return *this;
        }
      }
    }
    else if (std::isdigit(tmp))
    {
      switch (currentKind_)
      {
        case token_t::INVALID:
        {
          currentKind_ = token_t::NUMBER;
          data += tmp;
          break;
        }
        case token_t::NUMBER:
        {
          data += tmp;
          break;
        }
        case token_t::DASH:
        {
          dataForNextToken_ = tmp;
          return *this;
        }
        case token_t::PUNCTUATION_MARK:
        {
          if ((data.back() == '+') || (data.back() == '-'))
          {
            currentKind_ = token_t::NUMBER;
            data += tmp;
            break;
          }
          dataForNextToken_ = tmp;
          return *this;
        }
        case token_t::WORD:
        {
          currentToken_.kind = token_t::INVALID;
          return *this;
        }
      }
    }
    else if ((tmp == decimalPoint_) && (currentKind_ == token_t::NUMBER) && std::isdigit(in_->peek()))
    {
      data += tmp;
    }
    else if (tmp == '-')
    {
      switch (currentKind_)
      {
        case token_t::INVALID:
        {
          currentKind_ = token_t::PUNCTUATION_MARK;
          data += tmp;
          break;
        }
        case token_t::PUNCTUATION_MARK:
        {
          if (data == "-")
          {
            data += tmp;
            currentKind_ = token_t::DASH;
            break;
          }
          else
          {
            dataForNextToken_ = tmp;
            return *this;
          }
        }
        case token_t::WORD:
        {
          if (data.back() == '-')
          {
            data.pop_back();
            dataForNextToken_ = "--";
            return *this;
          }
          else
          {
            data += tmp;
            break;
          }
        }
        case token_t::NUMBER:
        {
          dataForNextToken_ = tmp;
          return *this;
        }
        case token_t::DASH:
        {
          data += tmp;
          break;
        }
      }
    }
    else if (std::ispunct(tmp))
    {
      switch (currentKind_)
      {
        case token_t::INVALID:
        {
          data = tmp;
          currentKind_ = token_t::PUNCTUATION_MARK;
          break;
        }
        case token_t::DASH:
        {
          dataForNextToken_ = tmp;
          return *this;
        }
        case token_t::WORD:
        case token_t::NUMBER:
        case token_t::PUNCTUATION_MARK:
        {
          dataForNextToken_ = tmp;
          return *this;
        }
      }
    }
    else
    {
      break;
    }
  }
  if (data.empty())
  {
    in_ = nullptr;
    return *this;
  }
  return *this;
}
TokenIterator TokenIterator::operator++(int)
{
  TokenIterator tmp = *this;
  operator++();
  return tmp;
}
