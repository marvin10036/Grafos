#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "../Graph-lib/Hashes-Vector-Graph.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <limits>
#include <string>

struct dijkstraResult{
  std::vector<long> ancestry;
  std::vector<double> lowest_cost;
};


void prettyPrintingDijkstra(dijkstraResult dr, long start_node_index);

dijkstraResult dijkstra(HashesVectorGraph& graph, long start_node_index);

#endif
