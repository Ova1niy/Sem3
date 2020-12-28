#include <iostream>
#include "list_for_pairs.h"
#include "graph.h"


int main() {
    system("chcp 65001");
    std::cout << "Введите количество вершин графа: ";
    int n;
    std::cin >> n;
    Graph* g = new Graph(n);
    g->Print();
    std::cout << "\n";
    DynamicArray<int>* colors = g->GetColors();
    for (int i = 0; i < colors->GetSize(); ++i) {
        std::cout << i << ":" << char(colors->Get(i) + 64) << "\n";
    }
    return 0;
}


