#include <iostream>
#include "mst.hpp"
#include "graph.hpp"
#include "rand_graph.hpp"
#include "mw_perfect_matching.hpp"
#include "euler_circuit.hpp"
#include <vector>
using namespace std;

vector<int> nodes_uncomplete(graph* T, int s, int t) {
  vector<int> nodes;
  int n = T->n;
  for (int i=0; i<n; i++) {
    if (i==s || i==t) {
      if (degree(T, i)%2 == 0) {
        nodes.push_back(i);
      }
    }
    else if (degree(T,i)%2 == 1) {
      nodes.push_back(i);
    }
  }
  return nodes;
}

graph induced_subgraph(graph* G, vector<int> O) {
  int n = (int)O.size();
  graph S(n);

  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      S.edges[i][j] = G->edges[O[i]][O[j]];
    }
  }
  return S;
}

graph union_tree_matching(graph* T, matching* M, vector<int> O) {
  int n=T->n;
  graph G(n);
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      if (T->edges[i][j]>0)
        G.edges[i][j]++;
  for (int i=0; i<M->n; i++)
    if (M->pair[i]!=-1)
      G.edges[O[i]][O[M->pair[i]]]++;
  return G;
}

path christofides(graph* G, graph* T, int s, int t) {
  int n = G->n;
  vector<int> O = nodes_uncomplete(T, s, t);
  graph S = induced_subgraph(G, O);
  matching M = mw_perfect_matching(&S);
  graph E = union_tree_matching(T, &M, O);
  circuit C = euler_circuit(&E, s, t);
  path P = clean_circuit(&C, n, t);
  return P;
};
