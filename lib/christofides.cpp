#include <iostream>
#include "mst.hpp"
#include "graph.hpp"
#include "rand_graph.hpp"
#include "perfect_matching.hpp"
#include <vector>
using namespace std;

vector<int> nodes_uncomplete(graph T, int s, int t) {
  vector<int> nodes;
  int n = T.n;
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

graph induced_subgraph(graph G, vector<int> O) {
  int n = (int)O.size();
  graph S(n);

  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      S.edges[i][j] = G.edges[O[i]][O[j]];
    }
  }
  return S;
}

path christofides(graph G, graph T, int s, int t) {
  int n = G.n;
  path P(n);

  vector<int> O = nodes_uncomplete(T, s, t);
  for (int i=0; i<(int)O.size(); i++) {
    cout << O[i] << " ";
  }
  cout << "\n";
  graph S = induced_subgraph(G, O);
  print_graph(S);
  matching M = perfect_matching(S);
  for (int i=0; i<S.n; i++) {
    cout << i << M.pair[i] << "\n";
  }

  return P;
};
