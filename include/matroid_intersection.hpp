#ifndef __MATROID_INTERSECTION_HPP_INCLUDED__
#define __MATROID_INTERSECTION_HPP_INCLUDED__

#include<set>
#include<map>
using namespace std;

struct d_node {
  int i;
  int j;
  int id_k;
  int color;
}

struct node {
  int id;
  int id_k;
}

typedef map<d_node,vector<d_node>> digraph;

typedef set<d_node> independent_set;

struct graphic_matroid {
  int k;
  int n;
  set<node>** set_of_node;
  graphic_matroid(int n, int k) {
    this->n=n;
    this->k=k;
    this->set_of_node = new set<node>*[n];
    for (int i=0; i<n; i++) {
      this->set_of_node[i] = new set<node>[k];
      for (int j=0; j<n; j++)
        this->set_of_node[i][j] = set<node>
    }
  }
};

struct partition_matroid {
  int n;
  int k;
  bool*** used;
  partition_matroid(int n, int k) {
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
  ~partition_matroid() {
    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++)
        delete [] this->edges[i][j];
      delete [] this->edges[i];
    }
    delete [] this->edges;
  }
};

#endif
