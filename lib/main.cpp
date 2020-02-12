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
  //vector<graph> LT =
}
