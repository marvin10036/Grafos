#ifndef LOAD_FILE_HPP
#define LOAD_FILE_HPP

#include "../Graph-lib/Hashes-Vector-Graph.hpp"
#include <fstream>

void createNodes(std::ifstream& fd, std::string& stringBuffer, HashesVectorGraph& graph);

void createEdges(std::ifstream& fd, std::string& stringBuffer, HashesVectorGraph& graph);

int loadFile(int argc, char** argv, HashesVectorGraph& graph);

#endif 
