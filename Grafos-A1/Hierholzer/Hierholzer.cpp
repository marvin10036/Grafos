#include "Hierholzer.hpp"


void prettyPrintingHierholzer(hierholzerResult& hr)
{
  if (hr.has_cycle == false)
  {
    std::cout << "0" << std::endl;
  }
  else
  {
    std::cout << "1" << std::endl;
    bool first_time = true;
    for (long i : hr.cycle)
    {
      if (first_time)
      {
        std::cout << i;
        first_time = false;
      }
      else
      {
        std::cout << ",";
        std::cout << i;
      }

    }
    std::cout << std::endl;
  }
}

hierholzerResult searchEulerianSubcycle(HashesVectorGraph& graph,
                                        std::map<std::set<long>, bool>& visited_edges,
                                        long start_node_index)
{
  hierholzerResult return_value;
  return_value.has_cycle = true;
  return_value.cycle.push_back(start_node_index);

  long current_index = start_node_index;
  do 
  {
    // Checando se existe adjacência ainda não testada para esse vertice
    bool none_found = true;
    for (long i : graph.vizinhos(current_index))
    {
      if (visited_edges[{current_index, i}] == false)
      {
        none_found = false;
        visited_edges[{current_index, i}] = true;
        current_index = i;
        // Concatenando ao final do caminho do ciclo
        return_value.cycle.push_back(i);
        break;
      }
    }
    if (none_found) {
      return_value.has_cycle = false;
      return return_value;
    }
  } 
  while (current_index != start_node_index);

  std::vector<long> cycle_untill_here;
  hierholzerResult subcicle_return_value;

  for (long i : return_value.cycle)
  {
    cycle_untill_here.push_back(i);
    for (long j: graph.vizinhos(i))
    {
      if (visited_edges[{i, j}] == false)
      {
        subcicle_return_value = searchEulerianSubcycle(graph, visited_edges, i);
        if (subcicle_return_value.has_cycle == false)
        {
          // Constitui ausencia de ciclo Euleriano
          return subcicle_return_value;
        }
        // Ignora o primeiro elemento do subciclo (para não haver repetição)
        cycle_untill_here.insert(cycle_untill_here.end(),
                                 subcicle_return_value.cycle.begin() + 1,
                                 subcicle_return_value.cycle.end());
      }
    }
  }
  return_value.cycle = cycle_untill_here;
  return return_value;
}

hierholzerResult hierholzer(HashesVectorGraph& graph)
{
  std::map<std::set<long>, bool> visited_edges;
  long start_node_index;
  // Correcao do VPL espera que eu comece do vertice 1
  start_node_index = 1;

  // TODO file agnotisc
  for (long i = 1; i <= graph.qtdVertices(); i++)
  {
    for (long j: graph.vizinhos(i))
    {
      visited_edges[{i, j}] = false;
    }
  }
  hierholzerResult result;
  result = searchEulerianSubcycle(graph, visited_edges, start_node_index);


  // Checando se há componente desconexa
  for (const auto& i : visited_edges)
  {
    if (i.second == false)
    {
      result = {false, {}};
    }
  }
  prettyPrintingHierholzer(result);
  return result;
}

