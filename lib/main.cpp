#include <iostream>
#include <vector>
#include "graph.hpp"
#include "christofides.hpp"
#include "mst.hpp"
#include "linker.hpp"
#include "find_k.hpp"
#include "matroid_intersection.hpp"
#include "rand_graph.hpp"
using namespace std;

int main() {
  //srand(time(NULL));
  int n;
  cout << "Enter n: ";
  cin >> n;
  int max_w;
  cout << "Enter max_weight: ";
  cin >> max_w;
  int s = 0;
  int t = n-1;

  graph G = rand_connex_graph(n, max_w);
  print_graph(&G);
  LP_solution x = get_solution(&G, s, t);
  print_LP_solution(&x);
  int k = find_k(&x);
  cout << "k: " << k << "\n";
  graph integer_solution = from_LP_solution_to_graph(&x, k);
  print_graph(&integer_solution);
  ind_set A = max_ind_set(&integer_solution, k);
  print_ind_set(&A);
  tree_list LT = tree_list_from_ind_set(&G, &A, k);

  cout << "LP solution cost: " << LP_solution_cost(&x, &G) << "\n";
  cout << "Christofides costs:\n";
  for (int i=0; i<k; i++) {
    graph* T = LT.content[i];
    print_graph(T);
    path P = christofides(&G, T, s, t);
    print_path(&P);
    cout << path_cost(&P, &G) << "\n";
  }
}
