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

  auto &e0 = add_edge(v0, v1, 2, {CU(1, 5)});
  auto &e1 = add_edge(v0, v2, 2, {CU(0, 3)});
  auto &e2 = add_edge(v1, v2, 2, {CU(1, 5)});
  auto &e3 = add_edge(v2, v3, 2, {CU(1, 5)});

  cout << "&v0 = " << &v0 << endl;
  cout << "&get_source(e0) = " << &get_source(e0) << endl;

  // Make sure we are using the same vertex objects.
  assert(&get_source(e0) == &v0);
  assert(&get_target(e1) == &v1);
  
  for(const auto &v: get_vertexes(g))
    {
      cout << get_name(v) << ":\n";
      for(const auto &e: get_edges(v))
        cout << "\t" << get_name(get_target(e)) << ", "
             << get_weight(e) << ", " << get_resources(e) << '\n';
    }
}
