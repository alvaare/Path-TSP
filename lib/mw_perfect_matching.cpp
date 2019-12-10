#include<iostream>
#include"mw_perfect_matching.hpp"
#include"lemon/matching.h"
#include"lemon/smart_graph.h"
using namespace std;

void construct_graph(graph* G, lemon::SmartGraph* g) {

}

matching mw_perfect_matching(graph* G) {
  lemon::SmartGraph g;
  construct_graph(G, &g);

  matching M(G->n);
  return M;
}
