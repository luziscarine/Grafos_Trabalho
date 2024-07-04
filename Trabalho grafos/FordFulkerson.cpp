#include "Graph.h"
#include <queue>
#include <limits.h>

// Algoritimo de busca por profundidade -> Ford Furkson
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
    int u, v;
    int V = vertices.size();

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

    while (bfs(residualGraph, s, t, parent)) {
        int pathFlow = INT_MAX;

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            pathFlow = std::min(pathFlow, residualGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}