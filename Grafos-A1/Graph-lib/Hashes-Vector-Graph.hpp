#ifndef HASHESVECTORGRAPH_HPP
#define HASHESVECTORGRAPH_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <limits>
#include <cstdlib>


class Node
{
  private:
    // Curioso, os maps não deram problema algum
    std::map<long, double> adjacency_list;
    std::string node_data;

  public:
    Node();
    Node(const std::string& nd);

    std::map<long, double> getAdjacencyList();
    std::string getNodeData();

    void addEdge(const long destination_node, const double weight);
};

class HashesVectorGraph
{
  private:
    // Poderia ser std::vector<Node> graph_nodes, mas o objeto é grande
    std::vector<std::shared_ptr<Node>> graph_nodes;
    long edges_counter;

  public:
    HashesVectorGraph();

    long getEdgesCounter();
    std::shared_ptr<Node> getNodeAtIndex(const long node_index);

    void addNode(const long node_index, const std::string& node_data);
    void addEdgeToNode(const long node_index, const long destination_node_index, const double weight);

    // Funções do exercício 1
    long qtdVertices();
    long qtdArestas();
    long grau(const long node_index);
    std::string rotulo(const long node_index);
    std::vector<long> vizinhos(const long node_index);
    bool haAresta(const long first_node_index, const long second_node_index);
    double peso(const long first_node_index, const long second_node_index);
};

#endif
