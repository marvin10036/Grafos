#include "Hashes-Vector-Graph.hpp"


// Node class methods
Node::Node() = default;
Node::Node(const std::string& nd) : adjacency_list(), node_data(nd) {};

std::map<long, double> Node::getAdjacencyList()
{
  return adjacency_list;
}

std::string Node::getNodeData()
{
  return node_data;
}

void Node::addEdge(const long destination_node, const double weight)
{
  adjacency_list[destination_node] = weight;
}

// HashesVectorGraph class methods
HashesVectorGraph::HashesVectorGraph(): graph_nodes(), edges_counter(0) {};

long HashesVectorGraph::getEdgesCounter()
{
  return edges_counter;
}

std::shared_ptr<Node> HashesVectorGraph::getNodeAtIndex(const long node_index)
{
  std::shared_ptr<Node> node;
  try
  {
    node = graph_nodes.at(node_index);
  }
  catch(std::out_of_range)
  {
    std::cerr << "Index out of range\n";
  }
  return node;
}

void HashesVectorGraph::addNode(const long node_index, const std::string& node_data)
{
  // TODO Insert pode dar problemas se uma operação de inserção for repetida em index já usado
  std::shared_ptr<Node> x = std::make_shared<Node>(node_data);

  // TODO, Estou esperançosamente esperando que os indices venham em ordem
  if (node_index > graph_nodes.size()) 
  {
    graph_nodes.resize(node_index);
  }

  graph_nodes.insert(graph_nodes.begin() + node_index, std::make_shared<Node>(node_data));
}

void HashesVectorGraph::addEdgeToNode(const long node_index, const long destination_node_index, const double weight)
{
  std::shared_ptr<Node> node = getNodeAtIndex(node_index);

  node->addEdge(destination_node_index, weight);
  edges_counter += 1;
}

long HashesVectorGraph::qtdVertices()
{
  if (graph_nodes.size() == 0)
  {
    return 0;
  }
  else
  {
    // -1 pois os arquivos de input começam com o index 1
    // TODO fazer solução agnóstica do arquivo de input
    return graph_nodes.size() - 1;
  }
}

long HashesVectorGraph::qtdArestas()
{
  // TODO adicionar caso para digrafo
  return edges_counter/2;
}

long HashesVectorGraph::grau(const long node_index)
{
  std::shared_ptr<Node> node = getNodeAtIndex(node_index);

  return (node->getAdjacencyList()).size();
}

std::string HashesVectorGraph::rotulo(const long node_index)
{
  std::shared_ptr<Node> node = getNodeAtIndex(node_index);

  return node->getNodeData();
}

std::vector<long> HashesVectorGraph::vizinhos(const long node_index)
{
  std::shared_ptr<Node> node = getNodeAtIndex(node_index);
  std::vector<long> keys;

  for (auto i : node->getAdjacencyList())
  {
    // É um std::pair
    keys.push_back(i.first);
  }
  return keys;
}

bool HashesVectorGraph::haAresta(const long first_node_index, const long second_node_index)
{
  std::shared_ptr<Node> first_node = getNodeAtIndex(first_node_index);
  std::shared_ptr<Node> second_node = getNodeAtIndex(second_node_index);

  std::map<long, double> first_node_adjacency_list = first_node->getAdjacencyList();
  if (first_node_adjacency_list.find(second_node_index) != first_node_adjacency_list.end()) 
  {
    return true;
  }

  std::map<long, double> second_node_adjacency_list = second_node->getAdjacencyList();
  if (second_node_adjacency_list.find(first_node_index) != second_node_adjacency_list.end()) 
  {
    return true;
  }

  return false;
}

double HashesVectorGraph::peso(const long first_node_index, const long second_node_index)
{
  if (haAresta(first_node_index, second_node_index))
  {
    return getNodeAtIndex(first_node_index)->getAdjacencyList()[second_node_index];
  }
  return std::numeric_limits<double>::max();
}

