#pragma once

#include "idictionary.h"
#include "dynamic_array.h"
#include <iostream>
#include <functional>

template<class T>
struct Range {
    T first;
    T second;
    Range() : first(), second() {}
    explicit Range(T v) : first(v), second(v) {}
    Range(T f, T s) {
        if (f < s) {
            first = f;
            second = s;
        } else {
            first = s;
            second = f;
        }
    }
    bool IsValue() const { return first==second; }
    bool Contains(T v) {
        if (IsValue()) {
            return first==v;
        } else {
            return ((first <= v) && (v <= second));
        }
    }

    friend bool operator==(const Range<T>& l, const Range<T>& r) {
        return l.first == r.first && l.second == r.second;
    }
};

template<class T>
std::ostream& operator<< (std::ostream& os, const Range<T>& r) {
    if (r.IsValue()) {
        os << r.first;

    } else {
        os << "(" << r.first << "," << r.second << ")";
    }
    return os;
}

template <class T>
struct HashRangeDef
{
    using TRange = Range<T>;
    int operator()(TRange r) const
    {
        if (r.IsValue()) {
            return std::hash<T>{}(r.first);
        } else {
            std::size_t h1 = std::hash<T>{}(r.first);
            std::size_t h2 = std::hash<T>{}(r.second);
            return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
        }
    }
};

template<class TParam, class TObject>
class Histogram {
private:
    using TRange = Range<TParam>;
    IDictionary<TRange, int>* set;
    DynamicArray<TRange>* ranges;
    DynamicArray<TParam>* parameters;
private:
    std::function<TParam(TObject)>GetParam;
    Range<TParam> GetRange(TParam v);
    void Split();
public:
    Histogram(std::function<TParam(TObject)>gp,
              DynamicArray<TObject>* objects,
              DynamicArray<TRange>* r,
              std::function<int(TRange)>hash = HashRangeDef<TParam>());
    IDictionary<TRange, int>*Get() { return set; }
    void Print();
};

template<class TParam, class TObject>
Histogram<TParam, TObject>::Histogram(std::function<TParam(TObject)> gp, DynamicArray<TObject> *objects,
                                      DynamicArray<TRange> *r, std::function<int(TRange)> hash) {
    set = new IDictionary<Range<TParam>, int>(hash);
    ranges = r;
    GetParam = gp;
    ranges->Prepend(TRange());
    for (int i = 0; i < ranges->GetSize(); ++i) {
//        std::cout << ranges->Get(i) << "\n";
//        std::cout << "Privet 4u4a!\n";
        set->Add(ranges->Get(i), 0);
    };
//    std::cout << "AAAAAA!\n";

    parameters = new DynamicArray<TParam>();
    for (int i = 0; i < objects->GetSize(); ++i)
        parameters->Prepend(GetParam(objects->Get(i)));
    Split();
}

template<class TParam, class TObject>
void Histogram<TParam, TObject>::Split() {
    for(int i = 0; i < parameters->GetSize(); ++i) {
        Range<TParam> range = GetRange(parameters->Get(i));
//        std::cout << "par: " << parameters->Get(i) << " => added " << range << " in the set\n";
        set->Add(range, ++(set->Get(range)));
    }
}

template<class TParam, class TObject>
Range<TParam> Histogram<TParam, TObject>::GetRange(TParam v) {
    for (int i = 0; i < ranges->GetSize(); ++i) {
        Range<TParam> range = ranges->Get(i);
        if (range.Contains(v))
            return range;
    }
    return Range<TParam>(); // другое
}

template<class TParam, class TObject>
void Histogram<TParam, TObject>::Print() {
    for (int i = 0; i < ranges->GetSize() - 1; ++i) {
        Range<TParam> range = ranges->Get(i);
        std::cout << range << ":" << set->Get(range) << "\n";
    }
    int count = set->Get(ranges->Get(ranges->GetSize() - 1));
    if (count != 0) {
        std::cout << "Other:" << count << "\n";
    }
}
