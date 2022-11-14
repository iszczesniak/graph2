#ifndef GRAPH_INTERFACE_HPP
#define GRAPH_INTERFACE_HPP

// *******************************************************************
// The vertex traits

template<typename>
struct vertex_traits;

template <typename T>
using Vertex = typename vertex_traits<T>::type;

// *******************************************************************
// The index traits

template<typename>
struct index_traits;

template <typename T>
using Index = typename index_traits<T>::type;

// *******************************************************************
// The edge traits

template<typename>
struct edge_traits;

template <typename G>
using Edge = typename edge_traits<G>::type;

// *******************************************************************
// The weight traits

template<typename>
struct weight_traits;

template <typename T>
using Weight = typename weight_traits<T>::type;

#endif // GRAPH_INTERFACE_HPP
