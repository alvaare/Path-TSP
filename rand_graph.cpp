#include "graph.hpp"
#include <stdlib.h>
#include <time.h>
using namespace std;

int bernouilli() {
  srand(time(NULL));
  return rand()%2;
}

graph rand_graph(int n) {
  graph G;
  G.n = n;
  while (!is_connex(G)) {
    for (int i=0; i<n; i++) {
      for (int j=0; j<i; j++) {
        int r = bernouilli();
        G.edges[i][j] = r;
        G.edges[j][i] = r;
      }
    }
  }
  return G;
}
