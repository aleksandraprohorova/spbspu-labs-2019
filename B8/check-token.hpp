#ifndef CHECK_TOKEN
#define CHECK_TOKEN

#include "token.hpp"

class check_token
{
public:
  check_token();
  token_t operator()(const token_t& token);
private:
  bool isFirst;
  token_t last;
};

#endif // CHECK_TOKEN
