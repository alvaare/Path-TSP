#ifndef __GRAPH_HPP_INCLUDED__
#define __GRAPH_HPP_INCLUDED__

struct graph {
  int n;
  int edges[n][n];
};

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
