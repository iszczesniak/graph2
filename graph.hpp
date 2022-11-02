#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>
#include <set>
#include <string>
#include <tuple>
#include <vector>

// *******************************************************************
// A directed graph, where an edge has a weight and a set of units.
// *******************************************************************

struct vertex;
struct edge;

// The graph.
struct graph
{
  // The type of the container for storing vertexes: the vector.  We
  // cannot allow the vector to relocate its elements (the vertexes),
  // because that would invalidate references to the vertexes stored
  // in edges.  Therefore we reserve the memory for the vector in the
  // constructor.
  using vertexes_type = std::vector<vertex>;

  // Here we store vertexes.
  vertexes_type m_vertexes;

  // The size type.
  using size_type = vertexes_type::size_type;

  // Cannot default-initialize.
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

struct vertex
{
  // The data structure for storing edges.
  using edges_type = std::vector<edge>;
  // The type of the edge index.
  using index_type = edges_type::size_type;

  // The index of the vertex.
  index_type m_index;

  // The name of the vertex.
  std::string m_name;

  vertex(index_type index, std::string name = {})
    m_index(index), m_name(name)
  {
  }

  bool operator==(const vertex &b) const
  {
    return this == &b;
  }

  // We're using a vector, because we're frequently iterating over the
  // edges of a vertex.  When using a vector, iterators or references
  // to edges can invalidate when we add a new vertex, because the
  // vector can be reallocated.  However, we don't mind that, because
  // we don't store references to edges anywhere.
  edges_type m_edges;
};

template <typename W>
struct edge
{
  using weight_type = W;
  using units_type = std::set<unsigned>;

  // The source node of the edge.
  const vertex &m_source;
  // The target node of the edge.
  const vertex &m_target;

  // The cost of an edge.
  cost_type m_cost;

  // The units required to take the edge.
  units_type m_units;

  edge(const vertex &source, const vertex &target, cost_type cost,
       units_type units = {}):
    m_source(source), m_target(target), m_cost(cost), m_units(units)
  {
  }

  // We need this operator to establish order between edges.  This is
  // needed by the generic_label which defines order between labels.
  bool operator<(const edge &b) const
  {
    return this < &b;
  }

  bool operator==(const edge &b) const
  {
    return std::tie(m_source, m_target, m_cost, m_units) ==
      std::tie(b.m_source, b.m_target, b.m_cost, b.m_units);
  }
};

// *******************************************************************
// The vertex traits

template<typename>
struct vertex_traits;

template<>
struct vertex_traits<graph>
{
  using type = vertex;
};

template<>
struct vertex_traits<edge>
{
  using type = vertex;
};

template <typename T>
using Vertex = typename vertex_traits<T>::type;

// *******************************************************************
// The edge traits

template<typename>
struct edge_traits;

template<>
struct edge_traits<graph>
{
  using type = edge;
};

template <typename G>
using Edge = typename edge_traits<G>::type;

// *******************************************************************
// The cost traits

template <typename>
struct cost_traits;

template <>
struct cost_traits<edge>
{
  using type = edge::cost_type;
};

template <typename T>
using Cost = typename cost_traits<T>::type;

// *******************************************************************
// The index traits

template <typename>
struct index_traits;

template <>
struct index_traits<vertex>
{
  using type = vertex::index_type;
};

template <typename T>
using Index = typename index_traits<T>::type;

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

Index<vertex>
get_index(const vertex &);

const std::string &
get_name(const vertex &);

const std::vector<edge> &
get_edges(const vertex &);

const graph::vertexes_type &
get_vertexes(const graph &);

graph::size_type
num_vertexes(const graph &);

const vertex &
get_source(const edge &);

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
