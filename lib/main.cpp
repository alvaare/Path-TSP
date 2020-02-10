#include <iostream>
#include "graph.hpp"
#include "christofides.hpp"
#include "mst.hpp"
#include "linker.hpp"
#include "find_k.hpp"
#include "matroid_intersection.hpp"
using namespace std;

int main() {
  LP_solution x = get_solution();
  print_LP_solution(&x);
  int k = find_k(&x);
  cout << "k: " << k << "\n";
  graph G = from_LP_solution_to_graph(&x, k);
  print_graph(&G);
  ind_set A = max_ind_set(&G, k);
}
