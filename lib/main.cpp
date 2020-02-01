#include <iostream>
#include "graph.hpp"
#include "christofides.hpp"
#include "mst.hpp"
#include "linker.hpp"
#include "find_k.hpp"
using namespace std;

int main() {
  LP_solution x = get_solution();
  print_LP_solution(&x);
  int k = find_k(&x);
  cout << "k: " << k << "\n";
}
