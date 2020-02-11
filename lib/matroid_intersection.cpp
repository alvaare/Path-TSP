#include<iostream>
#include<algorithm>
#include<queue>
#include<unordered_set>
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

set<node> union_set(set<node>* s1, set<node>* s2) {
  set<node> s;
  set_union(s1->begin(),s1->end(),s2->begin(),s2->end(),inserter(s,s.begin()));
  return s;
}

bool can_add(d_node e, graphic_m* M) {
  return M->set_of_node[e.i][e.id_k]!=M->set_of_node[e.j][e.id_k];
}

bool can_add(d_node e, part_m* M) {
  return !M->used[e.i][e.j][e.color];
}

void add_graphic_m(d_node e, graphic_m* M) {
  set<node>* s1 = M->set_of_node[e.i][e.id_k];
  set<node>* s2 = M->set_of_node[e.j][e.id_k];
  set<node>* s = new set<node>;
  *s = union_set(s1, s2);
  delete s1;
  delete s2;
  for(set<node>::iterator it=s->begin(); it!=s->end(); it++)
    M->set_of_node[it->id][it->id_k] = s;
}

void add_part_m(d_node e, part_m* M) {
  M->used[e.i][e.j][e.color] = true;
}

typedef map<int,vector<int>> s_graph;

s_graph const_adj_list(d_node e, ind_set* J, set<node>* s) {
  s_graph adj_list;
  for(set<node>::iterator it=s->begin(); it!=s->end(); it++)
    adj_list[it->id] = {};
  for(ind_set::iterator it=J->begin(); it!=J->end(); it++)
    if (it->id_k==e.id_k && s->find({it->i, it->id_k})!=s->end()) {
      adj_list[it->i].push_back(it->j);
      adj_list[it->j].push_back(it->i);
    }
  return adj_list;
}

void const_set(int i, int id_k, s_graph adj_list, set<node>* s) {
  queue<int> to_visit;
  unordered_set<int> visited;
  to_visit.push(i);
  visited.insert(i);
  while(!to_visit.empty()) {
    int u = to_visit.front();
    to_visit.pop();
    s->insert({u, id_k});
    for(int it=0; it<(int)adj_list[u].size(); it++) {
      int v = adj_list[u][v];
      if(visited.find(v)==visited.end()) {
        visited.insert(v);
        to_visit.push(v);
      }
    }
  }
}

void split_set(d_node e,ind_set* J,set<node>* s, set<node>* s1, set<node>* s2) {
  s_graph adj_list = const_adj_list(e, J, s);
  const_set(e.i, e.id_k, adj_list, s1);
  const_set(e.j, e.id_k, adj_list, s2);
}

void erase_graphic_m(d_node e, graphic_m* M, ind_set* J) {
  set<node>* s = M->set_of_node[e.i][e.id_k];
  set<node>* si = new set<node>;
  set<node>* sj = new set<node>;
  split_set(e, J, s, si, sj);
  delete s;
  for(set<node>::iterator it=si->begin(); it!=si->end(); it++)
    M->set_of_node[it->id][it->id_k] = si;
  for(set<node>::iterator it=sj->begin(); it!=sj->end(); it++)
    M->set_of_node[it->id][it->id_k] = sj;

}

void erase_part_m(d_node e, part_m* M) {
  M->used[e.i][e.j][e.color] = false;
}

bool can_exchange(d_node e, d_node f, graphic_m* M, ind_set* J) {
  erase_graphic_m(f, M, J);
  bool res = can_add(e, M);
  add_graphic_m(f, M);
  return res;
}

bool can_exchange(d_node e, d_node f, part_m* M) {
  erase_part_m(f, M);
  bool res = can_add(e, M);
  add_part_m(f, M);
  return res;
}

digraph const_digraph(graphic_m* M1, part_m* M2, ind_set* J, graph* G, int k) {
  digraph DG = initialize_digraph(G, k);
  for (digraph::iterator it=DG.begin(); it!=DG.end(); ++it) {
    d_node e = it->first;
    if (e!=s() && e!=r() && J->find(e)==J->end()) {
      if (can_add(e, M1))
        DG[e].push_back(s());
      if (can_add(e, M2))
        DG[r()].push_back(e);
      for(ind_set::iterator it=J->begin(); it!=J->end(); it++) {
        d_node f = *it;
        if (can_add(e, M1) && can_exchange(e, f, M1, J))
          DG[e].push_back(f);
        if (can_add(e, M2) && can_exchange(e, f, M2))
          DG[f].push_back(e);
      }
    }
  }
  return DG;
}

ind_set max_ind_set(graph* G, int k) {
  int n=G->n;
  ind_set J;
  graphic_m M1(n,k);
  part_m M2(n,k,G);
  while(true) {
    digraph DG = const_digraph(&M1, &M2, &J, G, k);
    return J;
  }
  return J;
}
