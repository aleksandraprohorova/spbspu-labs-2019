#ifndef AP_DATA_STRUCT
#define AP_DATA_STRUCT

#include <string>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

std::istream& operator>>(std::istream& in, DataStruct& dataStruct);
std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct);

#endif // AP_DATA_STRUCT
