#include<iostream>
#include"graph.hpp"
#include"matroid_intersection.hpp"
using namespace std;

bool operator<(const d_node& lhs, const d_node& rhs) {
  return tie(lhs.i, lhs.j, lhs.id_k, lhs.color) <
    tie(rhs.i, rhs.j, rhs.id_k, rhs.color);
}

bool operator<(const node& lhs, const node& rhs) {
    return tie(lhs.id, lhs.id_k) < tie(rhs.id, rhs.id_k);
};

bool operator!=(const d_node& lhs, const d_node& rhs) {
  return (lhs<rhs || rhs<lhs);
}

d_node s() {
  return {-1,-1,-1,-1};
}

d_node r() {
  return {-1,-1,-1,0};
}

void print_d_node(d_node e) {
  cout << e.i << " " << e.j << " " << e.id_k << " " << e.color;
}

void print_vector(vector<d_node> v) {
  for (int i=0; i<(int)v.size(); ++i) {
    print_d_node(v[i]);
    cout << "\n";
  }
}

void print_digraph(digraph* DG) {
  for (digraph::iterator it=DG->begin(); it!=DG->end(); ++it) {
    cout << "Les voisins de: ";
    print_d_node(it->first);
    cout << " sont:\n";
    print_vector((it->second));
    cout << "\n";
  }
}

digraph initialize_digraph(graph* G, int k) {
  digraph DG;
  for (int i=0; i<G->n; i++)
    for (int j=0; j<G->n; j++)
      for (int color = 0; color < G->edges[i][j]; color++)
        for (int id_k=0; id_k<k; id_k++)
          DG.insert(d_neighbors({i,j,color,id_k}, {}));
  DG.insert(d_neighbors(s(), {}));
  DG.insert(d_neighbors(r(), {}));
  return DG;
}

bool can_add(d_node e, graphic_m* M) {
  return M->set_of_node[e.i][e.id_k]!=M->set_of_node[e.j][e.id_k];
}


digraph const_digraph(graphic_m* M1, part_m* M2, ind_set* J, graph* G, int k) {
  digraph DG = initialize_digraph(G, k);
  print_digraph(&DG);
  for (digraph::iterator it=DG.begin(); it!=DG.end(); ++it) {
    d_node e = it->first;
    if (e!=s() && e!=r() && J->find(e)==J->end()) {
      if (can_add(e, M1))
        it->second.push_back(s());
    }
  }
  print_digraph(&DG);
  return DG;
}

ind_set max_ind_set(graph* G, int k) {
  int n=G->n;
  ind_set J;
  graphic_m M1(n,k);
  part_m M2(n,k);
  while(true) {
    digraph DG = const_digraph(&M1, &M2, &J, G, k);
    return J;
  }
  return J;
}
