#include "Graph.h"
#include <tuple>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <limits.h>
#include <numeric>

using namespace std;

Graph::Graph(std::vector<int> v, std::vector<std::tuple<int, int, int>> e, bool bi) : bidirectional(bi), colors(v.size(), -1) {
    // Copia os vértices e os organiza
    vertices = v;
    std::sort(vertices.begin(), vertices.end());

    // Copia as arestas
    edges = e;
    std::sort(edges.begin(), edges.end());
}

void Graph::printMatrix() {
    int n = vertices.size();
    // Cria a matriz
    int **matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    // Inicializa com 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    // Dá valores à matriz
    for (int k = 0; k < edges.size(); k++) {
        int u = std::get<0>(edges[k]) - 1;
        int v = std::get<1>(edges[k]) - 1;
        int weight = std::get<2>(edges[k]);

        matrix[u][v] = weight;

        if (bidirectional) {
            matrix[v][u] = weight;
        }
    }

    // Imprime a matriz
    std::cout << "Matriz de adjacencias:\n  ";
    for (int i = 0; i < n; i++) {
        std::cout << vertices[i] << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < n; i++) {
        std::cout << vertices[i] << " ";
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Deleta a matriz
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Graph::printList() {
    // Inicia o vetor
    std::vector<std::list<std::pair<int, int>>> adj(vertices.size());

    // Preenche a lista
    for (int i = 0; i < edges.size(); i++) {
        int u = std::get<0>(edges[i]) - 1;
        int v = std::get<1>(edges[i]) - 1;
        int weight = std::get<2>(edges[i]);

        adj[u].push_back({v + 1, weight});
        if (bidirectional) {
            adj[v].push_back({u + 1, weight});
        }
    }

    // Imprime a lista
    std::cout << "Lista de adjacencias:\n";
    for (int i = 0; i < vertices.size(); i++) {
        std::cout << vertices[i] << ": ";
        for (auto it = adj[i].begin(); it != adj[i].end(); it++) {
            std::cout << "(" << it->first << ", " << it->second << ") ";
        }
        std::cout << "\n";
    }
}


