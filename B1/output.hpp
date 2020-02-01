#ifndef AP_OUTPUT
#define AP_OUTPUT

#include <iostream>

template <typename T, typename = typename T::const_iterator>
std::ostream& operator<<(std::ostream& out, const T& container)
{
  for (auto element: container)
  {
    out << element << " ";
  }
  out << "\n";
  return out;
}

#endif // AP_OUTPUT
