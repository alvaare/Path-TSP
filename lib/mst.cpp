#include<climits>
#include "graph.hpp"
using namespace std;

int next_node(int n, int dist[], bool visited[]){
  int min_dist = INT_MAX;
  int imin;

  for (int i=0; i<n; i++) {
    if (!visited[i] && dist[i] < min_dist) {
      min_dist = dist[i];
      imin = i;
    }
  }
  return imin;
}

graph primMST(graph* G) {
  int n = G->n;
  graph T(n);
  int parent[n];
  int dist[n];
  bool visited[n];

  for (int i=0; i<n; i++) {
    dist[i] = INT_MAX;
    visited[i] = false;
  }

  dist[0] = 0;
  parent[0] = -1;

  for (int i=0; i<n; i++) {
    int v = next_node(n, dist, visited);
    visited[v] = true;
    int p = parent[v];
    if (p>=0) {
      T.edges[v][p] = 1;
      T.edges[p][v] = 1;
    }
    for (int l=0; l<n; l++){
      if (!visited[l] && G->edges[v][l]>0 && G->edges[v][l]<dist[l]) {
        parent[l] = v;
        dist[l] = G->edges[v][l];
      }
    }
  }

  return T;
}
