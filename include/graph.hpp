#ifndef __GRAPH_HPP_INCLUDED__
#define __GRAPH_HPP_INCLUDED__

using namespace std;

struct graph {
  int n;
  int** edges;
  graph(int n) {
    this->n = n;
    this->edges = new int*[n];
    for (int i = 0; i < n; i++) {
      this->edges[i] = new int[n];
      for (int j = 0; j < n; j++)
        this->edges[i][j] = 0;
    }
  }
  ~graph() {
    for (int i=0; i<n; i++)
      delete [] this->edges[i];
    delete [] this->edges;
  }
};

struct path {
  int n;
  int* nodes;
  path(int n) {
    this->n = n;
    nodes = new int[n];
  }
  ~path() {
    delete [] nodes;
  }
};

struct matching {
  int n;
  int* pair;
  matching(int n) {
    this->n = n;
    pair = new int[n];
    for (int i=0; i<n; i++) {
      this->pair[i] = -1;
    }
  }
  ~matching() {
    delete [] pair;
  }
};

bool is_connex(graph*);

int degree(graph*, int);

void print_graph(graph*);

void print_matching(matching*);

graph complete_graph(graph*);

#endif
