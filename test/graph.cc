#include "graph.hpp"

#include <cassert>
#include <iostream>

using namespace std;

int
main()
{
  // (0)-------------[2, (0, 3)]-------------(2)---[2, (1, 5)]---(3)
  //  \                                       /
  //   \---[2, (1, 5)]---(1)---[2, (1, 5)]---/

  graph<vertex<edge<int>>> g(4);
  auto &v0 = add_vertex(g, "v0");
  auto &v1 = add_vertex(g, "v1");
  auto &v2 = add_vertex(g, "v2");
  auto &v3 = add_vertex(g, "v3");

  add_edge(v0, v1, 2, {CU(1, 5)});
  add_edge(v0, v2, 2, {CU(0, 3)});
  add_edge(v1, v2, 2, {CU(1, 5)});
  add_edge(v2, v3, 2, {CU(1, 5)});

  for(const auto &v: get_vertexes(g))
    {
      cout << get_name(v) << ":\n";
      for(const auto &e: get_edges(v))
        cout << "\t" << get_name(get_target(e)) << ", "
             << get_weight(e) << ", " << get_units(e) << '\n';
    }
}
