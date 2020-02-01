#include<iostream>
#include<stack>
#include"graph.hpp"
using namespace std;

int lcm_multiple(stack<int>* ks) {
  return 0;
}

int k_of_double(double x) {
  return 0;
}

int find_k(LP_solution* x) {
  int n = x->n;
  stack<int> ks;
  for(int i=0; i<n; i++)
    for(int j=i+1; j<n; j++)
      if(x->edges[i][j]>0)
        ks.push(k_of_double(x->edges[i][j]));
  return lcm_multiple(&ks);
}
