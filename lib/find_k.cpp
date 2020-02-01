#include<iostream>
#include<stack>
#include<algorithm>
#include<cmath>
#include"graph.hpp"
using namespace std;

const double eps = 1e-5;

int gcd(int a, int b) {
  if (b==0)
    return a;
  return gcd(b, a%b);
}

int lcm(int a, int b) {
  if(a>b)
    return (a/gcd(a,b))*b;
  else
    return (b/gcd(a,b))*a;
}

int lcm_multiple(stack<int>* ks) {
  if (ks->size()==0)
    return 0;
  while (ks->size()>1) {
    int a = ks->top();
    ks->pop();
    int b = ks->top();
    ks->pop();
    ks->push(lcm(a,b));
  }
  return ks->top();
}

int k_of_double(double x) {
  int k=1;
  while(true) {
    if (abs(round(k*x)-k*x) < eps)
      return k;
    k++;
  }
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
