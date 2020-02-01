#include "token.hpp"
#include <ostream>

bool token_t::operator==(const token_t& other) const
{
  return ((kind == other.kind) && (data == other.data));
}
bool token_t::operator!=(const token_t& other) const
{
  return !(*this == other);
}
std::ostream& operator<<(std::ostream& out, const token_t& token)
{
  out << token.data << '\n';
  return out;
}
