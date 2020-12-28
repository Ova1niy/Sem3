#pragma once

#include "dynamic_array.h"
#include "list_for_pairs.h"
#include<iostream>


// Неориентированный граф
class Graph {
private:
    LinkedList<int, float>* adjacency; // вместо float может быть T но мне лень писать <T>
    int size;
    int used_colors;
    DynamicArray<int>* node_colors;
private:
    DynamicArray<int>* GetNeighborsColors(unsigned index);
    void Connect(unsigned a, unsigned b, float weight);
    void PaintGraph();
public:
    Graph(unsigned n);
    Graph(float (*matr)[5], int n);
    DynamicArray<int>* GetColors() { return node_colors; };
    void Print();
};

Graph::Graph(unsigned int n) {
    size = n;
    adjacency = new LinkedList<int, float> [n];
    used_colors = 0;
    node_colors = new DynamicArray<int>(n);
    int to;
    float weight;
    for (int i = 0; i < n; ++i) {
        std::cout << "Укажите соседей " << i << " и вес соединения (через пробел)\n"
                                                "чтобы закончить введите -1 0\n";
        while (true) {
            std::cin >> to >> weight;
            if (to == -1)
                break;
            Connect(i, to, weight);
        }
        node_colors->Set(i, -1);
    }
    PaintGraph();
}

Graph::Graph(float (*matr)[5], int n) {
    size = n;
    adjacency = new LinkedList<int, float> [n];
    used_colors = 0;
    node_colors = new DynamicArray<int>(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            if (matr[i][j] != 0)
                Connect(i, j, matr[i][j]);
        node_colors->Set(i, -1);
    }
    PaintGraph();
}


void Graph::Connect(unsigned int a, unsigned int b, float weight) {
    adjacency[a].Add(b, weight);
    adjacency[b].Add(a, weight);
}

void Graph::PaintGraph() {
    for (int i = 0; i < size; ++i) {
        DynamicArray<int>* pallet = GetNeighborsColors(i);
        int pallet_size = pallet->GetSize();
        if (used_colors > pallet_size) {
            bool* checker = new bool [used_colors];
            for (int a = 0; a < used_colors; ++a)
                checker[a] = false;
            for (int color_num = 0; color_num < pallet_size; ++color_num)
                checker[pallet->Get(color_num) - 1] = true;
            for (int color = 0; color < used_colors; ++color) {
                if (!checker[color]) {
                    node_colors->Set(i, color+1);
                }
            }
        } else {
            ++used_colors;
            node_colors->Set(i, used_colors);
        }
    }
}

DynamicArray<int> *Graph::GetNeighborsColors(unsigned int index) {
    DynamicArray<int>* res = new DynamicArray<int>();
    for (int i = 0; i < adjacency[index].GetSize(); ++i) {
        int color = node_colors->Get(adjacency[index].GetPairByIndex(i).first);
        if (color != -1)
            res->Prepend(color);
    }
    return res;
}

void Graph::Print() {
    std::cout << size << "\n";
    for (int node = 0; node < size; ++node) {
        std::cout << node << ": ";
        adjacency[node].Print();
    }
}