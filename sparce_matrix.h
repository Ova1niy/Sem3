#pragma once

#include "idictionary.h"
#include "hash_table.h"
#include "dynamic_array.h"

#include<iostream>

template <class T>
using TPair = Pair<T,T>;

int HashPairDef(Pair<int, int> p)
{
    std::size_t h1 = std::hash<int>{}(p.first);
    std::size_t h2 = std::hash<int>{}(p.second);
    return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
}

unsigned const DEFAULT_SIZE = 1000;

template<typename T>
class SparceMatrix {
private:
    IDictionary<Pair<int, int>, T>* values;
    DynamicArray<Pair<int, int>>* coordinates;
    unsigned m;
    unsigned n;
public:
    SparceMatrix(){
        m = DEFAULT_SIZE;
        n = DEFAULT_SIZE;
        values = new IDictionary<Pair<int, int>, T>(HashPairDef);
        coordinates = new DynamicArray<Pair<int, int>>();
    }
    SparceMatrix(DynamicArray<Pair<Pair<int, int>, T>>* v, int m_ = DEFAULT_SIZE,
                 int n_ = DEFAULT_SIZE){
        m = DEFAULT_SIZE;
        n = DEFAULT_SIZE;
        coordinates = new DynamicArray<Pair<int, int>>();
        values = new IDictionary<Pair<int, int>, T>(HashPairDef);
        for (int i = 0; i < v->GetSize(); ++i) {
            auto tmp = v->Get(i);
            values->Add(tmp.first, tmp.second);
            coordinates->Prepend(tmp.first);
        }
    }
    void Print() {
        for (int i = 0; i < coordinates->GetSize(); ++i) {
            Pair<int, int>coord = coordinates->Get(i);
            T value = Get(coord);
            std::cout << "(" << coord.first << "," << coord.second << ") " << value << " ";
        }
    }
    T Get(Pair<int, int> coords) {
        if (values->ContainsKey(coords)) {
            return values->Get(coords);
        }
        return 0;
    }
    void Add(Pair<int, int> coords, T value) {
        coordinates->Prepend(coords);
        values->Add(coords, value);
    }
    SparceMatrix<T>* operator+=(SparceMatrix<T>& matrix) {
        for (int i = 0; i < matrix.coordinates->GetSize(); ++i) {
            Pair<int, int>coord = matrix.coordinates->Get(i);
            T value = this->Get(matrix.coordinates->Get(i));
            if (value == 0) {
                this->Add(coord, matrix.values->Get(coord));
            } else {
                if (value + matrix.values->Get(coord) == 0) {
                    this->values->Remove(coord);
                } else {
                    this->Add(coord, value + matrix.values->Get(coord));
                }
            }
        }
        return this;
    }
    SparceMatrix<T>* operator-=(SparceMatrix<T>& matrix) {
        for (int i = 0; i < matrix.coordinates->GetSize(); ++i) {
            Pair<int, int>coord = matrix.coordinates->Get(i);
            T value = this->Get(matrix.coordinates->Get(i));
            if (value == 0) {
                this->Add(coord, matrix.values->Get(coord));
            } else {
                if (value - matrix.values->Get(coord) == 0) {
                    this->values->Remove(coord);
                } else {
                    this->Add(coord, value - matrix.values->Get(coord));
                }
            }
        }
        return this;
    }
};
