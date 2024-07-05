#include "Graph.h"
#include <tuple>
#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>
#include "stdlib.h"
#include "stdio.h"

using namespace std;

void printMenu() {
    std::cout << "===== Menu =====\n";
    std::cout << "1. Imprimir Matriz de Adjacencia\n";
    std::cout << "2. Imprimir Lista de Adjacencia\n";
    std::cout << "3. Coloracao de Grafos (Algoritmo de Brelaz)\n";
    std::cout << "4. Imprimir Arvore Geradora Minima (Algoritmo de Prim)\n";
    std::cout << "5. Calcular Fluxo Maximo (FordFulkerson)\n";
    std::cout << "6. Calcular Emparelhamento Maximo (Grafo Bipartido)\n";
    std::cout << "7. Sair\n";
    std::cout << "Escolha uma opcao: ";
}

int main() {
    vector<int> vertices = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<tuple<int, int, int>> arestas = {
        {1, 2, 5}, {1, 3, 8}, {1, 4, 3},
        {2, 3, 6}, {2, 5, 9}, {3, 4, 2},
        {3, 6, 7}, {4, 7, 4}, {5, 6, 1},
        {5, 8, 5}, {6, 9, 3}, {7, 8, 2},
        {7, 10, 6}, {8, 9, 4}, {9, 10, 7}
    };

    Graph teste(vertices, arestas);
    int op = 0;
    system("cls");

    do {
        printMenu();
        std::cin >> op;
        system("cls");

        // Limpa o buffer de entrada para evitar erros de leitura.
        std::cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (op) {
            case 1:
                std::cout << "\nMatriz de Adjacencia:\n";
                teste.printMatrix();
                std::cout << "\n";
                break;
            case 2:
                std::cout << "\nLista de Adjacencia:\n";
                teste.printList();
                std::cout << "\n";
                break;
            case 3:
                std::cout << "\nColoracao de Grafos (Algoritmo de Brelaz):\n";
                teste.brelazColoring();
                teste.printColors();
                std::cout << "\n";
                break;
            case 4:
                std::cout << "\nImprimir Arvore Geradora Minima (Algoritmo de Prim):\n";
                teste.prim();
                std::cout << "\n";
                break;
            case 5:
                {
                    std::cout << "\nCalcular Fluxo Maximo (Ford-Fulkerson):\n";
                    int source, sink;
                    std::cout << "Digite o vertice de origem: ";
                    std::cin >> source;
                    std::cout << "Digite o vertice de destino: ";
                    std::cin >> sink;
                    if (source >= 1 && source <= vertices.size() && sink >= 1 && sink <= vertices.size()) {
                        int maxFlow = teste.fordFulkerson(source - 1, sink - 1);
                        std::cout << "O fluxo maximo de " << source << " para " << sink << " e " << maxFlow << "\n\n";
                    } else {
                        std::cout << "Vertices invalidos.\n\n";
                    }
                }
                break;
            case 6:
                {
                    std::cout << "\nCalcular Emparelhamento Maximo (Grafo Bipartido):\n";
                    int maxMatching = teste.maxBipartiteMatching();
                    std::cout << "O emparelhamento maximo e " << maxMatching << "\n\n";
                }
                break;
            case 7:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opção invalida. Tente novamente.\n\n";
                break;
        }
    } while (op != 7);

    return 0;
}
