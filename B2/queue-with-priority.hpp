#ifndef AP_QUEUE_WITH_PRIORITY
#define AP_QUEUE_WITH_PRIORITY

#include <list>
#include <stdexcept>

#include <functional>

template <typename T>
class QueueWithPriority
{
public:

  enum class ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  bool operator==(const QueueWithPriority& other) const;
  bool operator!=(const QueueWithPriority& other) const;

  void putElementToQueue(const T& element, ElementPriority priority);

  template <typename handlerType>
  void handleElement(handlerType handler);

  void accelerate();

  bool empty() const;
  int size() const;

  void swap(QueueWithPriority& other);

private:
  std::list<T> low;
  std::list<T> normal;
  std::list<T> high;

  T& getFrontElement();
  void removeFrontElement();
};

template <typename T>
bool QueueWithPriority<T>::operator==(const QueueWithPriority<T>& other) const
{
  return ((high == other.high) && (normal == other.normal) && (low == other.low));
}
template <typename T>
bool QueueWithPriority<T>::operator!=(const QueueWithPriority<T>& other) const
{
  return !(*this == other);
}

template <typename T>
void QueueWithPriority<T>::putElementToQueue(const T& element, ElementPriority priority)
{
  switch (priority)
  {
    case ElementPriority::HIGH:
    {
      high.push_back(element);
      break;
    }
    case ElementPriority::NORMAL:
    {
      normal.push_back(element);
      break;
    }
    case ElementPriority::LOW:
    {
      low.push_back(element);
      break;
    }
  }
}

template <typename T>
T& QueueWithPriority<T>::getFrontElement()
{
  if (!high.empty())
  {
    auto& element = high.front();
    return element;
  }
  if (!normal.empty())
  {
    auto& element = normal.front();
    return element;
  }
  if (!low.empty())
  {
    auto& element = low.front();
    return element;
  }
  throw std::invalid_argument("Queue is empty.\n");
}

template <typename T>
void QueueWithPriority<T>::removeFrontElement()
{
  if (!high.empty())
  {
    high.pop_front();
    return;
  }
  if (!normal.empty())
  {
    normal.pop_front();
    return;
  }
  if (!low.empty())
  {
    low.pop_front();
    return;
  }
  throw std::invalid_argument("Queue is empty.\n");
}

template <typename T>
template <typename handlerType>
void QueueWithPriority<T>::handleElement(handlerType handler)
{
  T& element = getFrontElement();
  handler(element);
  removeFrontElement();
}


template <typename T>
void QueueWithPriority<T>::accelerate()
{
  high.splice(high.end(), low);
}

template <typename T>
bool QueueWithPriority<T>::empty() const
{
  return (low.empty() && normal.empty() && high.empty());
}

template <typename T>
int QueueWithPriority<T>::size() const
{
  return (low.size() + normal.size() + high.size());
}

template <typename T>
void QueueWithPriority<T>::swap(QueueWithPriority<T>& other)
{
  low.swap(other.low);
  normal.swap(other.normal);
  high.swap(other.high);
}

#endif // AP_QUEUE_WITH_PRIORITY
