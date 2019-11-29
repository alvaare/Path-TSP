#ifndef __GRAPH_HPP_INCLUDED__
#define __GRAPH_HPP_INCLUDED__

#include<queue>
using namespace std;

struct graph {
  int n;
  int** edges;
  graph(int n) {
    this->n = n;
    edges = new int*[n];
    for (int i = 0; i < n; i++) {
      edges[i] = new int[n];
      for (int j = 0; j < n; j++)
        edges[i][j] = 0;
    }
  }
};

struct path {
  int n;
  int* nodes;
  path(int n) {
    this->n = n;
    nodes = new int*[n];
  }
}

bool is_connex(graph);

void print_graph(graph);

#endif
