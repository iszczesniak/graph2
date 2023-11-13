#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "graph_interface.hpp"

#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

// *******************************************************************
// A directed graph of the number of vertexes given in advance.
// *******************************************************************

// The graph.
template <typename Vertex>
struct graph
{
  // The type of the container for storing vertexes: the vector.  We
  // cannot allow the vector to relocate its elements (the vertexes),
  // because that would invalidate references to the vertexes stored
  // in edges.  Therefore we reserve the memory for the given number
  // of vertexes in the constructor.
  using vertexes_type = std::vector<Vertex>;

  // Here we store vertexes.
  vertexes_type m_vertexes;

  // The size type.
  using size_type = typename vertexes_type::size_type;

  // You have to give the number of vertexs to create the graph.
  graph(size_type n)
  {
    m_vertexes.reserve(n);
  }

  // Can't copy, because edges have references to vertexes.  I would
  // have to implement this.  For now, I'm disabling copying.
  graph(const graph &) = delete;

  // Can move.
  graph(graph &&) = default;
};

template <typename Edge, typename... Props>
struct vertex: Props...
{
  using edge_type = Edge;
  // The data structure for storing edges.
  using edges_type = std::vector<edge_type>;

  vertex(Props &&... props): Props(std::forward<Props>(props))...
  {
  }

  // We're using a vector, because we're frequently iterating over the
  // edges of a vertex.  When using a vector, references to edges can
  // invalidate when we add a new vertex, because the vector can be
  // reallocated.  However, we don't mind that, because we don't store
  // references to edges anywhere.
  edges_type m_edges;

  template <typename... EdgeProps>
  void
  add_edge(const vertex &t, EdgeProps &&... ep)
  {
    m_edges.emplace_back(*this, t, std::forward<EdgeProps>(ep)...);
  }

  // Vertex objects are the same only when it's the same object.
  bool
  operator == (const vertex &a) const
  {
    return this == &a;
  }
};

template <template<typename, typename...> typename Vertex,
          typename... Props>
struct edge: Props...
{
  using vertex_type = Vertex<edge>;

  // The source node of the edge.
  const vertex_type &m_source;
  // The target node of the edge.
  const vertex_type &m_target;

  edge(const vertex_type &source, const vertex_type &target,
       Props &&... props):
    m_source(source), m_target(target),
    Props(std::forward<Props>(props))...
    {
    }

  // Edge objects are the same only when it's the same object.
  bool operator == (const edge &e)
  {
    return this == &e;
  }
};

template <template<typename, typename...> typename Vertex,
          typename... Props>
std::ostream &
operator << (std::ostream &os, const edge<Vertex, Props...> &e)
{
  os << "edge(";
  (os << ... << static_cast<Props>(e));
  os << ")";

  return os;
}

// *******************************************************************
// The graph functions.

template <typename Vertex>
auto
num_vertexes(const graph<Vertex> &g)
{
  return g.m_vertexes.size();
}

template <typename Vertex>
auto &
get_vertexes(graph<Vertex> &g)
{
  return g.m_vertexes;
}

template <typename Vertex>
const auto &
get_vertexes(const graph<Vertex> &g)
{
  return g.m_vertexes;
}

// *******************************************************************
// The vertex functions.

template <typename Edge, typename... Props>
auto &
get_edges(vertex<Edge, Props...> &v)
{
  return v.m_edges;
}

template <typename Edge, typename... Props>
const auto &
get_edges(const vertex<Edge, Props...> &v)
{
  return v.m_edges;
}

template <typename Edge, typename... Props>
std::ostream &
operator << (std::ostream &os, const vertex<Edge, Props...> &v)
{
  os << "vertex(" << "name = " << get_name(v) << ")";

  return os;
}

// *******************************************************************
// The edge functions.

template <template<typename, typename...> typename Vertex,
          typename... Props>
auto &
get_source(edge<Vertex, Props...> &e)
{
  return e.m_source;
}

template <template<typename, typename...> typename Vertex,
          typename... Props>
const auto &
get_source(const edge<Vertex, Props...> &e)
{
  return e.m_source;
}

template <template<typename, typename...> typename Vertex,
          typename... Props>
auto &
get_target(edge<Vertex, Props...> &e)
{
  return e.m_target;
}

template <template<typename, typename...> typename Vertex,
          typename... Props>
const auto &
get_target(const edge<Vertex, Props...> &e)
{
  return e.m_target;
}

// *******************************************************************
// The helper functions.

template <typename Vertex>
auto &
add_vertex(graph<Vertex> &g, const std::string name)
{
  assert(g.m_vertexes.size() < g.m_vertexes.capacity());
  auto index = g.m_vertexes.size();
  g.m_vertexes.emplace_back(index, name);
  return g.m_vertexes.back();
}

template <typename Vertex, typename... Props>
void
add_edge(Vertex &s, const Vertex &t, Props &&... props) requires requires
{
  s.add_edge(t, std::forward<Props>(props)...);
}
{
  s.add_edge(t, std::forward<Props>(props)...);
}

template <typename Vertex, typename... Props>
void
add_edge_pair(Vertex &v1, const Vertex &v2, Props &&... props)
{
  add_edge(v1, v2, std::forward<Props>(props)...);
  add_edge(v2, v1, std::forward<Props>(props)...);
}

// *******************************************************************
// Traits.

template <typename Edge, typename... Props>
struct index_traits<vertex<Edge, Props...>>
{
  using type = vertex<Edge, Props...>::index_type;
};

template <typename Vertex>
struct vertex_traits<graph<Vertex>>
{
  using type = Vertex;
};

template <template<typename, typename...> typename Vertex,
          typename... Props>
struct vertex_traits<edge<Vertex, Props...>>
{
  using type = typename edge<Vertex, Props...>::vertex_type;
};

#endif // GRAPH_HPP
