#include <iostream>
#include <set>

using namespace std;

template <typename Weight>
struct weight
{
  Weight m_weight;

  weight(const Weight &weight): m_weight(weight)
  {
  }
};

template <typename Weight>
auto &
get_weight(weight<Weight> &a)
{
  return a.m_weight;
}

template <typename Weight>
const auto &
get_weight(const weight<Weight> &a)
{
  return a.m_weight;
}

template <typename Resources>
struct resources
{
  Resources m_resources;

  resources(const Resources &resources): m_resources(resources)
  {
  }
};

// The non-const getter.
template <typename Resources>
auto &
get_resources(resources<Resources> &a)
{
  return a.m_resources;
}

// The const getter.
template <typename Resources>
const auto &
get_resources(const resources<Resources> &a)
{
  return a.m_resources;
}

template <typename... Props>
struct edge: Props...
{
  edge(const Props &... props): Props(props)...
  {
  }
};

int
main()
{
  // The getter works for the base object.
  edge<weight<const int>, resources<std::set<int>>> e(1, std::set{10});

  cout << get_weight(e) << endl;
  //  get_resources(e).insert(1);
}
