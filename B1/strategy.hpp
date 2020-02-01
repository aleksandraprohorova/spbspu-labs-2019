#ifndef AP_STRATEGY
#define AP_STRATEGY

template <typename Container>
struct StrategyBrackets
{
  using valueType = typename Container::value_type;
  using containerType = Container;

  static int begin(Container&)
  {
    return 0;
  }

  static int end(Container& container)
  {
    return container.size();
  }

  static valueType& get(Container& container, int index)
  {
    return container[index];
  }
};

template <typename Container>
struct StrategyAt
{
  using valueType = typename Container::value_type;
  using containerType = Container;

  static int begin(Container&)
  {
    return 0;
  }

  static int end(Container& container)
  {
    return container.size();
  }

  static valueType& get(Container& container, int index)
  {
    return container.at(index);
  }
};

template <typename Container>
struct StrategyIterators
{
  using valueType = typename Container::value_type;
  using containerType = Container;

  static auto begin(Container& container)->decltype(container.begin())
  {
    return container.begin();
  }

  static auto end(Container& container)->decltype(container.end())
  {
    return container.end();
  }

  template <typename Iterator>
  static valueType& get(Container&, Iterator it)
  {
    return (*it);
  }

};

#endif // AP_STRATEGY
