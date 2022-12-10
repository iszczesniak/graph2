#ifndef PROPS_HPP
#define PROPS_HPP

#include <iostream>

// -------------------------------------------------------------------
// weight
// -------------------------------------------------------------------

template <typename Weight>
struct weight
{
  using weight_type = Weight;
  weight_type m_weight;

  weight(const weight_type &weight): m_weight(weight)
  {
  }

  constexpr auto operator <=> (const weight &) const = default;
};

// The non-const getter.
template <typename Weight>
constexpr auto &
get_weight(weight<Weight> &a)
{
  return a.m_weight;
}

// The const getter.
template <typename Weight>
constexpr const auto &
get_weight(const weight<Weight> &a)
{
  return a.m_weight;
}

template <typename Weight>
std::ostream &
operator << (std::ostream &os, const weight<Weight> &w)
{
  os << "weight = " << w.m_weight;

  return os;
}

// -------------------------------------------------------------------
// resources
// -------------------------------------------------------------------

template <typename Resources>
struct resources
{
  Resources m_resources;

  resources(const Resources &resources): m_resources(resources)
  {
  }

  constexpr auto operator <=> (const resources &) const = default;
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

template <typename Resources>
std::ostream &
operator << (std::ostream &os, const resources<Resources> &w)
{
  os << "resources = " << w.m_resources;

  return os;
}

// -------------------------------------------------------------------
// index
// -------------------------------------------------------------------

template <typename Index>
struct index
{
  using index_type = Index;
  index_type m_index;

  index(const index_type &index): m_index(index)
  {
  }

  constexpr auto operator <=> (const index &) const = default;
};

// The non-const getter.
template <typename Index>
auto &
get_index(index<Index> &a)
{
  return a.m_index;
}

// The const getter.
template <typename Index>
const auto &
get_index(const index<Index> &a)
{
  return a.m_index;
}

template <typename Index>
std::ostream &
operator << (std::ostream &os, const index<Index> &w)
{
  os << "index = " << w.m_index;

  return os;
}

// -------------------------------------------------------------------
// name
// -------------------------------------------------------------------

template <typename Name>
struct name
{
  Name m_name;

  name(const Name &name): m_name(name)
  {
  }
};

// The non-const getter.
template <typename Name>
auto &
get_name(name<Name> &a)
{
  return a.m_name;
}

// The const getter.
template <typename Name>
const auto &
get_name(const name<Name> &a)
{
  return a.m_name;
}

template <typename Name>
std::ostream &
operator << (std::ostream &os, const name<Name> &w)
{
  os << "name = " << w.m_name;

  return os;
}

#endif // PROPS_HPP
