#ifndef AP_PHONE_BOOK
#define AP_PHONE_BOOK

#include <utility>
#include <list>
#include <vector>
#include <string>

class PhoneBook
{
public:
  using value_type = std::pair<std::string, std::string>;
  using iterator = std::list<value_type>::iterator;
  using const_iterator = std::list<value_type>::const_iterator;
  using difference_type = std::list<value_type>::difference_type;

  iterator insert(iterator pos, const value_type& record);
  void pushBack(const value_type& record);

  void replace(iterator pos, const value_type& record);
  iterator erase(iterator pos);

  void show(iterator pos) const;

  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;

  int size() const;
  bool empty() const;

private:
  std::list<value_type> records_;
};

#endif // AP_PHONE_BOOK
