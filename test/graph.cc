#include "graph.hpp"
#include "props.hpp"
#include "units.hpp"

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

// The vertex type with the key and the name properties.  It's a
// temporary vertex type, because it still need the edge type.
template <typename Edge>
using vertex_type_tmp = vertex<Edge, key<unsigned>, name<string>>;

// The edge type with the weight and the resources properties.  We
// break the dependency between the vertex and the edge type by
// passing to the edge type the vertex_type_tmp template.
using edge_type = edge<vertex_type_tmp, weight<unsigned>, resources<SU>>;

// Now we know the edge type, so we can instantiate the vertex type.
using vertex_type = vertex_type_tmp<edge_type>;

// Here's the graph type.
using graph_type = graph<vertex_type>;

int
main()
{
  // (0)-------------[2, (0, 3)]-------------(2)---[2, (1, 5)]---(3)
  //  \                                       /
  //   \---[2, (1, 5)]---(1)---[2, (1, 5)]---/

  graph_type g(4);

  auto &v0 = add_vertex(g, "v0");
  auto &v1 = add_vertex(g, "v1");
  auto &v2 = add_vertex(g, "v2");
  auto &v3 = add_vertex(g, "v3");

  assert(get_key(v0) == 0);
  assert(get_key(v1) == 1);
  assert(get_key(v2) == 2);
  assert(get_key(v3) == 3);

  // Test the key traits.
  auto i0 = get_key(v0);

  add_edge(v0, v1, 1, SU{CU(1, 5)}); // e0
  add_edge(v0, v2, 2, SU{CU(0, 3)}); // e1
  add_edge(v1, v2, 3, SU{CU(1, 5)}); // e2
  add_edge(v2, v3, 4, SU{CU(1, 5)}); // e3

  // Make sure we are using the same vertex objects.
  auto v0i = get_edges(v0).begin();

  // Edge e0.
  auto &e0 = *v0i;
  assert(get_source(e0) == v0);
  assert(get_target(e0) == v1);
  assert(get_weight(e0) == 1);
  assert(get_resources(e0) == SU{CU(1, 5)});

  // Edge e1.
  ++v0i;
  auto &e1 = *v0i;
  assert(get_source(e1) == v0);
  assert(get_target(e1) == v2);
  assert(get_weight(e1) == 2);
  assert(get_resources(e1) == SU{CU(0, 3)});
  
  for(const auto &v: get_vertexes(g))
    {
      cout << v << ":\n";
      for(const auto &e: get_edges(v))
        cout << "\t" << e << '\n';
    }
}
