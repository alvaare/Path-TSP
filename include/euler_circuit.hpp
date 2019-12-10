#ifndef __EULER_CIRCUIT_HPP_INCLUDED__
#define __EULER_CIRCUIT_HPP_INCLUDED__

#include "graph.hpp"

struct circuit {
  int node;
  circuit* next;
  circuit(int n) {
    this->node = n;
    this->next = NULL;
  }
};

circuit euler_circuit(graph*, int, int);

#endif
