#include <iostream>
#include "rand_graph.hpp"
#include "graph.hpp"
#include "christofides.hpp"
#include "mst.hpp"
using namespace std;

int main() {
  srand(time(NULL));

  graph G = rand_connex_graph(7);
  print_graph(G);
  graph T = primMST(G);
  print_graph(T);

  christofides(G, T, 0, 1);

}
