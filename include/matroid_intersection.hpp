#ifndef __MATROID_INTERSECTION_HPP_INCLUDED__
#define __MATROID_INTERSECTION_HPP_INCLUDED__

#include<set>
#include<map>
#include<vector>
using namespace std;

struct d_node {
  int i;
  int j;
  int color;
  int id_k;
};

bool operator<(const d_node&, const d_node&);

struct node {
  int id;
  int id_k;
};

bool operator<(const node&, const node&);

typedef map<d_node,vector<d_node>> digraph;

typedef pair<d_node,vector<d_node>> d_neighbors;

typedef set<d_node> ind_set;

struct graphic_m{
  int k;
  int n;
  set<node>*** set_of_node;
  graphic_m(int n, int k) {
    this->n=n;
    this->k=k;
    this->set_of_node = new set<node>**[n];
    for (int i=0; i<n; i++) {
      this->set_of_node[i] = new set<node>*[k];
      for (int j=0; j<k; j++) {
        node u = {i,j};
        this->set_of_node[i][j] = new set<node>;
        this->set_of_node[i][j]->insert(u);
      }
    }
  }
  ~graphic_m() {
    bool freed[n][k];
    for (int i=0; i<n; i++)
      for (int j=0; j<n; j++)
        freed[i][j] = false;
    for (int i=0; i<n; i++) {
      for (int j=0; j<k; j++)
        if (!freed[i][j]) {
          set<node> s = *(set_of_node[i][j]);
          for (set<node>::iterator it=s.begin(); it!=s.end(); it++)
            freed[it->id][it->id_k] = true;
          delete this->set_of_node[i][j];
        }
      delete [] this->set_of_node[i];
    }
    delete [] this->set_of_node;
  }
};

struct part_m {
  int n;
  int k;
  bool*** used;
  part_m(int n, int k, graph* G) {
    this->n = n;
    this->k = k;
    this->used = new bool**[n];
    for (int i = 0; i < n; i++) {
      this->used[i] = new bool*[n];
      for (int j = 0; j < n; j++) {
        int colors = G->edges[i][j];
        this->used[i][j] = new bool[colors];
        for (int l = 0; l < colors; l++)
          this->used[i][j][l] = false;
      }
    }
  }
  ~part_m() {
    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++)
        delete [] this->used[i][j];
      delete [] this->used[i];
    }
    delete [] this->used;
  }
};

struct tree_list {
  int n;
  int k;
  graph** content;
  tree_list(int n, int k) {
    this->n=n;
    this->k=k;
    this->content = new graph*[k];
    for (int i=0; i<k; i++)
      this->content[i] = new graph(n);
  }
  ~tree_list() {
    for (int i=0; i<k; i++)
      delete this->content[i];
    delete [] this->content;
  }
};

ind_set max_ind_set(graph*, int);

void print_ind_set(ind_set*);

tree_list tree_list_from_ind_set(graph*, ind_set*, int);

void print_tree_list(tree_list*);

#endif
