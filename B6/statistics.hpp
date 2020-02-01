#ifndef AP_STATISTICS
#define AP_STATISTICS

#include <ostream>

struct get_statistics
{
  int max;
  int min;
  double mean;
  int positive;
  int negative;
  long sumOfOdd;
  long sumOfEven;
  bool isFirstEqualLast;

  get_statistics();

  void operator()(int number);

  bool empty() const;

private:
  int quantity;
  int first;
  bool isFirst;
};

std::ostream& operator<<(std::ostream& out, const get_statistics& statistics);

#endif // AP_STATISTICS
