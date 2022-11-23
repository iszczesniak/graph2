#include <vector>

template <typename Edge>
struct vertex
{
  std::vector<Edge> m_t;
};

template <typename Vertex>
struct edge
{
  const Vertex &m_a;
};

int
main()
{
  using edge_type = edge<vertex>;
  using vertex_type = vertex<edge<vertex>>;
  vertex_type v;
}
