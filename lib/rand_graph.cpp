#include "graph.hpp"
#include "stdlib.h"
#include "time.h"
using namespace std;

int bernouilli() {
  return rand()%2;
}

graph rand_graph(int n, int max_w) {
  graph G(n);
  for (int i=0; i<n; i++) {
    for (int j=0; j<i; j++) {
      int r = rand() % (max_w+1);
      G.edges[i][j] = r;
      G.edges[j][i] = r;
    }
  }
  return G;
}

graph rand_connex_graph(int n, int max_w) {
  graph G = rand_graph(n, max_w);
  while (!is_connex(&G)) {
    G = rand_graph(n, max_w);
  }
  return G;
}
