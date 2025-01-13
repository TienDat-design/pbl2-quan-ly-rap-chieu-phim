#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class Set {
private:
    T* elements;
    size_t capacity;
    size_t count;

public:
    Set(size_t initialCapacity = 10) : capacity(initialCapacity), count(0) {
        elements = new T[capacity];
    }

    ~Set() {
        delete[] elements;
    }

    void insert(const T& element) {
        if (contains(element)) {
            return;
        }

        if (count == capacity) {
            resize(capacity * 2);
        }

        elements[count++] = element;
    }

    void remove(const T& element) {
        size_t index = find(element);
        if (index != count) {
            for (size_t i = index; i < count - 1; ++i) {
                elements[i] = elements[i + 1];
            }
            --count;
        }
    }

    bool contains(const T& element) const {
        return find(element) != count;
    }

    void print() const {
        for (size_t i = 0; i < count; ++i) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }

    size_t size() const {
        return count;
    }

private:
    size_t find(const T& element) const {
        for (size_t i = 0; i < count; ++i) {
            if (elements[i] == element) {
                return i;
            }
        }
        return count;
    }

    void resize(size_t newCapacity) {
        T* newElements = new T[newCapacity];
        for (size_t i = 0; i < count; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }
};