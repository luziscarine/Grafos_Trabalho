#ifndef GRAPH_H
#define GRAPH_H

#include <tuple>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <limits.h>

class Graph {
private:
    std::vector<int> vertices;
    std::vector<std::tuple<int, int, int>> edges;
    bool bidirectional;

    // Implementação do algoritimo de Brelaz -> coloração de Grafos 
    std::vector<int> colors;
    int getDegree(int vertex);
    int getSaturationDegree(int vertex, const std::vector<int>& vertexColors);
    int selectVertex(const std::vector<int>& vertexColors, const std::vector<int>& saturationDegree, const std::vector<int>& remainingDegree);
    bool isColorValid(int vertex, int color, const std::vector<int>& vertexColors);
    bool bfs(std::vector<std::vector<int>>& residualGraph, int s, int t, std::vector<int>& parent);
    bool bpm(int u, std::vector<bool>& seen, std::vector<int>& matchR, std::vector<std::tuple<int, int>>& matchingEdges);

public:
    Graph(std::vector<int> v, std::vector<std::tuple<int, int, int>> e, bool bi = true);
    void printMatrix();
    void printList();
    void prim();
    int getEdgeWeight(int u, int v);
    void brelazColoring();
    void printColors();
    int fordFulkerson(int s, int t);
    int maxBipartiteMatching();
};

#endif