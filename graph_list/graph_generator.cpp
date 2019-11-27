#include<iostream>
#include<cmath>
#include<fstream>
#include<algorithm>
#include<tuple>
#include<queue>
using namespace std;

const int n = 8;
ofstream file ("graphs_"+to_string(n)+".txt");


struct graph {
  bool G[n][n] = {0};
};

void debug(bool* V){
  for (int i=0; i<n; i++) {
    cout << V[i];
  }
  cout << "\n";
}

bool is_connex(graph G) {
  bool visited[n]={false};
  int v = 0;
  queue<int> q;
  q.push(v);
  while(!q.empty()) {
    v = q.front();
    q.pop();
    if (!visited[v]) {
      visited[v] = true;
      for (int i=0; i < n; i++)
        if (G.G[v][i])
          q.push(i);
    }
  }

  for(int i=0; i<n; i++)
    if(!visited[i]) {
      return false;
    }
  return true;
}

void store(graph G) {
  for (int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      file << G.G[i][j];
    }
    file << "\n";
  }
  file << "\n";
}

void print_graph(graph G){
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      cout << G.G[i][j];
    }
    cout << "\n";
  }
  cout << "\n";
}

void search_graph(graph G, int  i, int j) {
  G.G[i][j] = true;
  G.G[j][i] = true;
  if (is_connex(G)){
    store(G);
  }
  if (i==j+1 && i < n-1) {
    search_graph(G,i+1,0);
    G.G[i][j]=false;
    G.G[j][i]=false;
    search_graph(G,i+1,0);
  }
  if (i!=j+1) {
    search_graph(G,i,j+1);
    G.G[i][j]=false;
    G.G[j][i]=false;
    search_graph(G,i,j+1);
    j++;
  }
}

int main() {
  graph G;
  search_graph(G,1,0);
}
