#pragma once

#include "hash_table.h"
#include <functional>


template<class TKey, class TElement>
class IDictionary {
private:
    HashTable<TKey, TElement>* table;
public:
    explicit IDictionary(std::function<int(TKey)> F = HashFunction<TKey>()) {
        table = new HashTable<TKey, TElement>(F);
    }
    ~IDictionary() = default;
    unsigned GetCount() { return table->GetCount(); }
    unsigned GetCapacity() { return table->GetCapacity(); }
    TElement& Get(TKey key) { return table->Get(key); }
    bool ContainsKey(TKey key) { return table->ContainsKey(key); }
    void Add(TKey key, TElement element) { table->Add(key, element); };
    void Remove(TKey key) { table->Remove(key); }
    void HashPrint() { table->Print(); }
};