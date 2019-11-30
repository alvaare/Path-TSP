#include <iostream>
#include "perfect_matching.hpp"
#include "graph.hpp"
#include <vector>
#include <queue>
using namespace std;

struct tree {
  int node;
  int depth;
  tree* parent;
  tree* root;
  vector<tree*> sons;
  tree(int v) {
    this->node = v;
    this->depth = 0;
    this->parent = NULL;
    this->root = NULL;
  }
  void add_edge(int w, int x, tree** tree_of_node) {
    tree Tx(x);
    tree Tw(w);
    Tw.depth = this->depth+1;
    Tx.depth = this->depth+2;
    Tw.parent = this;
    Tx.parent = &Tw;
    this->sons.push_back(&Tw);
    Tw.sons.push_back(&Tx);
    tree_of_node[x] = &Tx;
    tree_of_node[w] = &Tw;
  }
};

typedef vector<tree> forest;

vector<int> construct_path(graph* G, matching* M, tree* Tv, tree* Tw) {
  vector<int> P;
  int size_first_half = Tv->depth+1;
  int first_half_path[size_first_half];
  tree* curr_tree = Tv;
  first_half_path[size_first_half-1]=curr_tree->node;
  for (int i = size_first_half-2; i>=0; i--){
    curr_tree = curr_tree->parent;
    first_half_path[i] = curr_tree->node;
  }
  for (int i=0; i<size_first_half; i++) {
    P.push_back(first_half_path[i]);
  }
  curr_tree = Tw;
  P.push_back(curr_tree->node);
  for (int i=0; i<Tw->depth; i++) {
    curr_tree = curr_tree->parent;
    P.push_back(curr_tree->node);
  }
  return P;

}

vector<int> find_augmenting_path(graph* G, matching* M) {
  //initialize
  int n = G->n;
  bool visited[n];
  bool used[n][n];
  //mark matched edges
  for (int i=0; i<n; i++)
    if (M->pair[i]>=0)
      used[i][M->pair[i]]=true;
  //find exposed vertex and add them to forest
  forest F;
  queue<int> nodes_to_visit;
  queue<int> edges_to_visit[n];
  tree* tree_of_node[n];
  for (int i=0; i<n; i++)
    if (M->pair[i] == -1) {
      visited[i] = true;
      tree Ti = tree(i);
      F.push_back(Ti);
      nodes_to_visit.push(i);
      tree_of_node[i] = &Ti;
      for (int j=0; j<n; j++)
        if (G->edges[i][j]>0)
          edges_to_visit[i].push(j);
  }
  //search augmenting path
  while(!nodes_to_visit.empty()) {
    int v = nodes_to_visit.front();
    nodes_to_visit.pop();
    while(!edges_to_visit[v].empty()) {
      int w = edges_to_visit[v].front();
      edges_to_visit[v].pop();
      if (!visited[w]) {
        int x = M->pair[w];
        tree_of_node[v]->add_edge(w, x, tree_of_node);
      }
      else if (tree_of_node[w]->depth%2 == 0) {
        if (tree_of_node[w]->root != tree_of_node[v]->root) {
          //There is an augmenting path
          return construct_path(G, M, tree_of_node[v], tree_of_node[w]);
        }
      }
    }
  }

}

matching augment_matching(matching* M, vector<int> P) {
  matching AM(M->n);
  return AM;
}

matching perfect_matching(graph G) {
  matching M(G.n);
  vector<int> P;
  do {
    P = find_augmenting_path(&G, &M);
    M = augment_matching(&M, P);
  }
  while (!P.empty());
  return M;
}
