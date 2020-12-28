#pragma once

#include <stdexcept>

template<class T>
class DynamicArray {
private:
    T* head;
    unsigned size;
    unsigned capacity;
    unsigned const BUFFER_SIZE = 10;
private:
    int BufferCount (int s) {
        int i = 1;
        for (; s > BUFFER_SIZE * i; ++i) {}
        return i;
    }
public:
    DynamicArray();
    explicit DynamicArray(unsigned count);
    ~DynamicArray() { delete head; head = nullptr; }
    unsigned GetSize() { return size; }
    T& Get(unsigned index);
    void Set(unsigned index, T value);
    bool Contains(T value);
    void Prepend(T value);
};

template<class T>
DynamicArray<T>::DynamicArray() {
    head = new T [BUFFER_SIZE];
    size = 0;
    capacity = BUFFER_SIZE;
}

template<class T>
DynamicArray<T>::DynamicArray(unsigned count) {
    size = count;
    capacity = BufferCount(count);
    head = new T [capacity];
}

template<class T>
T& DynamicArray<T>::Get(unsigned index) {
    if (index >= size)
        std::out_of_range("Index out of range");
    return head[index];
}

template<class T>
void DynamicArray<T>::Set(unsigned index, T value) {
    if (index >= size)
        std::out_of_range("Index out of range");
    head[index] = value;
}

template<class T>
void DynamicArray<T>::Prepend(T value) {
    if (BufferCount(size) != BufferCount(size + 1)) {
        ++size;
        capacity += BUFFER_SIZE;
        T* n_head = new T [capacity];
        for (int i = 0; i < size - 1; ++i) {
            n_head[i] = head[i];
        }
        n_head[size] = value;
        delete head;
        head = n_head;
    } else {
        head[size] = value;
        ++size;
    }
}

template<class T>
bool DynamicArray<T>::Contains(T value) {
    for (int i = 0; i < size; ++i) {
        if (head[i] == value)
            return true;
    }
    return false;
}
