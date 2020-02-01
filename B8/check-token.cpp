#include "check-token.hpp"

#include <stdexcept>

check_token::check_token():
  isFirst(true)
{
}
token_t check_token::operator()(const token_t& token)
{
  if (isFirst)
  {
    isFirst = false;
    last = token;
    if ((last.kind == token_t::INVALID) ||
        (last.kind == token_t::PUNCTUATION_MARK) ||
        (last.kind == token_t::DASH) ||
        (last.kind == token_t::INVALID))
    {
      std::string message = "Input failed.\nLine: " + std::to_string(last.line) + "\nColumn: " + std::to_string(last.column);
      throw std::runtime_error(message);
    }
    if (last.data.size() > 20)
    {
      throw std::runtime_error("Invalid size of token.");
    }
    return token;
  }
  if (token.kind == token_t::PUNCTUATION_MARK)
  {
    if ((last.kind == token_t::PUNCTUATION_MARK) ||
        (last.kind == token_t::DASH))
    {
      throw std::runtime_error("Contracting punctuation is forbidden.");
    }
  }
  if (token.kind == token_t::DASH)
  {
    if (((last.kind == token_t::PUNCTUATION_MARK) && (last.data != ",")) ||
        (last.kind == token_t::DASH))
    {
      throw std::runtime_error("Contracting punctuation is forbidden.");
    }
  }
  if (token.kind == token_t::INVALID)
  {
    std::string message = "Input failed.\nLine: " + std::to_string(last.line) + "\nColumn: " + std::to_string(last.column);
    throw std::runtime_error(message);
  }
  if (token.data.size() > 20)
  {
    throw std::runtime_error("Invalid size of token.");
  }
  last = token;
  return token;
}
