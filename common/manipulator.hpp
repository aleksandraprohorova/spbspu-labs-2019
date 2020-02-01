#ifndef AP_MANIPULATOR
#define AP_MANIPULATOR

#include <istream>

std::istream& blank(std::istream& in);

/*struct skip_blank_t
{
  extern const int SKIP_BLANK_INDEX;
  extern const int SKIP_BLANK;
  extern const int NO_SKIP_BLANK;
};*/
extern const int SKIP_BLANK_INDEX;
extern const int SKIP_BLANK;
extern const int NO_SKIP_BLANK;

std::istream& skipBlank(std::istream& in);
std::istream& noSkipBlank(std::istream& in);

#endif // AP_MANIPULATOR
