#include "Graph.h"
#include <vector>

// Emparelhamento máximo 
bool Graph::bpm(int u, std::vector<bool>& seen, std::vector<int>& matchR) {
    for (const auto& edge : edges) {
        int v = std::get<1>(edge) - 1;

        if (!seen[v] && (matchR[v] == -1 || bpm(matchR[v], seen, matchR))) {
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

int Graph::maxBipartiteMatching() {
    std::vector<int> matchR(vertices.size(), -1);
    int result = 0;

    for (int u = 0; u < vertices.size(); u++) {
        std::vector<bool> seen(vertices.size(), false);
        if (bpm(u, seen, matchR)) {
            result++;
        }
    }

    return result;
}
