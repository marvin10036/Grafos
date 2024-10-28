#ifndef FLOYD_WARSHALL_HPP
#define FLOYD_WARSHALL_HPP

#include "../Graph-lib/Hashes-Vector-Graph.hpp"
#include <vector>

struct floydWarshallResult {
  std::vector<std::vector<double>> cost;
  std::vector<std::vector<long>> predecessors;
};


void prettyPrintingFloydWarshall(floydWarshallResult& fwr);

floydWarshallResult floydWarshall(HashesVectorGraph& graph);

#endif
