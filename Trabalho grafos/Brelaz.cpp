#include "Graph.h"
#include <unordered_set>
#include <iostream>

// Implementação do algoritimo de Brelaz -> coloração de Grafos 
int Graph::getDegree(int vertex) {
    int degree = 0;
    for (const auto& edge : edges) {
        if (std::get<0>(edge) == vertex || std::get<1>(edge) == vertex) {
            degree++;
        }
    }
    return degree;
}

int Graph::getSaturationDegree(int vertex, const std::vector<int>& vertexColors) {
    std::unordered_set<int> neighborColors;
    for (const auto& edge : edges) {
        if (std::get<0>(edge) == vertex && vertexColors[std::get<1>(edge) - 1] != -1) {
            neighborColors.insert(vertexColors[std::get<1>(edge) - 1]);
        }
        if (std::get<1>(edge) == vertex && vertexColors[std::get<0>(edge) - 1] != -1) {
            neighborColors.insert(vertexColors[std::get<0>(edge) - 1]);
        }
    }
    return neighborColors.size();
}

int Graph::selectVertex(const std::vector<int>& vertexColors, const std::vector<int>& saturationDegree, const std::vector<int>& remainingDegree) {
    int maxSaturation = -1;
    int minRemainingDegree = vertices.size() + 1;
    int selectedVertex = -1;

    for (int i = 0; i < vertices.size(); i++) {
        if (vertexColors[i] == -1) {
            if (saturationDegree[i] > maxSaturation || (saturationDegree[i] == maxSaturation && remainingDegree[i] < minRemainingDegree)) {
                maxSaturation = saturationDegree[i];
                minRemainingDegree = remainingDegree[i];
                selectedVertex = i;
            }
        }
    }

    return selectedVertex;
}

bool Graph::isColorValid(int vertex, int color, const std::vector<int>& vertexColors) {
    for (const auto& edge : edges) {
        if ((std::get<0>(edge) == vertex + 1 && vertexColors[std::get<1>(edge) - 1] == color) ||
            (std::get<1>(edge) == vertex + 1 && vertexColors[std::get<0>(edge) - 1] == color)) {
            return false;
        }
    }
    return true;
}

void Graph::brelazColoring() {
    std::vector<int> vertexColors(vertices.size(), -1);
    std::vector<int> saturationDegree(vertices.size(), 0);
    std::vector<int> remainingDegree(vertices.size());

    for (int i = 0; i < vertices.size(); i++) {
        remainingDegree[i] = getDegree(vertices[i]);
    }

    int coloredVertices = 0;

    while (coloredVertices < vertices.size()) {
        int vertex = selectVertex(vertexColors, saturationDegree, remainingDegree);
        int color = 0;

        while (!isColorValid(vertex, color, vertexColors)) {
            color++;
        }

        vertexColors[vertex] = color;
        colors[vertex] = color;

        for (const auto& edge : edges) {
            if (std::get<0>(edge) == vertex + 1 || std::get<1>(edge) == vertex + 1) {
                int neighbor = (std::get<0>(edge) == vertex + 1) ? std::get<1>(edge) - 1 : std::get<0>(edge) - 1;
                if (vertexColors[neighbor] == -1) {
                    saturationDegree[neighbor]++;
                }
            }
        }

        remainingDegree[vertex] = -1;
        coloredVertices++;
    }
}

void Graph::printColors() {
    std::cout << "Cores para cada vertice:\n";
    for (int i = 0; i < vertices.size(); i++) {
        std::cout << "Vertex " << vertices[i] << ": Color " << colors[i] << "\n";
    }
}