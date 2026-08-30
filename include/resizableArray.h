#ifndef RESIZABLEARRAY_H
#define RESIZABLEARRAY_H

#include <cstddef>

template<class Type>
class resizableArray {
    Type *array;
    size_t sz;
    size_t idx;

    void resize() {
        size_t newSz = (sz == 0) ? 16 : 2 * sz;
        Type *arr = new Type[newSz];
        for (size_t i = 0; i < idx; i++) {
            arr[i] = array[i];
        }
        delete[] array;
        array = arr;
        sz = newSz;
    }

public:
    resizableArray() : array(new Type[16]), sz(16), idx(0) {}
    resizableArray(size_t x) : array(new Type[x ? 2 * x : 16]), sz(x ? 2 * x : 16), idx(x) {}

    ~resizableArray() {
        delete[] array;
    }

    resizableArray(const resizableArray &other) : sz(other.sz), idx(other.idx) {
        array = new Type[sz];
        for (size_t i = 0; i < idx; i++) {
            array[i] = other.array[i];
        }
    }

    resizableArray& operator=(const resizableArray &other) {
        if (this != &other) {
            delete[] array;
            sz = other.sz;
            idx = other.idx;
            array = new Type[sz];
            for (size_t i = 0; i < idx; i++) {
                array[i] = other.array[i];
            }
        }
        return *this;
    }

    void addItem(Type x) {
        if (idx == sz) resize();
        array[idx++] = x;
    }

    int size() const {
        return static_cast<int>(idx);
    }

    Type& operator[](size_t x) const {
        return array[x];
    }
};

#endif