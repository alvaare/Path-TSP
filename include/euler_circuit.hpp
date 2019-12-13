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
  ~circuit() {
    delete this->next;
  }
};

circuit euler_circuit(graph*, int, int);

void print_circuit(circuit*);

path clean_circuit(circuit*, int, int);

#endif
