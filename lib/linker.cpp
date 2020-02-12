#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<iostream>
#include"linker.hpp"
using namespace std;

void read_LP_solution(LP_solution* x) {
  string line;
  ifstream myfile ("temp.txt");
  int i=0, j=0;
  while (getline(myfile,line)) {
    double e = stod(line);
    x->edges[i][j] = e;
    if(j==x->n-1) {
      j = 0;
      i++;
    }
    else
      j++;
  }
  myfile.close();
}

void write_problem(graph* G, int s, int t) {
  ofstream myfile;
  myfile.open("temp.txt");
  myfile << G->n << "\n" << s << "\n" << t << "\n";
  for (int i=0; i<G->n; i++) {
    for (int j=0; j<G->n; j++)
      myfile << G->edges[i][j] << ",";
    myfile << "\n";
  }
  myfile.close();
}

LP_solution get_solution(graph* G, int s, int t) {
  write_problem(G, s, t);

  char command[] = "python Lp_solver.py";
  system(command);

  LP_solution x(G->n);
  x.s=s;
  x.t=t;
  read_LP_solution(&x);

  return x;

}
