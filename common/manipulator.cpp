#include "manipulator.hpp"

std::istream& blank(std::istream& in)
{
  while (std::isblank(in.peek()))
  {
    in.get();
  }
  return in;
}

const int SKIP_BLANK_INDEX = std::ios_base::xalloc();
const int SKIP_BLANK = 0;
const int NO_SKIP_BLANK = 1;

std::istream& skipBlank(std::istream& in)
{
  in.iword(SKIP_BLANK_INDEX) = SKIP_BLANK;
  return in;
}
std::istream& noSkipBlank(std::istream& in)
{
  in.iword(SKIP_BLANK_INDEX) = NO_SKIP_BLANK;
  return in;
}
