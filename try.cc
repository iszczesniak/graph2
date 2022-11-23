#include <vector>

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
  using edge_type = edge<vertex, int>;
  using vertex_type = vertex<edge<vertex, int>>;
  vertex_type v;
}
