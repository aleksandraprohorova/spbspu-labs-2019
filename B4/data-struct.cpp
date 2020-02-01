#include "data-struct.hpp"
#include <iostream>
#include "manipulator.hpp"


std::istream& operator>>(std::istream& in, DataStruct& dataStruct)
{
  in >> blank >> dataStruct.key1 >> blank;
  if (in.fail())
  {
    return in;
  }
  if ((in.peek() != ',') || (abs(dataStruct.key1) > 5))
  {
    if (in.eof())
    {
      in.clear(in.rdstate() & ~std::ios_base::eofbit);;
    }
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.get();

  in >> blank >> dataStruct.key2 >> blank;
  if (in.fail())
  {
    return in;
  }
  if ((in.peek() != ',') || (abs(dataStruct.key2) > 5))
  {
    if (in.eof())
    {
      in.clear(in.rdstate() & ~std::ios_base::eofbit);;
    }
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.get();
  in >> blank;
  getline(in, dataStruct.str);
  if (in.fail())
  {
    return in;
  }
  return in;
}
std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct)
{
  out << dataStruct.key1 << "," << dataStruct.key2 << "," << dataStruct.str << "\n";
  return out;
}
