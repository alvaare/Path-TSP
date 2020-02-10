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

d_node s() {
  return {-1,-1,-1,-1};
}

d_node r() {
  return {-1,-1,-1,0};
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

digraph construct_digraph(graphic_m* M1, partition_m* M2, ind_set* J, graph* G,
  int k) {
  digraph DG = initialize_digraph(G, k);

  return DG;
}

ind_set max_ind_set(graph* G, int k) {
  int n=G->n;
  ind_set J;
  graphic_m M1(n,k);
  partition_m M2(n,k);
  while(true) {
    digraph DG = construct_digraph(&M1, &M2, &J, G, k);
    return J;
  }
  return J;
}
