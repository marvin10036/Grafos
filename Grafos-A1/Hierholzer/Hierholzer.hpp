#ifndef HIERHOLZER_HPP
#define HIERHOLZER_HPP

#include "../Graph-lib/Hashes-Vector-Graph.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <map>

struct hierholzerResult{
  bool has_cycle;
  std::vector<long> cycle;
};


void prettyPrintingHierholzer(hierholzerResult& hr);

hierholzerResult hierholzer(HashesVectorGraph& graph);

#endif
