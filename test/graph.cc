#include "graph.hpp"
#include "units.hpp"

#include <cassert>
#include <iostream>

using namespace std;

int
main()
{
  // (0)-------------[2, (0, 3)]-------------(2)---[2, (1, 5)]---(3)
  //  \                                       /
  //   \---[2, (1, 5)]---(1)---[2, (1, 5)]---/

  graph<vertex<edge<int, SU>>> g(4);
  auto &v0 = add_vertex(g, "v0");
  auto &v1 = add_vertex(g, "v1");
  auto &v2 = add_vertex(g, "v2");
  auto &v3 = add_vertex(g, "v3");

  assert(get_index(v0) == 0);
  assert(get_index(v1) == 1);
  assert(get_index(v2) == 2);
  assert(get_index(v3) == 3);

  // Test the index traits.
  Index<vertex<edge<int, SU>>> i0 = get_index(v0);

  add_edge(v0, v1, 1, {CU(1, 5)}); // e0
  add_edge(v0, v2, 2, {CU(0, 3)}); // e1
  add_edge(v1, v2, 3, {CU(1, 5)}); // e2
  add_edge(v2, v3, 4, {CU(1, 5)}); // e3

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
      cout << get_name(v) << ":\n";
      for(const auto &e: get_edges(v))
        cout << "\t" << get_name(get_target(e)) << ", "
             << get_weight(e) << ", " << get_resources(e) << '\n';
    }
}
