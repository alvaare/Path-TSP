#include <iostream>
#include "graph.hpp"
#include "christofides.hpp"
#include "mst.hpp"
#include "linker.hpp"
using namespace std;

int main() {
  LP_solution x = get_solution();
  print_LP_solution(&x);

}
