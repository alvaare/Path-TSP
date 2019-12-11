#include<iostream>
#include"mw_perfect_matching.hpp"
#include"lemon/matching.h"
#include"lemon/smart_graph.h"
using namespace std;

typedef lemon::SmartGraph l_graph;
typedef l_graph::EdgeMap<int> l_weights;
typedef l_graph::Node l_nodes;
typedef lemon::MaxWeightedPerfectMatching<lemon::SmartGraph> l_matching;
typedef l_graph::EdgeIt EdgeIt;

void construct_graph(graph* G, l_graph* g, l_weights* weight, l_nodes* nodes) {
  int n = G->n;
  for (int i=0; i<n; i++)
    nodes[i] = g->addNode();
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      weight->set(g->addEdge(nodes[i], nodes[j]), -G->edges[i][j]);
}

void copy_matching(l_graph* g, l_matching* m, matching* M) {
  for (EdgeIt e(*g); e !=lemon::INVALID; ++e)
    if (m->matching(e)) {
      M->pair[g->id(g->u(e))] = g->id(g->v(e));
      M->pair[g->id(g->v(e))] = g->id(g->u(e));
    }
}

matching mw_perfect_matching(graph* G) {
  int n = G->n;
  l_graph g;
  l_nodes nodes[n];
  l_weights weight(g);
  construct_graph(G, &g, &weight, nodes);
  l_matching m(g,weight);
  m.run();
  matching M(G->n);
  copy_matching(&g, &m, &M);
  return M;
}
