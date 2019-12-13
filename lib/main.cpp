#include <iostream>
#include "rand_graph.hpp"
#include "graph.hpp"
#include "christofides.hpp"
#include "perfect_matching.hpp"
#include "mst.hpp"
using namespace std;

int main() {
  srand(time(NULL));
  int n = 8;
  graph G = rand_graph(n);
  //print_graph(&G);
  graph C = complete_graph(&G);
  //print_graph(&C);
  graph T = primMST(&C);
  //print_graph(&T);

  christofides(&C, &T, 0, 1);

}
