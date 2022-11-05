#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "units.hpp"

#include <set>
#include <string>
#include <vector>

// *******************************************************************
// A directed graph of the number of vertex given in advance.
// An edge has a weight and a set of units.
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
  using size_type = vertexes_type::size_type;

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

template <typename Edge>
struct vertex
{
  // The data structure for storing edges.
  using edges_type = std::vector<Edge>;

  // The name of the vertex.
  std::string m_name;

  vertex(std::string name = {}): m_name(name)
  {
  }

  // We're using a vector, because we're frequently iterating over the
  // edges of a vertex.  When using a vector, references to edges can
  // invalidate when we add a new vertex, because the vector can be
  // reallocated.  However, we don't mind that, because we don't store
  // references to edges anywhere.
  edges_type m_edges;
};

template <typename Weight>
struct edge
{
  using weight_type = Weight;
  // The type of available units.
  using units_type = SU;

  // The source node of the edge.
  const vertex<edge> &m_source;
  // The target node of the edge.
  const vertex<edge> &m_target;

  // The weight.
  weight_type m_weight;

  // The avilable units.
  units_type m_units;

  edge(const vertex<edge> &source, const vertex<edge> &target,
       weight_type weight, units_type units = {}):
    m_source(source), m_target(target), m_weight(weight), m_units(units)
  {
  }
};

// *******************************************************************
// The graph functions.

template <typename Vertex>
auto
num_vertexes(const graph<Vertex> &g)
{
  g.m_vertexes.size();
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

template <typename Edge>
const auto &
get_name(const vertex<Edge> &v)
{
  return v.m_name;
}

template <typename Edge>
auto &
get_edges(vertex<Edge> &v)
{
  return v.m_edges;
}

template <typename Edge>
const auto &
get_edges(const vertex<Edge> &v)
{
  return v.m_edges;
}

// *******************************************************************
// The edge functions.

template <typename Weight>
auto &
get_source(edge<Weight> &e)
{
  return e.m_source;
}

template <typename Weight>
const auto &
get_source(const edge<Weight> &e)
{
  return e.m_source;
}

template <typename Weight>
auto &
get_target(edge<Weight> &e)
{
  return e.m_target;
}

template <typename Weight>
const auto &
get_target(const edge<Weight> &e)
{
  return e.m_target;
}

template <typename Weight>
const auto &
get_weight(const edge<Weight> &e)
{
  return e.m_weight;
}

template <typename Weight>
auto &
get_units(edge<Weight> &e)
{
  return e.m_units;
}

template <typename Weight>
const auto &
get_units(const edge<Weight> &e)
{
  return e.m_units;
}

// *******************************************************************
// The helper functions.

template <typename Vertex>
auto &
add_vertex(graph<Vertex> &g, const std::string name)
{
  assert(g.m_vertexes.size() < g.m_vertexes.capacity());
  g.m_vertexes.emplace_back(name);
  return g.m_vertexes.back();
}

template <typename Edge>
void
add_edge(vertex<Edge> &s, const vertex<Edge> &t,
         typename Edge::weight_type w,
         typename Edge::units_type u = {})
{
  s.m_edges.emplace_back(s, t, w, u);
}

template <typename Edge>
void
add_edge_pair(vertex<Edge> &v1, vertex<Edge> &v2,
              typename Edge::weight_type w,
              typename Edge::units_type u = {})
{
  add_edge(v1, v2, w, u);
  add_edge(v2, v1, w, u);
}

#endif // GRAPH_HPP
