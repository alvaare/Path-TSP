#include <iostream>
#include <set>
#include "graph.hpp"
#include "euler_circuit.hpp"
using namespace std;

typedef set<int> neighbors;

void construct_times_edge_used(int** times_edge_used, int n) {
  for (int i = 0; i < n; ++i)
    times_edge_used[i] = new int[n];
  for(int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      times_edge_used[i][j]=0;
}

void destroy_times_edge_used(int** times_edge_used, int n) {
  for (int i=0; i < n; i++)
    delete [] times_edge_used[i];
  delete [] times_edge_used;
}

void construct_disused_edges(graph* G, neighbors* disused_edges) {
  for (int i=0; i<G->n; i++)
    for (int j=0; j<G->n; j++)
      if (G->edges[i][j] > 0)
        disused_edges[i].insert(j);
}

void use_edge(int i, int j, neighbors* disused_edges, int* times_edge_used[],
              graph* G) {
  times_edge_used[i][j]++;
  times_edge_used[j][i]++;
  if(times_edge_used[i][j] == G->edges[i][j]) {
    disused_edges[i].erase(j);
    disused_edges[j].erase(i);
  }
}

circuit* first_trail(graph* G, neighbors* disused_edges, int* times_edge_used[],
                  set<int>* visited, circuit* C) {
  circuit* curr_circuit = C;
  int curr_node = C->node;
  while(!disused_edges[curr_node].empty()) {
    int next_node = *disused_edges[curr_node].begin();
    circuit* next_circuit = new circuit(next_node);
    use_edge(curr_node, next_node, disused_edges, times_edge_used, G);
    curr_circuit->next = next_circuit;
    curr_node = next_node;
    curr_circuit = next_circuit;
    visited->insert(curr_node);
  }
  return curr_circuit;
}

circuit* find_next_start(circuit* C, int* new_node, set<int>* visited, graph* G) {
  circuit* curr_circuit = C;
  while(curr_circuit->next != NULL) {
    for (int i=0; i<G->n; i++)
      if (G->edges[curr_circuit->node][i] > 0 && !visited->count(i)) {
        *new_node = i;
        return curr_circuit;
      }
    curr_circuit = curr_circuit->next;
  }
  cout << "ERROR: circuit not found";
  return NULL;
}

void aux_trail(graph* G, set<int>* visited, circuit* C,
                neighbors* disused_edges, int* times_edge_used[], int new_node){
  circuit* curr_circuit = new circuit(new_node);
  use_edge(C->node, new_node, disused_edges, times_edge_used, G);
  visited->insert(new_node);
  circuit* last_C =
        first_trail(G, disused_edges, times_edge_used, visited, curr_circuit);
  last_C->next = C->next;
  C->next = curr_circuit;
}

circuit euler_circuit(graph* G, int s, int t) {
  circuit C(s);
  int n = G->n;
  set<int> visited;
  visited.insert(s);
  neighbors disused_edges[n];
  int** times_edge_used = new int*[n];

  construct_times_edge_used(times_edge_used, n);
  construct_disused_edges(G, disused_edges);
  first_trail(G, disused_edges, times_edge_used, &visited, &C);
  while ((int)visited.size() < n) {
    int new_node;
    circuit* next_start = find_next_start(&C, &new_node, &visited, G);
    aux_trail(G, &visited, next_start, disused_edges, times_edge_used,new_node);
  }
  destroy_times_edge_used(times_edge_used, n);
  return C;
}

void print_circuit(circuit* C) {
  cout << C->node << "\n";
  if (C->next != NULL)
    print_circuit(C->next);
}

path clean_circuit(circuit* C, int n, int t) {
  path P = path(n);
  int i=0;
  bool used[n] = {false};
  circuit* curr_circuit = C;
  while(curr_circuit != NULL){
    int node = curr_circuit->node;
    if(!used[node] && node != t) {
      used[node] = true;
      P.nodes[i] = node;
      i++;
    }
    curr_circuit = curr_circuit->next;
  }
  P.nodes[n-1] = t;
  return P;
}
