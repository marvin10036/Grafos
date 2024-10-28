#include "Dijkstra.hpp"


void prettyPrintingDijkstra(dijkstraResult dr, long start_node_index)
{
  std::vector<long> ancestry = dr.ancestry;
  std::vector<double> lowest_cost = dr.lowest_cost;

  double current_node_cost;
  for (long i = 1; i < ancestry.size(); i++)
  {
    // Ou é a origem ou alcançável
    if (ancestry[i] != -1 || i == start_node_index)
    {
      current_node_cost = lowest_cost[i];
      std::cout << i << ": ";

      std::string path_string;
      long inner_path_node = i;

      while (inner_path_node != start_node_index)
      {
        path_string.insert(0, std::to_string(inner_path_node));
        path_string.insert(0, ",");
        inner_path_node = ancestry[inner_path_node];
      }
      // Adicionando o start_node_index
      std::cout << start_node_index;
      std::cout << path_string << "; d=" << current_node_cost << std::endl;
    }
  }
}

dijkstraResult dijkstra(HashesVectorGraph& graph, long start_node_index)
{
  // Multisets são binary search trees, pair contém <custo, index_vertice>
  std::multiset<std::pair<double, long>> ms;

  std::vector<long> ancestry(graph.qtdVertices() + 1);
  std::vector<double> current_lowest_cost(graph.qtdVertices() + 1);
  std::vector<bool> visited(graph.qtdVertices() + 1);

  // Inicializando
  for (long i = 1; i <= graph.qtdVertices(); i++)
  {
    ms.insert({std::numeric_limits<double>::max(), i});
    ancestry[i] = -1;
    current_lowest_cost[i] = std::numeric_limits<double>::max();
    visited[i] = false;
  }

  ms.erase(ms.find({current_lowest_cost[start_node_index], start_node_index}));
  ms.insert({0.0, start_node_index});

  current_lowest_cost[start_node_index] = 0.0;

  while (ms.empty() == false)
  {
    std::pair<double, long> current_node = *(ms.begin());
    ms.erase(ms.begin());

    visited[current_node.second] = true;

    for (long i : graph.vizinhos(current_node.second))
    {
      if (visited[i] == false)
      {
        // Relaxamento
        if (current_lowest_cost[i] > current_node.first + graph.peso(current_node.second, i))
        {
          ms.erase(ms.find({current_lowest_cost[i], i}));

          current_lowest_cost[i] = current_node.first + graph.peso(current_node.second, i);
          ms.insert({current_lowest_cost[i], i});

          ancestry[i] = current_node.second;
        }
      }
    }
  }
  prettyPrintingDijkstra({ancestry, current_lowest_cost}, start_node_index);
  return {ancestry, current_lowest_cost};
}

