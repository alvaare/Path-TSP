#include <iostream>
#include "mst.hpp"
#include "graph.hpp"
#include "rand_graph.hpp"
#include "perfect_matching.hpp"
#include <vector>
using namespace std;

vector<int> nodes_uncomplete(graph* T, int s, int t) {
  vector<int> nodes;
  int n = T->n;
  for (int i=0; i<n; i++) {
    if (i==s || i==t) {
      if (degree(T, i)%2 == 0) {
        nodes.push_back(s);
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

graph union_tree_matching(graph* T, matching* M) {
  int n=T->n;
  graph G(n);
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      if (T->edges[i][j]>0 || M->pair[i]==j)
        G.edges[i][j] = 1;
  return G;
}

path christofides(graph* G, graph* T, int s, int t) {
  int n = G->n;
  path P(n);

  vector<int> O = nodes_uncomplete(T, s, t);
  for (int i=0; i<(int)O.size(); i++) {
    cout << O[i] << " ";
  }
  cout << "\n";
  graph S = induced_subgraph(G, O);
  print_graph(&S);
  matching M = perfect_matching(S);
  print_matching(&M);
  graph E = union_tree_matching(T, &M);
  print_graph(&E);

  return P;
};
