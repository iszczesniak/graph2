#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "graph_interface.hpp"
#include "props_interface.hpp"

#include <cassert>
#include <iostream>
#include <numeric>
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
};

template <template<typename, typename...> typename Vertex,
          typename... Props>
struct edge: Props...
{
  using vertex_type = Vertex<edge>;

  // The source vertex of the edge.
  const vertex_type &m_source;
  // The target vertex of the edge.
  const vertex_type &m_target;

  // Creates an edge with the properties defaulted.
  edge(const vertex_type &source, const vertex_type &target):
    m_source(source), m_target(target)
    {
    }

  edge(const vertex_type &source, const vertex_type &target,
       Props &&... props):
    m_source(source), m_target(target),
    Props(std::forward<Props>(props))...
    {
    }
};

template <template<typename, typename...> typename Vertex,
          typename Prop, typename... Props>
std::ostream &
operator << (std::ostream &os, const edge<Vertex, Prop, Props...> &e)
{
  os << "edge(";
  os << static_cast<const Prop &>(e);
  ((os << ", " << static_cast<const Props &>(e)), ...);
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
auto
num_edges(const graph<Vertex> &g)
{
  return std::accumulate(g.m_vertexes.begin(), g.m_vertexes.end(), 0,
                         [](auto c, const auto &v)
                         {return c + get_edges(v).size();});
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

// We consider vertex objects equal when they are the same object.
template <typename Edge, typename... Props>
bool
operator == (const vertex<Edge, Props...> &v1,
             const vertex<Edge, Props...> &v2)
{
  return &v1 == &v2;
}

template <typename Edge, typename Prop, typename... Props>
std::ostream &
operator << (std::ostream &os, const vertex<Edge, Prop, Props...> &v)
{
  os << "vertex(";
  os << static_cast<const Prop &>(v);
  ((os << ", " << static_cast<const Props &>(v)), ...);
  os << ")";

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

// We consider edge objects equal when they are the same object.
template <template<typename, typename...> typename Vertex,
          typename... Props>
bool operator == (const edge<Vertex, Props...> &e1,
                  const edge<Vertex, Props...> &e2)
{
  return &e1 == &e2;
}

// *******************************************************************
// The helper functions.

template <typename Vertex>
auto &
add_vertex(graph<Vertex> &g, const std::string name)
{
  assert(g.m_vertexes.size() < g.m_vertexes.capacity());
  auto key = g.m_vertexes.size();
  g.m_vertexes.emplace_back(key, name);
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
struct key_traits<vertex<Edge, Props...>>
{
  using type = typename vertex<Edge, Props...>::key_type;
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

template <typename Vertex>
struct edge_traits<graph<Vertex>>
{
  using type = typename Vertex::edge_type;
};

template <template<typename, typename...> typename Vertex,
          typename... Props>
struct weight_traits<edge<Vertex, Props...>>
{
  using type = typename edge<Vertex, Props...>::weight_type;
};

#endif // GRAPH_HPP
