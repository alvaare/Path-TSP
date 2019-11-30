#include <iostream>
#include "perfect_matching.hpp"
#include "graph.hpp"
#include <vector>
#include <queue>
using namespace std;

struct tree {
  int root;
  int depth;
  int parent;
  vector<tree> sons;
  tree(int v) {
    this->root = v;
    this->depth = 0;
    this->parent = -1;
  }
};

typedef vector<tree> forest;

vector<int> find_augmenting_path(graph G, matching M) {
  //initialize
  int n = G.n;
  vector<int> P;
  bool visited[n];
  bool used[n][n];
  //mark matched edges
  for (int i=0; i<n; i++) {
    if (M.pair[i]>=0) {
      used[i][M.pair[i]]=true;
    }
  }
  //find exposed vertex and add them to forest
  forest F;
  queue<int> nodes_to_visit;
  for (int i=0; i<n; i++) {
    if (M.pair[i] == -1) {
      F.push_back(tree(i));
      nodes_to_visit.push(i);
    }
  }

  return P;
}

matching augment_matching(matching M, vector<int> P) {
  matching AM(M.n);
  return AM;
}

matching perfect_matching(graph G) {
  matching M(G.n);
  vector<int> P;
  do {
    P = find_augmenting_path(G, M);
    M = augment_matching(M, P);
  }
  while (!P.empty());
  return M;
}
