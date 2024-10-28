#include "Floyd-Warshall.hpp"


void prettyPrintingFloydWarshall(floydWarshallResult& fwr)
{
  for (long i = 1; i < fwr.cost.size(); i++)
  {
    std::cout << i << ":";
    for (long j = 1; j < fwr.cost.size(); j++)
    {
      // Se for a última coluna
      if (j == fwr.cost.size() - 1)
      {
        std::cout << fwr.cost[i][j];
      }
      else
      {
        std::cout << fwr.cost[i][j] << ",";
      }
    }
    std::cout << std::endl;
  }
}

floydWarshallResult floydWarshall(HashesVectorGraph& graph)
{
  // Vou desperdiçar o espaço da posição 0 para não complicar a lógica, nos
  // vetores internos também
  std::vector<std::vector<double>> cost(graph.qtdVertices() + 1);
  std::vector<std::vector<long>> predecessors(graph.qtdVertices() + 1);

  // Inicializando
  for (long i = 1; i < graph.qtdVertices() + 1; i++)
  {
    // IMPORTANTE preenchendo as posições que não serão usadas
    cost[i].resize(graph.qtdVertices() + 1);
    cost[i][0] = 0;
    predecessors[i].resize(graph.qtdVertices() + 1);
    predecessors[i][0] = 0;

    for (long j = 1; j < graph.qtdVertices() + 1; j++)
    {
      if (graph.haAresta(i, j))
      {
        predecessors[i][j] = i;
        cost[i][j] = graph.peso(i, j);
      }
      else if (i == j)
      {
        cost[i][j] = 0;
        // 0 quando volta para ele mesmo e -1 para quando não há caminho
        predecessors[i][j] = 0;
      }
      else
      {
        // Está retornando std::numeric_limits::max()
        cost[i][j] = graph.peso(i, j);
        predecessors[i][j] = -1;
      }
    }
  }

  // Esse algoritmo parece simples, mas acho a ideia por trás dele não trivial
  // Todo par de vértices que tiver um k entre eles vai ser descoberto
  // Como k deve iterar por todos os vértices, eventualmente até mesmo a
  // pior transitividade possível, a que passa por todos os vértices no
  // meio, terá sido explorada. Notando que as transitividades marcadas em um
  // percurso vão sendo salvas na matriz e sendo usadas para os posteriores
  for(long k = 1; k < cost.size(); k++)
  {
    for(long i = 1; i < cost.size(); i++)
    {
      for (long j = 1; j < cost.size(); j++)
      {
        if (cost[i][j] > cost[i][k] + cost[k][j])
        {
          predecessors[i][j] = k; // TODO talvez esteja errado
          cost[i][j] = cost[i][k] + cost[k][j];
        }
      }
    }
  }

  floydWarshallResult fwr{cost, predecessors};
  prettyPrintingFloydWarshall(fwr);
  return fwr;
}

