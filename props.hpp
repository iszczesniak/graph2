#ifndef PROPS_HPP
#define PROPS_HPP

template <typename Weight>
struct weight
{
  Weight m_weight;

  weight(const Weight &weight): m_weight(weight)
  {
  }
};

// The non-const getter.
template <typename Weight>
auto &
get_weight(weight<Weight> &a)
{
  return a.m_weight;
}

// The const getter.
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

#endif // PROPS_HPP
