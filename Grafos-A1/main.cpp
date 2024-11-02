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
  if (argc != 3)
  {
    std::cerr << "Número de parâmetros insuficiente. Espera-se 2."<< std::endl;
    std::cerr << "arquivo_grafo.net numero_vertice_inicial"<< std::endl;
    return 1;
  }

  HashesVectorGraph graph = HashesVectorGraph();

  int status_code = loadFile(argc, argv, graph);
  if (status_code != 0)
  {
    return 1;
  }

  std::cout<< graph.qtdVertices() << std::endl;
  std::cout<< graph.qtdArestas() << std::endl;

  BFS(graph, std::stol(argv[2]));
  dijkstra(graph, std::stol(argv[2]));
  hierholzer(graph);
  // Não consigo representar multigrafo na minha estrutura de dados
  floydWarshall(graph);

  return 0;
}
