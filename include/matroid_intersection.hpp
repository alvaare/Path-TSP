#ifndef __MATROID_INTERSECTION_HPP_INCLUDED__
#define __MATROID_INTERSECTION_HPP_INCLUDED__

#include<set>
#include<map>
#include<vector>
using namespace std;

struct d_node {
  int i;
  int j;
  int id_k;
  int color;
};

bool operator<(const d_node&, const d_node&);

struct node {
  int id;
  int id_k;
};

bool operator<(const node&, const node&);

typedef map<d_node,vector<d_node>> digraph;

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
    for (int i=0; i<n; i++) {
      for (int j=0; j<k; j++)
        delete this->set_of_node[i][j];
      delete [] this->set_of_node[i];
    }
    delete [] this->set_of_node;
  }
};

struct partition_m {
  int n;
  int k;
  bool*** used;
  partition_m(int n, int k) {
    this->n = n;
    this->k = k;
    this->used = new bool**[n];
    for (int i = 0; i < n; i++) {
      this->used[i] = new bool*[n];
      for (int j = 0; j < n; j++) {
        this->used[i][j] = new bool[k];
        for (int l = 0; l < k; l++)
          this->used[i][j][k] = false;
      }
    }
  }
  ~partition_m() {
    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++)
        delete [] this->used[i][j];
      delete [] this->used[i];
    }
    delete [] this->used;
  }
};

ind_set max_ind_set(graph*, int);

#endif
