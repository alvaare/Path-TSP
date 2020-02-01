#include<iostream>
#include<queue>
#include<climits>
#include"graph.hpp"
using namespace std;

bool is_connex(graph* G) {
  bool visited[G->n]={false};
  int v = 0;
  queue<int> q;
  q.push(v);
  while(!q.empty()) {
    v = q.front();
    q.pop();
    if (!visited[v]) {
      visited[v] = true;
      for (int i=0; i < G->n; i++)
        if (G->edges[v][i] != 0)
          q.push(i);
    }
  }

  for(int i=0; i<G->n; i++)
    if(!visited[i]) {
      return false;
    }
  return true;
}

void print_graph(graph* G) {
  for (int i=0; i<G->n; i++) {
    for (int j=0; j<G->n; j++) {
      cout << G->edges[i][j] << "\t";
    }
    cout << "\n";
  }
  cout << "\n";
}

int degree(graph* G, int v) {
  int deg = 0;
  for (int i=0; i<G->n; i++) {
    if (G->edges[v][i] > 0) {
      deg++;
    }
  }
  return deg;
}

void print_matching(matching* M) {
  for (int i=0; i<M->n; i++) {
    cout << i << "->" << M->pair[i] << "\n";
  }
}

graph complete_graph(graph* G) {
  graph C(G->n);
  for (int i=0; i<G->n; i++)
    for (int j=0; j<G->n; j++) {
      if (G->edges[i][j]>0 || i==j)
        C.edges[i][j] = G->edges[i][j];
      else
        C.edges[i][j] = INT_MAX/2;
      }
  for (int k=0; k<G->n; k++)
    for (int i=0; i<G->n; i++)
      for (int j=0; j<G->n; j++)
        if(C.edges[i][j] > C.edges[i][k]+C.edges[k][j])
          C.edges[i][j] = C.edges[i][k]+C.edges[k][j];
  return C;
}

void print_path(path* P) {
  for (int i=0; i<P->n; i++) {
    cout << P->nodes[i] << " ";
  }
  cout << "\n";
}

void print_LP_solution(LP_solution* G) {
  cout << "n: " << G->n << "\n";
  cout << "s: " << G->s << "\n";
  cout << "t: " << G->t << "\n";
  for (int i=0; i<G->n; i++) {
    for (int j=0; j<G->n; j++) {
      cout << G->edges[i][j] << "\t";
    }
    cout << "\n";
  }
  cout << "\n";
}
