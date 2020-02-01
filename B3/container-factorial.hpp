#ifndef AP_CONTAINER
#define AP_CONTAINER

#include <iterator>

class ContainerFactorial
{
public:
  class iterator: public std::iterator<std::bidirectional_iterator_tag, int,  std::ptrdiff_t, int, int>
  {
  public:

    iterator(int index);

    int operator*();

    iterator& operator++();
    iterator& operator--();

    iterator operator++(int);
    iterator operator--(int);

    bool operator!=(const iterator& other) const;
    bool operator==(const iterator& other) const;
  private:
    int index_;
    int value_;
    const int upperBound = 11;
  };

  using value_type = int;
  using const_iterator = iterator;
  using difference_type = std::ptrdiff_t;

  iterator begin() const;
  iterator end() const;

  const_iterator cbegin() const;
  const_iterator cend() const;

  size_t size() const;
  size_t max_size() const;
  bool empty() const;
};

#endif // AP_CONTAINER
