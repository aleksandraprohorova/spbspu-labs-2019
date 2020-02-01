#ifndef AP_TOKEN
#define AP_TOKEN

#include <string>
#include <iosfwd>

struct token_t
{
  enum KindOfToken
  {
    WORD,
    DASH,
    PUNCTUATION_MARK,
    NUMBER,
    INVALID
  };
  KindOfToken kind;
  std::string data;
  size_t line;
  size_t column;
  bool operator==(const token_t& other) const;
  bool operator!=(const token_t& other) const;
};

std::ostream& operator<<(std::ostream& out, const token_t& token);

#endif // AP_TOKEN
