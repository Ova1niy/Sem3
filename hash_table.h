#pragma once

#include <iostream>
#include "list_for_pairs.h"
#include <functional>


template <class T>
struct HashFunction
{
    int operator()(T value) const
    {
        return std::hash<T>{}(value);
    }
};

template<class TKey, class TElement>
class HashTable {
private:
    LinkedList<TKey, TElement>* arr;
    std::function<int(TKey)> Hash;
    static const int default_capacity = 11; // начальный размер нашей таблицы
    constexpr static const double rehash_size = 0.75;
    unsigned count;
    unsigned capacity;

public:
    explicit HashTable(std::function<int(TKey)> F = HashFunction<TKey>());
    ~HashTable() = default;
    unsigned GetCount() { return count; }
    unsigned GetCapacity() { return capacity; }
    void Resize(bool more);
    bool ContainsKey(TKey key);
    TElement& Get(TKey key);
    void Remove(TKey key);
    void Add(TKey key, TElement elem);
    void Print();
    void CondomPrint();
};

template<class TKey, class TElement>
HashTable<TKey, TElement>::HashTable(std::function<int(TKey)> F) {
    count = 0;
    capacity = default_capacity;
    Hash = F;
    arr = new LinkedList<TKey, TElement> [capacity];
}

template<class TKey, class TElement>
void HashTable<TKey, TElement>::Resize(bool more) {
    unsigned old_capacity = capacity;
    if (more) {
        capacity *= 2;
    } else {
        capacity /= 2;
    }
    LinkedList<TKey, TElement>* arr2 = new LinkedList<TKey, TElement> [capacity];
    std::swap(arr, arr2);
    count = 0;
    for (int i = 0; i < old_capacity; ++i) {
        for (int j = 0; j < arr2[i].GetSize(); ++j) {
            Pair<TKey, TElement> pair = arr2[i].GetPairByIndex(j);
            Add(pair.first, pair.second);
        }
    }
}

template<class TKey, class TElement>
bool HashTable<TKey, TElement>::ContainsKey(TKey key) {
    int h = Hash(key) % capacity;
    return arr[h].ContainsKey(key);
}

template<class TKey, class TElement>
TElement& HashTable<TKey, TElement>::Get(TKey key) {
    int h = Hash(key) % capacity;
    return arr[h].GetByKey(key);
}

template<class TKey, class TElement>
void HashTable<TKey, TElement>::Remove(TKey key) {
    if (count < capacity/2)
        Resize(false);
    int h = Hash(key) % capacity;
    arr[h].Remove(key);
    --count;
}

template<class TKey, class TElement>
void HashTable<TKey, TElement>::Add(TKey key, TElement elem) {
    if (count + 1 > capacity * rehash_size)
        Resize(true);
    int h = Hash(key) % capacity;
    int c = arr[h].GetSize();
//    std::cout << "ya v HT add\n";
    arr[h].Add(key, elem);
    if (c + 1 == arr[h].GetSize()) {
        ++count;
    }
}

template<class TKey, class TElement>
void HashTable<TKey, TElement>::Print() {
    for (int i = 0; i < capacity; ++i) {
        std::cout << "[" << i << "]:";
        arr[i].Print();
    }
    std::cout << "\n";
}

template<class TKey, class TElement>
void HashTable<TKey, TElement>::CondomPrint() {
    for (int i = 0; i < capacity; ++i) {
//        std::cout << "[" << i << "]:";
        if(arr[i].GetSize() > 0)
            arr[i].Print();
    }
    std::cout << "\n";
}

