#include <iostream>
#include "rand_graph.hpp"
#include "graph.hpp"
#include "christofides.hpp"
#include "perfect_matching.hpp"
#include "mst.hpp"
using namespace std;

int main() {
  srand(time(NULL));
  int n = 157;
  graph G = rand_graph(n);
  print_graph(G);/*
  graph T = primMST(G);
  print_graph(T);*/

  //christofides(G, T, 0, 1);
/*
  graph G(6);
  G.edges[0][2] = 1;
  G.edges[0][3] = 1;
  G.edges[1][3] = 1;
  G.edges[1][4] = 1;
  G.edges[1][5] = 1;
  G.edges[2][0] = 1;
  G.edges[2][4] = 1;
  G.edges[2][5] = 1;
  G.edges[3][0] = 1;
  G.edges[3][1] = 1;
  G.edges[3][4] = 1;
  G.edges[3][5] = 1;
  G.edges[4][1] = 1;
  G.edges[4][2] = 1;
  G.edges[4][3] = 1;
  G.edges[4][5] = 1;
  G.edges[5][1] = 1;
  G.edges[5][2] = 1;
  G.edges[5][3] = 1;
  G.edges[5][4] = 1;*/
  /*graph G(12);
  int A[12][12]={{0,0,1,0,1,1,1,0,0,1,1,1},
          {0,0,0,1,1,0,1,1,1,0,0,1},
          {1,0,0,0,0,0,1,1,1,1,0,1},
          {0,1,0,0,1,1,0,0,0,0,0,1},
          {1,1,0,1,0,1,1,1,1,1,0,1},
          {1,0,0,1,1,0,1,0,1,0,1,0},
          {1,1,1,0,1,1,0,0,0,0,1,0},
          {0,1,1,0,1,0,0,0,0,1,0,0},
          {0,1,1,0,1,1,0,0,0,1,0,1},
          {1,0,1,0,1,0,0,1,1,0,0,0},
          {1,0,0,0,0,1,1,0,0,0,0,0},
          {1,1,1,1,1,0,0,0,1,0,0,0}};
  for (int i=0; i<12; i++)
    for (int j=0; j<12; j++)
      G.edges[i][j] = A[i][j];*/
  matching M = perfect_matching(G);
  for (int i=0; i<n; i++) {
    cout << i << "->" << M.pair[i] << "\n";
  }
}
