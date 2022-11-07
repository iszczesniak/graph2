#ifndef GRAPH_INTERFACE_HPP
#define GRAPH_INTERFACE_HPP

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
