#ifndef __FIND_K_HPP_INCLUDED__
#define __FIND_K_HPP_INCLUDED__

#include"graph.hpp"

int find_k(LP_solution*);

graph from_LP_solution_to_graph(LP_solution*);

graph from_LP_solution_to_graph(LP_solution*, int k);


#endif
