#pragma once
#include <stdexcept>
#include <string>

// это список, который будет использоваться в хэш таблице

template<class TKey, class TElement>
struct Pair {
    TKey first;
    TElement second;

    Pair() : first(), second() {}
    Pair(TKey f, TElement s) : first(f), second(s) {}
    ~Pair() = default;

    bool operator==(Pair<TKey, TElement>& r) {
        return (this->first == r.first && this->second == r.second);
    }
};

template<class TKey, class TElement>
class LinkedList {
private:
    struct Node {
        Pair<TKey, TElement> data;
        Node* next;

        Node() : data(), next(nullptr) {}
        Node(TKey k, TElement e)  : data(k, e), next(nullptr) {}
        ~Node() = default;
    };
private:
    // Поля
    Node* head;
    unsigned size;

public:
    LinkedList();
    ~LinkedList();
    bool ContainsKey(TKey key);
    TElement& GetByKey(TKey key);
    Pair<TKey, TElement> GetPairByIndex(unsigned index);
    void Add(TKey key, TElement elem);
    void Remove(TKey key);
    unsigned GetSize() { return size; };
    void Print();
};

template<class TKey, class TElement>
LinkedList<TKey, TElement>::LinkedList() {
    head = nullptr;
    size = 0;
}

template<class TKey, class TElement>
LinkedList<TKey, TElement>::~LinkedList() {
    if (head != nullptr) {
        Node *q = head;
        Node *del = q;
        while (q != nullptr) {
            q = q->next;
            delete (del);
            del = q;
        }
    }
}

template<class TKey, class TElement>
bool LinkedList<TKey, TElement>::ContainsKey(TKey key) {
    if (head == nullptr)
        return false;
    Node* q = head;
    while (q != nullptr) {
        if (q->data.first == key)
            return true;
        q = q->next;
    }
    return false;
}

template<class TKey, class TElement>
TElement& LinkedList<TKey, TElement>::GetByKey(TKey key) {
    if (head == nullptr) {
        std::string message = "List is empty" + std::string(__FILE__) + " " + std::to_string(__LINE__);
        throw std::logic_error(message);
    }
    Node* q = head;
    while (q != nullptr) {
        if (q->data.first == key)
            return q->data.second;
        q = q->next;
    }
    std::string message = "List is empty" + std::string(__FILE__) + " " + std::to_string(__LINE__);
    throw std::logic_error(message);
}

template<class TKey, class TElement>
void LinkedList<TKey, TElement>::Add(TKey key, TElement elem) {
    if (head == nullptr) {
        head = new Node(key, elem);
        ++size;
    } else {
//        std::cout << "im in LL add\n";
        Node* q = head;
        while (true) {
            if (q->data.first == key) {
                q->data.second = elem;
                break;
            }
            if (q->next == nullptr) {
                q->next = new Node(key, elem);
                ++size;
                break;
            }
            q = q->next;
        }
    }
}

template<class TKey, class TElement>
void LinkedList<TKey, TElement>::Remove(TKey key) {
    if (head == nullptr) {
        std::string message = "List is empty" + std::string(__FILE__) + " " + std::to_string(__LINE__);
        throw std::logic_error(message);
    } else {
        Node* q = head;
        Node* bef = nullptr;
        while (q != nullptr) {
            if (q->data.first == key) {
                if (bef == nullptr) {
                    head = nullptr; // это всё чинит, но объекты же не удаляются
                } else {
                    bef->next = q->next;
                    delete q;
//                    q = nullptr;
                }
                --size;
                return;
            }
            bef = q;
            q = q->next;
        }
        throw std::logic_error("No element with this key");
    }
}

template<class TKey, class TElement>
void LinkedList<TKey, TElement>::Print() {
    Node* q = head;
    while (q != nullptr) {
        std::cout << q->data.first << ":" << q->data.second << ", ";
        q = q->next;
    }
    std::cout << "\n";
}

template<class TKey, class TElement>
Pair<TKey, TElement> LinkedList<TKey, TElement>::GetPairByIndex(unsigned index) {
    if (head == nullptr) {
        std::string message = "List is empty" + std::string(__FILE__) + " " + std::to_string(__LINE__);
        throw std::logic_error(message);
    }
    Node* q = head;
    for (int i = 0; i < index; ++i) {
        if (q == nullptr)
            throw std::out_of_range("Index out of range");
        q = q->next;
    }
    return q->data;
}


