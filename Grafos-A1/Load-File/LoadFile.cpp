#include "LoadFile.hpp"


void createNodes(std::ifstream& fd, std::string& stringBuffer, HashesVectorGraph& graph)
{
  fd >> stringBuffer;
  int number_of_nodes = std::stoi(stringBuffer);

  for (int i = 0; i < number_of_nodes; i++)
  {
    // Pular o number_of_nodes após leitura
    fd >> stringBuffer;
    long node_index = std::stol(stringBuffer);

    // O getLine move o byte offset pra frente antes de ler
    std::getline(fd, stringBuffer);
    size_t start_of_the_string_index = stringBuffer.find_first_not_of(" ");
    size_t first_quote_index = stringBuffer.find('"');
    size_t last_quote_index = stringBuffer.rfind('"');
    stringBuffer = stringBuffer.substr(first_quote_index + 1, last_quote_index - 1 - first_quote_index);

    std::string node_data = stringBuffer;
    graph.addNode(node_index, node_data);
  }
}

void createEdges(std::ifstream& fd, std::string& stringBuffer, HashesVectorGraph& graph)
{
  long node_index, destination_node_index;
  double weight;
  while(fd >> stringBuffer)
  {
    // Primeiro vertice
    node_index = std::stol(stringBuffer);

    // Segundo vertice
    fd >> stringBuffer;
    destination_node_index = std::stol(stringBuffer);

    // Peso da Aresta
    fd >> stringBuffer;
    weight = std::stod(stringBuffer);

    graph.addEdgeToNode(node_index, destination_node_index, weight);
    // TODO, estou sempre considerando que são grafos não dirigidos
    graph.addEdgeToNode(destination_node_index, node_index, weight);
  }
}

int loadFile(int argc, char** argv, HashesVectorGraph& graph)
{
  std::ifstream fd{argv[1], std::ios::in};
  if (!fd) 
  {
    std::cerr << "Arquivo não encontrado" << std::endl;
    fd.close();
    return 1;
  }

  std::string stringBuffer;
  while (fd >> stringBuffer) 
  {
    if (stringBuffer == "*vertices")
    {
      createNodes(fd, stringBuffer, graph);
    }
    if (stringBuffer == "*edges")
    {
      createEdges(fd, stringBuffer, graph);
    }
  }
  fd.close();
  return 0;
}

