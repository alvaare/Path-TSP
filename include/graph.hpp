#ifndef __GRAPH_HPP_INCLUDED__
#define __GRAPH_HPP_INCLUDED__

#include<vector>
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
    nodes = new int[n];
  }
};

typedef vector< pair <int, int>> matching;

bool is_connex(graph);

int degree(graph, int);

void print_graph(graph);

#endif
