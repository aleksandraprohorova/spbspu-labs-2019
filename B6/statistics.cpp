#include "statistics.hpp"

get_statistics::get_statistics():
  mean(0),
  positive(0),
  negative(0),
  sumOfOdd(0),
  sumOfEven(0),
  isFirstEqualLast(true),
  quantity(0),
  isFirst(true)
{
}
void get_statistics::operator()(int number)
{
  if (isFirst)
  {
    first = number;
    min = number;
    max = number;
    isFirst = false;
  }
  else
  {
    isFirstEqualLast = (first == number);
    max = std::max(max, number);
    min = std::min(min, number);
  }

  mean = (mean * quantity + number) / (quantity + 1);
  ++quantity;

  if (number > 0)
  {
    ++positive;
  }
  if (number < 0)
  {
    ++negative;
  }
  (number % 2 ? sumOfOdd : sumOfEven) += number;
}

bool get_statistics::empty() const
{
  return (quantity == 0);
}
std::ostream& operator<<(std::ostream& out, const get_statistics& statistics)
{
  if (statistics.empty())
  {
    out << "No Data\n";
    return out;
  }
  out << "Max: " << statistics.max << "\n"
      << "Min: " << statistics.min << "\n"
      << "Mean: " << std::fixed << statistics.mean << "\n"
      << "Positive: " << statistics.positive << "\n"
      << "Negative: " << statistics.negative << "\n"
      << "Odd Sum: " << statistics.sumOfOdd << "\n"
      << "Even Sum: " << statistics.sumOfEven << "\n"
      << "First/Last Equal: ";
  statistics.isFirstEqualLast ? out << "yes" : out << "no";
  out << "\n";
  return out;
}
