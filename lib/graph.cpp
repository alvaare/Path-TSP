#include<iostream>
#include"graph.hpp"
using namespace std;

bool is_connex(graph G) {
  bool visited[G.n]={false};
  int v = 0;
  queue<int> q;
  q.push(v);
  while(!q.empty()) {
    v = q.front();
    q.pop();
    if (!visited[v]) {
      visited[v] = true;
      for (int i=0; i < G.n; i++)
        if (G.edges[v][i] != 0)
          q.push(i);
    }
  }

  for(int i=0; i<G.n; i++)
    if(!visited[i]) {
      return false;
    }
  return true;
}

void print_graph(graph G) {
  for (int i=0; i<G.n; i++) {
    for (int j=0; j<G.n; j++) {
      cout << G.edges[i][j] << "\t";
    }
    cout << "\n";
  }
  cout << "\n";
}

int degree(graph G, int v) {
  int deg = 0;
  for (int i=0; i<G.n; i++) {
    if (G.edges[v][i] > 0) {
      deg++;
    }
  }
  return deg;
}
