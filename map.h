#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>

using namespace std;

template <typename K, typename V>
class Map {
private:
    struct Node {
        K key;
        V value;
    };
    Node* data;
    int capacity;
    int size;

    void resize() {
        capacity *= 2;
        Node* newData = new Node[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    Map() : capacity(10), size(0) {
        data = new Node[capacity];
    }

    ~Map() {
        delete[] data;
    }

    void insert(const K& key, const V& value) {
        if (size == capacity) {
            resize();
        }
        for (int i = 0; i < size; i++) {
            if (data[i].key == key) {
                data[i].value = value;
                return;
            }
        }
        data[size].key = key;
        data[size].value = value;
        size++;
    }

    bool contains(const K& key) const {
        for (int i = 0; i < size; i++) {
            if (data[i].key == key) {
                return true;
            }
        }
        return false;
    }

    V get(const K& key) const {
        for (int i = 0; i < size; i++) {
            if (data[i].key == key) {
                return data[i].value;
            }
        }
        throw out_of_range("Key not found");
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            cout << "| " << left << setw(20) << data[i].key
                 << " | " << right << setw(10) << data[i].value << " |" << endl;
        }
    }

    int getSize() const {
        return size;
    }

    V& operator[](const K& key) {
        for (int i = 0; i < size; i++) {
            if (data[i].key == key) {
                return data[i].value;
            }
        }
        if (size == capacity) {
            resize();
        }
        data[size].key = key;
        data[size].value = V();
        size++;
        return data[size - 1].value;
    }

    Node* begin() {
        return data;
    }

    Node* end() {
        return data + size;
    }

    const Node* begin() const {
        return data;
    }

    const Node* end() const {
        return data + size;
    }
};
