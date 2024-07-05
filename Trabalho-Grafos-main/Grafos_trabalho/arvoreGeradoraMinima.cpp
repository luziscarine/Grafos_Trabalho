#include "Graph.h"
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void Graph::prim() {
    vector<bool> visited(vertices.size(), false);
    vector<int> parent(vertices.size(), -1);
    vector<int> key(vertices.size(), numeric_limits<int>::max());

    key[0] = 0;

    for (int i = 0; i < vertices.size(); i++) {
        int minKey = numeric_limits<int>::max();
        int u = -1;

        for (int j = 0; j < vertices.size(); j++) {
            if (!visited[j] && key[j] < minKey) {
                minKey = key[j];
                u = j;
            }
        }

        if (u == -1) break; // Se não houver vértices não visitados, saia do loop.

        visited[u] = true;

        for (int v = 0; v < vertices.size(); v++) {
            int weight = getEdgeWeight(vertices[u], vertices[v]);
            if (!visited[v] && weight != 0 && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    cout << "Arvore geradora minima:" << endl;
    for (int i = 1; i < vertices.size(); i++) {
        if (parent[i] != -1) { // Verifica se o vértice faz parte da MST
            cout << vertices[parent[i]] << " -> " << vertices[i] << " : " << getEdgeWeight(vertices[parent[i]], vertices[i]) << endl;
        }
    }
}

int Graph::getEdgeWeight(int u, int v) {
    for (const auto& edge : edges) {
        if ((std::get<0>(edge) == u && std::get<1>(edge) == v) || 
            (std::get<0>(edge) == v && std::get<1>(edge) == u)) {
            return std::get<2>(edge);
        }
    }
    return 0; // Retorna 0 se não houver aresta entre u e v
}
