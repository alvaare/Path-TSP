#include<iostream>
#include<algorithm>
#include<queue>
#include<unordered_set>
#include"graph.hpp"
#include"matroid_intersection.hpp"
using namespace std;

bool operator<(const d_node& lhs, const d_node& rhs) {
  if (lhs.i != rhs.i)
    return lhs.i < rhs.i;
  if (lhs.j != rhs.j)
    return lhs.j < rhs.j;
  if (lhs.id_k != rhs.id_k)
    return lhs.id_k < rhs.id_k;
  if (lhs.color != rhs.color)
    return lhs.color < rhs.color;
  return false;
}

bool operator<(const node& lhs, const node& rhs) {
  if (lhs.id != rhs.id)
    return lhs.id < rhs.id;
  if (lhs.id_k != rhs.id_k)
    return lhs.id_k < rhs.id_k;
  return false;
};

bool operator!=(const d_node& lhs, const d_node& rhs) {
  return (lhs<rhs || rhs<lhs);
}

bool operator==(const d_node& lhs, const d_node& rhs) {
  return !(lhs!=rhs);
}

d_node s() {
  return {-1,-1,-1,-1};
}

d_node r() {
  return {-1,-1,-1,0};
}

void print_d_node(d_node e) {
  cout << e.i << " " << e.j << " " << e.color << " " << e.id_k;
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

void print_set_node(set<node>* A) {
  for(set<node>::iterator it=A->begin(); it!=A->end(); it++) {
    cout << it->id << " ";
  }
  cout << "\n";
}

void print_graphic_m(graphic_m* M) {
  for (int i=0; i<M->n; i++) {
    cout << i << ":\n";
    for (int id_k=0; id_k<M->k; id_k++) {
      print_set_node(M->set_of_node[i][id_k]);
      cout << "\n";
    }
  }
}

void print_part_m(part_m* M){
  for(int i=0; i<M->n; i++) {
    cout << i << ":\n";
    for(int j=0; j<M->n; j++) {
      cout << j << ": ";
      for(int k=0; k<M->k; k++) {
        cout << M->used[i][j][k] << " ";
      }
      cout << "\n";
    }
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
    if (it->id_k==e.id_k && s->find({it->i, it->id_k})!=s->end()
  && (it->i!=e.i || it->j!=e.j) && (it->i!=e.j || it->j!=e.i)) {
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
      int v = adj_list[u][it];
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
  if (J->find(f)!=J->end())
    erase_graphic_m(f, M, J);
  bool res = can_add(e, M);
  if (J->find(f)!=J->end())
    add_graphic_m(f, M);
  return res;
}

bool can_exchange(d_node e, d_node f, part_m* M, ind_set* J) {
  if (J->find(f)!=J->end())
    erase_part_m(f, M);
  bool res = can_add(e, M);
  if (J->find(f)!=J->end())
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
        if (can_add(e, M2) && can_exchange(e, f, M2, J))
          DG[f].push_back(e);
      }
    }
  }
  return DG;
}

typedef vector<d_node> dipath;

dipath return_dipath(dipath P) {
  dipath P2;
  for(int i=P.size()-1; i>=0; i--)
    P2.push_back(P[i]);
  return P2;
}

void print_father(map<d_node, d_node> father) {
  for(map<d_node,d_node>::iterator it=father.begin(); it!=father.end(); it++) {
    cout << "The father of: "; print_d_node(it->first); cout << " is: ";
    print_d_node(it->second); cout << "\n";
  }
}

dipath dipath_from_fathers(map<d_node,d_node> father) {
  dipath P;
  d_node v = s();
  while(v!=r()) {
    if (father.find(v)==father.end()) {
      dipath empty;
      return empty;
    };
    v = father[v];
    P.push_back(v);
  }
  P.pop_back();
  return return_dipath(P);
}

void print_dipath(dipath* P) {
  cout << "The dipath contains:\n";
  for(int i=0; i<(int)P->size(); i++) {
    print_d_node((*P)[i]);
    cout << "\n";
  }
}

dipath find_dipath(digraph* G) {
  queue<d_node> Q;
  map<d_node,d_node> father;
  Q.push(r());
  while(!Q.empty()&&Q.front()!=s()) {
    d_node v = Q.front();
    Q.pop();
    vector<d_node> neighbors = (*G)[v];
    for (int i=0; i<(int)neighbors.size(); i++)
      if(father.find(neighbors[i]) == father.end()) {
        father[neighbors[i]] = v;
        Q.push(neighbors[i]);
      }
  }
  return dipath_from_fathers(father);
}

void update_ind_set(ind_set* J, graphic_m* M1, part_m* M2, dipath P) {
  int i = 0;
  for (; i<(int)P.size()-1; i+=2) {
    erase_part_m(P[i+1], M2);
    add_part_m(P[i], M2);
    erase_graphic_m(P[i+1], M1, J);
    add_graphic_m(P[i], M1);
    J->insert(P[i]);
    J->erase(P[i+1]);
  }
  J->insert(P[i]);
  add_part_m(P[i], M2);
  add_graphic_m(P[i], M1);
}

void print_ind_set(ind_set* A) {
  cout << "The independent set contains:\n";
  for(ind_set::iterator it=A->begin(); it!=A->end(); it++) {
    print_d_node(*it);
    cout << "\n";
  }
  cout << "\n";
}

ind_set max_ind_set(graph* G, int k) {
  int n=G->n;
  ind_set J;
  graphic_m M1(n,k);
  part_m M2(n,k,G);
  int i=0;
  while(true) {
    digraph DG = const_digraph(&M1, &M2, &J, G, k);
    dipath P = find_dipath(&DG);
    if (P.empty())
      return J;
    else
      update_ind_set(&J, &M1, &M2, P);
  }
  return J;
}
