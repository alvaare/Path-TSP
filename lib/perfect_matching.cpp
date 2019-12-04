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
  int root;
  vector<tree*> sons;
  tree(int v) {
    this->node = v;
    this->depth = 0;
    this->parent = NULL;
    this->root = v;
  }
  void add_edge(int w, int x, tree** tree_of_node) {
    tree* Tx = new tree(x);
    tree* Tw = new tree(w);
    Tw->depth = this->depth+1;
    Tx->depth = this->depth+2;
    Tw->parent = this;
    Tx->parent = Tw;
    this->sons.push_back(Tw);
    Tw->sons.push_back(Tx);
    Tx->root = this->root;
    Tw->root = this->root;
    tree_of_node[x] = Tx;
    tree_of_node[w] = Tw;
  }
  void print_tree() {
    cout << "node: " << this->node << "\n";
    cout << "depth: " << this->depth << "\n";
    if (this->parent != NULL)
    cout << "parent: " << this->parent->node << "\n";
    cout << "racine: " << this->root << "\n";
    cout << "fils: ";
    for (int i=0; i<(int)this->sons.size(); i++)
      cout << this->sons[i]->node << " ";
    cout << "\n";
  }
};

struct blossom {
  int root;
  vector<int> right;
  vector<int> left;
  blossom(int v) {
    this->root = v;
  }
  void print_blossom() {
    cout << "root: " << this->root << "\n";
    cout << "left: ";
    for (int i=0; i<(int)this->left.size(); i++)
      cout << this->left[i] << " ";
    cout << "\n";
    cout << "right: ";
    for (int i=0; i<(int)this->right.size(); i++)
      cout << this->right[i] << " ";
    cout << "\n";
  }
  int size() {
    return this->right.size() + this->left.size() -1; }
  bool is_in_left(int v) {
    for (int i=0; i<(int)this->left.size(); i++)
      if (this->left[i] == v)
        return true;
    return false;
  }
  bool is_in_right(int v) {
    for (int i=0; i<(int)this->right.size(); i++)
      if (this->right[i] == v)
        return true;
    return false;
  }
  int dist_to_root(int v) {
    for (int i=0; i<(int)this->left.size(); i++)
      if (this->left[i] == v)
        return i;
    for (int i=0; i<(int)this->right.size(); i++)
      if (this->right[i] == v)
        return i;
    return -1;
  }
  vector<int> path_to_root_clockwise(int v) {
    vector<int> P;
    if (this->is_in_right(v)) {
      int d = this->dist_to_root(v);
      for (int i=d; i>=0; i--)
        P.push_back(this->right[i]);
      return P;
    }
    if (this->is_in_left(v)) {
      int d = this->dist_to_root(v);
      for (int i=d; i<(int)this->left.size(); i++)
        P.push_back(this->left[i]);
      for (int i=(int)this->right.size()-1; i>=0; i--)
        P.push_back(this->right[i]);
      return P;
    }
    else {
      cout << "Ce noeud n'est pas dans le blossom";
      return P;
    }
  }
  vector<int> path_to_root_anticlockwise(int v) {
    vector<int> P;
    if (this->is_in_left(v)) {
      int d = this->dist_to_root(v);
      for (int i=d; i>=0; i--)
        P.push_back(this->left[i]);
      return P;
    }
    else {
      int d = this->dist_to_root(v);
      for (int i=d; i<(int)this->right.size(); i++)
        P.push_back(this->right[i]);
      for (int i=(int)this->left.size()-1; i>=0; i--)
        P.push_back(this->left[i]);
      return P;
    }
  }
  vector<int> augmenting_path_to_root(int v) {
    if ((this->is_in_left(v) && this->dist_to_root(v)%2==0) ||
        (this->is_in_right(v) && this->dist_to_root(v)%2==1))
      return this->path_to_root_anticlockwise(v);
    else
      return this->path_to_root_clockwise(v);
  }
  vector<int> path_from_root_clockwise(int v) {
    vector<int> P;
    for (int i=0; i<(int)this->left.size(); i++) {
      P.push_back(this->left[i]);
      if (this->left[i] == v)
        return P;
    }
    for (int i=this->right.size()-1; i>=0; i--) {
      P.push_back(this->right[i]);
      if (this->right[i]==v)
        return P;
    }
    return P;
  }
  vector<int> path_from_root_anticlockwise(int v) {
    vector<int> P;
    for (int i=0; i<(int)this->right.size(); i++) {
      P.push_back(this->right[i]);
      if (this->right[i] == v)
        return P;
    }
    for (int i=this->left.size()-1; i>=0; i--) {
      P.push_back(this->left[i]);
      if (this->left[i]==v)
        return P;
    }
    return P;
  }
  vector<int> augmenting_path_from_root(int v) {
    if ((this->is_in_left(v) && this->dist_to_root(v)%2==0) ||
        (this->is_in_right(v) && this->dist_to_root(v)%2==1))
      return this->path_from_root_clockwise(v);
    else
      return this->path_from_root_anticlockwise(v);
  }
};

vector<int> path_to_root(tree* T) {
  vector<int> path;
  int path_size = T->depth+1;
  int path_array[path_size];
  tree* curr_tree = T;
  path_array[path_size-1]=curr_tree->node;
  for (int i = path_size-2; i>=0; i--){
    curr_tree = curr_tree->parent;
    path_array[i] = curr_tree->node;
  }
  for (int i=0; i<path_size; i++)
    path.push_back(path_array[i]);
  return path;
}

vector<int> construct_path(graph* G, matching* M, tree* Tv, tree* Tw) {
  vector<int> P = path_to_root(Tv);
  tree* curr_tree = Tw;
  P.push_back(curr_tree->node);
  for (int i=0; i<Tw->depth; i++) {
    curr_tree = curr_tree->parent;
    P.push_back(curr_tree->node);
  }
  return P;

}

blossom form_blossom(graph* G, tree* Tv, tree* Tw) {
  blossom B(Tv->root);
  B.right = path_to_root(Tv);
  B.left = path_to_root(Tw);
  return B;
}

void make_is_in_blossom(int n, bool* res, blossom* B) {
  for (int i=0; i<(int)B->right.size(); i++)
    res[B->right[i]]=true;
  for (int i=0; i<(int)B->left.size(); i++)
    res[B->left[i]]=true;
}

void do_relabel(int n, int n2, bool* is_in_blossom, int* relabel) {
  int blossom_encountered = 0;
  for (int i=0; i<n; i++) {
    if (is_in_blossom[i]) {
      relabel[i] = n2-1;
      blossom_encountered++;
    }
    else
      relabel[i] = i-blossom_encountered;
  }
}

void find_prelabel(int n, int n2, bool* is_in_blossom, int* prelabel) {
  int blossom_encountered = 0;
  for (int i=0; i<n; i++) {
    if (!is_in_blossom[i])
      prelabel[i-blossom_encountered] = i;
    else
      blossom_encountered++;
  }
}

void contraction(graph* G, matching* M, blossom* B, graph* G2, matching* M2) {
  int n = G->n;
  int n2 = G2->n;
  bool is_in_blossom[n] = {false};
  make_is_in_blossom(n, is_in_blossom, B);
  int relabel[n];
  do_relabel(n, n2, is_in_blossom, relabel);
  for(int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      if (G->edges[i][j] > 0 && relabel[i] != relabel[j])
        G2->edges[relabel[i]][relabel[j]] = G->edges[i][j];
  for(int i=0; i<n; i++)
    if (M->pair[i] != -1 && relabel[i] != relabel[M->pair[i]])
      M2->pair[relabel[i]] = relabel[M->pair[i]];
    else
      M2->pair[relabel[i]] = -1;
}

int find_blossom_border(blossom* B, graph* G, int node) {
  for (int i=0; i<(int)B->left.size(); i++)
    if (G->edges[B->left[i]][node] > 0)
      return B->left[i];
  for (int i=0; i<(int)B->right.size(); i++)
    if (G->edges[B->right[i]][node] > 0)
      return B->right[i];
  cout << "Couldn't find blossom border\n";
  return -1;
}

vector<int> lifted_path(graph* G, matching* M, blossom* B,
                        graph* G2, matching* M2, vector<int> P2) {
  if (P2.size() == 0)
    return vector<int> ();
  int n = G->n;
  int n2 = G2->n;
  vector<int> P;
  bool is_in_blossom[n] = {false};
  make_is_in_blossom(n, is_in_blossom, B);
  int prelabel[n2-1];
  find_prelabel(n, n2, is_in_blossom, prelabel);
  int inode = 0;
  while (P2[inode]!=n2-1
    &&
    inode < (int)P2.size()) {
    P.push_back(prelabel[P2[inode]]);
    inode++;
  }
  if (inode == (int)P2.size()) {
    return P;
  }
  if (inode == (int)P2.size()-1) {
    int border = find_blossom_border(B,G,prelabel[P2[inode-1]]);
    vector<int> P_suite = B->augmenting_path_to_root(border);
    for (int i=0; i<(int)P_suite.size(); i++)
      P.push_back(P_suite[i]);
    return P;
  }
  if (inode == 0) {
    int border = find_blossom_border(B, G, prelabel[P2[1]]);
    P = B->augmenting_path_from_root(border);
    for (int i=1; i<(int)P2.size(); i++)
      P.push_back(prelabel[P2[i]]);
    return P;
  }

  int border = find_blossom_border(B, G, prelabel[P2[inode+1]]);
  vector<int> P_in_blossom;
  if (inode%2==0) {
      P_in_blossom = B->augmenting_path_from_root(border);
  }
  else {
    P_in_blossom = B->augmenting_path_to_root(border);
  }
  for (int i=0; i<(int)P_in_blossom.size(); i++) {
    P.push_back(P_in_blossom[i]);
  }
  inode++;
  while(inode < (int)P2.size()) {
    P.push_back(prelabel[P2[inode]]);
    inode++;
  }
  return P;
}

void print_forest(int n, tree** tree_of_node) {
  for (int i=0; i<n; i++) {
    if (tree_of_node[i] != NULL) {
    cout << "Voici l'arbre du noeud: " << i << " :\n";
    tree_of_node[i]->print_tree();
  }
  }
}

bool incorrect_matching(matching* M) {
  int A[M->n] = {0};
  for (int i=0; i<M->n; i++)
    if (M->pair[i]!=-1)
      A[M->pair[i]]++;
  for (int i=0; i<M->n; i++)
    if (A[i]>1)
      return true;
  return false;
}


vector<int> find_augmenting_path(graph* G, matching* M) {
  //initialize
  int n = G->n;
  bool visited[n] = {false};
  bool used[n][n];
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      used[i][j] = false;
  //mark matched edges
  for (int i=0; i<n; i++)
    if (M->pair[i]>=0)
      used[i][M->pair[i]]=true;
  //find exposed vertex and add them to forest
  queue<int> nodes_to_visit;
  queue<int> edges_to_visit[n];
  tree* tree_of_node[n] = {NULL};
  for (int i=0; i<n; i++)
    if (M->pair[i] == -1) {
      visited[i] = true;
      tree* Ti = new tree(i);
      nodes_to_visit.push(i);
      tree_of_node[i] = Ti;
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
      while(used[v][w] && !edges_to_visit[v].empty()) {
        w = edges_to_visit[v].front();
        edges_to_visit[v].pop();
      }
      if (used[v][w])
        break;
      if (!visited[w]) {
        int x = M->pair[w];
        tree_of_node[v]->add_edge(w, x, tree_of_node);
        nodes_to_visit.push(x);
        visited[x] = true;
      }
      else if (tree_of_node[w]->depth%2 == 0) {
        if (tree_of_node[w]->root != tree_of_node[v]->root) {
          //There is an augmenting path
          return construct_path(G, M, tree_of_node[v], tree_of_node[w]);
        }
        else {
          //contract blossom
          blossom B = form_blossom(G, tree_of_node[v], tree_of_node[w]);
          int new_n = n-B.size()+1;
          graph G2(new_n);
          matching M2(new_n);
          contraction(G,M,&B,&G2,&M2);
          vector<int> P2 = find_augmenting_path(&G2, &M2);
          return lifted_path(G,M,&B,&G2,&M2,P2);
        }
      }
      used[v][w] = true;
      used[w][v] = true;
    }
    visited[v] = true;
  }
  return vector<int> ();
}

void augment_matching(matching* M, vector<int> P) {
  for (int i=0; i<(int)P.size()-1; i+=2) {
    M->pair[P[i]] = P[i+1];
    M->pair[P[i+1]] = P[i];
  }
}

matching perfect_matching(graph G) {
  matching M(G.n);
  vector<int> P;
  do {
    P = find_augmenting_path(&G, &M);
    augment_matching(&M, P);

  }
  while (!P.empty());
  return M;
}
