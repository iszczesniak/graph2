#include <type_traits>

template <typename>
struct weight_traits;

template <typename T>
using Weight = typename weight_traits<T>::type;

template <typename Weight>
struct A
{
  Weight m_weight;
};

template <typename Weight>
struct weight_traits<A<Weight>>
{
  using type = Weight;
};

template <typename>
struct resource_traits;

template <typename Resource, typename Weight>
struct B: A<Weight>
{
  Resource m_resource;
};

template <typename Resource, typename Weight>
struct resource_traits<B<Resource, Weight>>
{
  using type = Resource;
};

int
main()
{
  static_assert(std::is_same_v<int, Weight<A<int>>>);
  static_assert(std::is_same_v<int, Weight<B<int, int>>>);
}
