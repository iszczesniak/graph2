#ifndef GRAPH_HPP
#define GRAPH_HPP

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
  // The available units.
  using units_type = std::set<unsigned>;

  // The source node of the edge.
  const vertex &m_source;
  // The target node of the edge.
  const vertex &m_target;

  // The weight.
  weight_type m_weight;

  // The avilable units.
  units_type m_units;

  edge(const vertex &source, const vertex &target, cost_type cost,
       units_type units = {}):
    m_source(source), m_target(target), m_cost(cost), m_units(units)
  {
  }
};

// *******************************************************************
// The units traits

template <typename>
struct units_traits;

template <>
struct units_traits<edge>
{
  using type = edge::units_type;
};

template <typename T>
using Units = typename units_traits<T>::type;

// *******************************************************************
// The functions.

template <typename Edge>
auto &
get_name(vertex<Edge> &v)
{
  return v.m_name;
}

template <typename Edge>
const auto &
get_edges(const vertex<Edge> &)
{
  return v.m_edges;
}

graph::size_type
num_vertexes(const graph &);

template <typename Weight>
const vertex &
get_source(const edge<Weight> &e)
{
  return 
}

const vertex &
get_target(const edge &);

const edge::cost_type &
get_cost(const edge &);

const edge::units_type &
get_units(const edge &);

const vertex::units_type &
get_units(const vertex &);

vertex &
add_vertex(graph &g, const std::string name,
           vertex::units_type units = {});

void
add_edge(graph &g, vertex &, const vertex &, edge::cost_type,
         edge::units_type = {});

void
add_edge_pair(graph &g, vertex &, vertex &,
              edge::cost_type, edge::units_type = {});

#endif // GRAPH_HPP
