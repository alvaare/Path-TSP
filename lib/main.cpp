#include <iostream>
#include "rand_graph.hpp"
#include "graph.hpp"
#include "christofides.hpp"
#include "perfect_matching.hpp"
#include "mst.hpp"
using namespace std;

int main() {
  srand(time(NULL));
  int n = 7;
  graph G = rand_connex_graph(n);
  print_graph(G);/*
  graph T = primMST(G);
  print_graph(T);*/

  //christofides(G, T, 0, 1);
  /*graph G2 = rand_connex_graph(n);
  matching M2 = perfect_matching(G2);
  for (int i=0; i<6; i++) {
    cout << i << M2.pair[i] << "\n";
  }*/
  /*graph G(6);
  G.edges[0][1] = 1;
  G.edges[0][2] = 1;
  G.edges[0][3] = 1;
  G.edges[0][4] = 1;
  G.edges[0][5] = 1;
  G.edges[1][0] = 1;
  G.edges[1][2] = 1;
  G.edges[1][3] = 1;
  G.edges[1][4] = 1;
  G.edges[2][0] = 1;
  G.edges[2][1] = 1;
  G.edges[3][0] = 1;
  G.edges[3][1] = 1;
  G.edges[4][0] = 1;
  G.edges[4][1] = 1;
  G.edges[4][5] = 1;
  G.edges[5][0] = 1;
  G.edges[5][4] = 1;*/
  matching M = perfect_matching(G);
  for (int i=0; i<n; i++) {
    cout << i << M.pair[i] << "\n";
  }
}
