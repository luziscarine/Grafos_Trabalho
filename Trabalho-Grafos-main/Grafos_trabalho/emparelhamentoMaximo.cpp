#include "Graph.h"
#include <vector>
#include <iostream>
#include <tuple>

std::vector<int> U = {1, 2, 3, 4, 5}; // Conjunto U
std::vector<int> V = {6, 7, 8, 9, 10}; // Conjunto V

// Emparelhamento máximo 
bool Graph::bpm(int u, std::vector<bool>& seen, std::vector<int>& matchR, std::vector<std::tuple<int, int>>& matchingEdges) {
    for (const auto& edge : edges) {
        int u_index = std::get<0>(edge) - 1;
        int v_index = std::get<1>(edge) - 1;

        // Verificar se a aresta conecta um vértice de U a um vértice de V
        if ((std::find(U.begin(), U.end(), u_index + 1) != U.end()) && (std::find(V.begin(), V.end(), v_index + 1) != V.end())) {
            int v = v_index - U.size(); // Ajustar índice de V para 0-base em V

            if (!seen[v]) {
                seen[v] = true;
                if (matchR[v] == -1 || bpm(matchR[v], seen, matchR, matchingEdges)) {
                    matchR[v] = u;
                    matchingEdges.emplace_back(u_index + 1, v_index + 1); // Guardar a aresta usada no emparelhamento
                    return true;
                }
            }
        }
    }
    return false;
}

int Graph::maxBipartiteMatching() {
    std::vector<int> matchR(vertices.size(), -1);
    std::vector<std::tuple<int, int>> matchingEdges; // Vector para armazenar as arestas usadas no emparelhamento
    int result = 0;

    for (int u_index = 0; u_index < U.size(); u_index++) { // Iterar sobre os vértices do conjunto U
        std::vector<bool> seen(vertices.size(), false);
        if (bpm(u_index, seen, matchR, matchingEdges)) { // Ajustar índice para 0-base
            result++;
        }
    }

    // Exibir as arestas usadas no emparelhamento máximo
    std::cout << "Arestas do emparelhamento máximo:" << std::endl;
    for (const auto& edge : matchingEdges) {
        std::cout << std::get<0>(edge) << " -- " << std::get<1>(edge) << std::endl;
    }

    return result;
}
