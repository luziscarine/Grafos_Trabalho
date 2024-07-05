#include "Graph.h"
#include <queue>
#include <limits.h>
#include <iostream>

// Algoritmo de busca por profundidade -> Ford-Fulkerson
bool Graph::bfs(std::vector<std::vector<int>>& residualGraph, int s, int t, std::vector<int>& parent) {
    std::vector<bool> visited(vertices.size(), false);
    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < vertices.size(); v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}

int Graph::fordFulkerson(int s, int t) {
    int V = vertices.size();

    // Criar grafo residual e inicializar com as capacidades
    std::vector<std::vector<int>> residualGraph(V, std::vector<int>(V, 0));
    for (const auto& edge : edges) {
        int u = std::get<0>(edge) - 1;
        int v = std::get<1>(edge) - 1;
        int capacity = std::get<2>(edge);
        residualGraph[u][v] = capacity;
        if (bidirectional) {
            residualGraph[v][u] = capacity;
        }
    }

    std::vector<int> parent(V);
    int maxFlow = 0;

    // Vetor para armazenar as arestas usadas no caminho aumentante
    std::vector<std::tuple<int, int>> pathEdges;

    while (bfs(residualGraph, s, t, parent)) {
        int pathFlow = INT_MAX;

        // Encontrar o fluxo máximo no caminho encontrado pela BFS
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, residualGraph[u][v]);
            pathEdges.emplace_back(u + 1, v + 1); // Armazenar a aresta usada no caminho
        }

        // Atualizar as capacidades residuais do caminho encontrado
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    // Exibir as arestas usadas no caminho aumentante
    std::cout << "Arestas no caminho aumentante:" << std::endl;
    for (const auto& edge : pathEdges) {
        std::cout << std::get<0>(edge) << " -- " << std::get<1>(edge) << std::endl;
    }

    return maxFlow;
}
