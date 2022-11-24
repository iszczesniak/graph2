#include <vector>

// This is an example of the circular dependency between two templated
// types:
//
// * vertex needs to know the type of the edges to store,
//
// * edge needs to know the type of the vertex is has a reference to.

template <typename Edge>
struct vertex
{
  std::vector<Edge> m_t;
};

template <typename Vertex, typename T>
struct edge
{
  Vertex &m_a;
  T m_t;
};

int
main()
{
  // Cannot create the type of the edge, because I need the type of
  // the vertex:
  //
  // edge<vertex<edge<vertex<edge<....

  // Neither can I create the type of the vertex:
  //
  // vertex<edge<vertex<edge<vertex<....
}
