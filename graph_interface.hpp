#ifndef GRAPH_INTERFACE_HPP
#define GRAPH_INTERFACE_HPP

// This file has only trait declarations, and type functions (i.e.,
// type aliases).

// I could also declare here a template of a property getter like
// this:
//
// template <typename T>
// auto get_weight(const T &);

// Then I could specialize the getter for a class that has the weight
// property:
//
// struct A
// {
//    double m_weight;
// };
//
// template <>
// auto get_weight(const A &a)
// {
//   return a.m_weight;
// }

// The above specialization is explicit, because A is not templated.
// However, if A was templated, we would have to partially specialize
// the getter, and the function partial specialization is not allowed
// in C++.  My types are templated, so I wouldn't be able to
// specialize partially the declations of the getters.

// *******************************************************************
// The vertex traits

template<typename>
struct vertex_traits;

template <typename T>
using Vertex = typename vertex_traits<T>::type;

// *******************************************************************
// The edge traits

template<typename>
struct edge_traits;

template <typename G>
using Edge = typename edge_traits<G>::type;

#endif // GRAPH_INTERFACE_HPP
