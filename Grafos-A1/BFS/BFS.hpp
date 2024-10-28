#ifndef BFS_HPP
#define BFS_HPP

#include "../Graph-lib/Hashes-Vector-Graph.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <queue>


void prettyPrintingBFS(std::vector<long>& edges_away_from_origin);

std::vector<long> BFS(HashesVectorGraph& graph, const long& start_node_index);

#endif
