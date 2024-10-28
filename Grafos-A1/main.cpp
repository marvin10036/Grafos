#include "Graph-lib/Hashes-Vector-Graph.hpp"
#include "Load-File/LoadFile.hpp"
#include "BFS/BFS.hpp"
#include "Hierholzer/Hierholzer.hpp"
#include "Dijkstra/Dijkstra.hpp"
#include "Floyd-Warshall/Floyd-Warshall.hpp"
#include <iostream>
#include <string>
#include <vector>


int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Número de parâmetros insuficiente. Espera-se 1."<< std::endl;
    return 1;
  }

  HashesVectorGraph graph = HashesVectorGraph();
  int status_code = loadFile(argc, argv, graph);

  // std::cout<< graph.qtdVertices() << std::endl;
  // std::cout<< graph.qtdArestas() << std::endl;

  // BFS(graph, std::stol(argv[2]));
  // Não consigo representar multigrafo na minha estrutura de dados
  floydWarshall(graph);

  return 0;
}
