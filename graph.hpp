#ifndef __GRAPH_HPP_INCLUDED__
#define __GRAPH_HPP_INCLUDED__

#include<queue>

struct graph {
  int n;
  int edges[n][n];
};

bool is_connex(graph);

void print_graph(graph);
