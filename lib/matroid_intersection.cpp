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


digraph construct_digraph(graphic_m* M1, partition_m* M2,
                          ind_set* J, graph* G) {
  digraph DG;

  return DG;
}

ind_set max_ind_set(graph* G, int k) {
  int n=G->n;
  ind_set J;
  graphic_m M1(n,k);
  partition_m M2(n,k);
  while(true) {
    digraph DG = construct_digraph(&M1, &M2, &J, G);
    return J;
  }
  return J;
}
