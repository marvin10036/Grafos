#include "BFS.hpp"


void prettyPrintingBFS(std::vector<long>& edges_away_from_origin)
{
  if (edges_away_from_origin.empty() == true)
  {
    return;
  }

  std::vector<std::vector<long>> depth;
  // TODO file agnostic
  for (long i = 1; i < edges_away_from_origin.size(); i++)
  {
    if (edges_away_from_origin[i] != -1)
    {
      if (edges_away_from_origin[i] >= depth.size())
      {
        depth.resize(edges_away_from_origin[i] + 1);
      }
      depth[edges_away_from_origin[i]].push_back(i);
    }
  }

  for (long i = 0; i < depth.size(); i++)
  {
    std::cout << i << ": ";
    for (long j = 0; j < depth[i].size(); j++)
    {
      if (j == 0)
      {
        std::cout << depth[i][j];
      }
      else
      {
        std::cout << "," << depth[i][j];
      }
    }
    std::cout<<std::endl;
  }
}

std::vector<long> BFS(HashesVectorGraph& graph, const long& start_node_index)
{
  std::vector<long> ancestors(graph.qtdVertices() + 1, -1);
  std::vector<long> edges_away_from_origin(graph.qtdVertices() + 1, -1);
  std::vector<bool> visited(graph.qtdVertices() + 1, false);

  std::queue<long> q;
  long current_node_index = start_node_index;

  visited[current_node_index] = true;
  edges_away_from_origin[current_node_index] = 0;

  q.push(current_node_index);
  long current_level = -1;

  while (not(q.empty()))
  {
    current_node_index = q.front();
    q.pop();
    for (long i : graph.vizinhos(current_node_index))
    {
      if (visited[i] == false)
      {
        visited[i] = true;
        ancestors[i] = current_node_index;
        edges_away_from_origin[i] = edges_away_from_origin[current_node_index] + 1;
        q.push(i);
      }
    }
  }
  // Seção de printing do exercício
  prettyPrintingBFS(edges_away_from_origin);
  return ancestors;
}

