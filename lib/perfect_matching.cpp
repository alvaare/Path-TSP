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
};

struct blossom {
  int root;
  vector<int> right;
  vector<int> left;
  blossom(int v) {
    this->root = v;
  }
  int size(){
    return this->right.size() + this->left.size() -1;
  }
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
    for (int i=0; i<(int)this->left.size(); i++) {
      if (this->left[i] == v)
        return i;
    }
    for (int i=0; i<(int)this->right.size(); i++) {
      if (this->right[i] == v)
        return i;
    }
    return -1;
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
  bool is_in_blossom[n];
  make_is_in_blossom(n, is_in_blossom, B);
  cout << "Les noeuds qui sont dans le blossom sont:\n";
  for (int i=0; i<n; i++) {
    if(is_in_blossom[i]) {
      cout << i << " ";
    }
  }
  cout << "\n";
  int relabel[n];
  do_relabel(n, n2, is_in_blossom, relabel);
  cout << "Voici le relabel: \n";
  for (int i=0; i<n; i++) {
    cout << i << "->" << relabel[i] << "\n";
  }
  for(int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      if (G->edges[i][j] > 0 && relabel[i] != relabel[j])
        G2->edges[relabel[i]][relabel[j]] = G->edges[i][j];
  for(int i=0; i<n; i++)
    if (M->pair[i] != -1 && relabel[i] != relabel[M->pair[i]])
      M2->pair[relabel[i]] = relabel[M->pair[i]];
    else
      M2->pair[relabel[i]] = -1;
  cout << "Voici le nouveau matching:\n";
  for(int i=0; i<n2; i++)
    cout << i << " " << M2->pair[i] << "\n";
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

vector<int> find_path_in_blossom_to_matched_edge(blossom* B, int node,
                                              vector<int> P) {
  int dist_to_root = -1;
  for (int i=0; i<(int)B->left.size(); i++)
    if (B->left[i] = node)
      dist_to_root = i+1;

  if (dist_to_root%2 == 0)
    while (dist_to_root > 0)
      P.push_back(B->left[dist_to_root-1]);
  else if (dist_to_root>0) {
    for (int i=dist_to_root-1; i<(int)B->left.size(); i++)
      P.push_back(B->left[i]);
    for (int i=(int)B->right.size()-1; i>=0; i--)
      P.push_back(B->right[i]);
  }
  else {
    for (int i=0; i<(int)B->right.size();i++)
      if (B->right[i] = node)
        dist_to_root = i+1;

    if (dist_to_root%2 == 0)
      while (dist_to_root > 0)
        P.push_back(B->right[dist_to_root-1]);
    else if (dist_to_root>0) {
      for (int i=dist_to_root-1; i<(int)B->right.size(); i++)
        P.push_back(B->right[i]);
      for (int i=(int)B->left.size()-1; i>=0; i--)
        P.push_back(B->left[i]);
    }
  }
  return P;
}

vector<int> blossom_fin(blossom* B, vector<int> P, int node) {

  return P;
}

vector<int> lifted_path(graph* G, matching* M, blossom* B,
                        graph* G2, matching* M2, vector<int> P2) {
  int n = G->n;
  int n2 = G2->n;
  vector<int> P;
  bool is_in_blossom[n];
  make_is_in_blossom(n, is_in_blossom, B);
  int prelabel[n2-1];
  find_prelabel(n, n2, is_in_blossom, prelabel);
  cout << "Voici le prelabel trouvé\n";
  for (int i=0; i<n2-1; i++){
    cout << i << "->" << prelabel[i] << "\n";
  }
  cout << "Voici P2: ";
  for (int i=0; i<(int)P2.size(); i++) {
    cout << P2[i] << " ";
  }
  cout << "\n";
  int inode = 0;
  while (P2[inode]!=n2-1 && inode < (int)P2.size()) {
    P.push_back(prelabel[P2[inode]]);
    inode++;
  }
  cout << "inode: " << inode << "\n";
  if (inode == (int)P2.size()) {
    cout << "Aucun probleme dans le lift\n";
    return P;
  }
  if (inode == (int)P2.size()-1) {
    cout << "Blossom à la fin\n";
    P = blossom_fin(B, P, P[inode-1]);
    return P;
  }

  int next_node = P2[inode+1];
  if (is_in_blossom[M2->pair[next_node]]) {
    if (inode == 0) {
      P.push_back(B->root);
      cout << next_node << "\n";
      cout << "Blossom au début\n";
    }
    else {
      P = find_path_in_blossom_to_matched_edge(B, P2[inode-1], P);
      cout << "case 1\n";
    }
  }
  else {
    int node = find_blossom_border(B, G, next_node);
    if (B->is_in_left(node)) {
      int i=0;
      while (B->left[i] != node) {
        P.push_back(B->left[i]);
      }
      P.push_back(node);
      cout << "case 2";
    }
    else {
      int i=0;
      while (B->right[i] != node) {
        P.push_back(B->right[i]);
      }
      P.push_back(node);
      cout << "case 3";
    }
  }
  cout << "Blossom lifted\n";
  while(inode < (int)P2.size()) {
    P.push_back(prelabel[P2[inode]]);
    inode++;
  }
  return P;
}

vector<int> find_augmenting_path(graph* G, matching* M) {
  print_graph(*G);
  for(int i=0; i<M->n; i++) {
    cout << M->pair[i] << " ";
  }
  cout << "\n";
  //initialize
  int n = G->n;
  bool visited[n];
  bool used[n][n];
  int k=0;
  //mark matched edges
  for (int i=0; i<n; i++)
    if (M->pair[i]>=0)
      used[i][M->pair[i]]=true;
  //find exposed vertex and add them to forest
  queue<int> nodes_to_visit;
  queue<int> edges_to_visit[n];
  tree* tree_of_node[n];
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
    cout << k << "\n";
    k++;
    int v = nodes_to_visit.front();
    cout << "Voici le noeud qu'on parcourt: " << v << "\n";
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
      cout << "Son voisin: " << w << "\n";
      if (!visited[w]) {
        cout << w << " visité pour la première fois" << "\n";
        int x = M->pair[w];
        cout << "Donc on ajoute " << x << "\n";
        tree_of_node[v]->add_edge(w, x, tree_of_node);
        cout << "Ajout complété\n";
        nodes_to_visit.push(x);
        visited[x] = true;
      }
      else if (tree_of_node[w]->depth%2 == 0) {
        cout << "La profondeur est paire\n";
        if (tree_of_node[w]->root != tree_of_node[v]->root) {
          //There is an augmenting path
          cout << "On a trouvé un chemin!\n";
          cout << "Les ancêtres sont " << tree_of_node[w]->root << " " << tree_of_node[v]->root << "\n";
          return construct_path(G, M, tree_of_node[v], tree_of_node[w]);
        }
        else {
          //contract blossom
          cout << "L'ancêtre commun est " << tree_of_node[w]->root << " " << tree_of_node[v]->root << "\n";
          cout << "On contracte un blossom\n";
          blossom B = form_blossom(G, tree_of_node[v], tree_of_node[w]);
          int new_n = n-B.size()+1;
          graph G2(new_n);
          matching M2(new_n);
          contraction(G,M,&B,&G2,&M2);
          vector<int> P2 = find_augmenting_path(&G2, &M2);
          return lifted_path(G,M,&B,&G2,&M2,P2);//TODO
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
    cout << "La taille de P est " << P.size() << "\n";
    for (int i = 0; i<(int)P.size(); i++) {
      cout << P[i] << " ";
    }
    cout << "\n";
    augment_matching(&M, P);

  }
  while (!P.empty());
  return M;
}
