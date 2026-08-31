//
// Created by Ibrahim on 8/30/2026.
//

#ifndef SMARTLIBRARYSYSTEM_RESIZABLEARRAY_H
#define SMARTLIBRARYSYSTEM_RESIZABLEARRAY_H
#include <cstddef>
using std::size_t;

template<class Type>
class resizableArray {
    Type *array;
    size_t sz, idx;
    void resize(){
        sz *= 2;
        Type *arr = new Type[sz];
        for (size_t i = 0; i < idx; ++i) arr[i] = array[i];
        delete[] array;
        array = arr;
    }
public :
    resizableArray() : sz(16), idx(0) {
        array = new Type[sz];
    }
    resizableArray(size_t x) : sz(2*x), idx(0) {
        array = new Type[sz];
    }
    resizableArray(const resizableArray &arr) : sz(arr.sz), idx(arr.idx) {
        array = new Type[sz];
        for (size_t i = 0; i < idx; ++i) {
            array[i] = arr.array[i];
        }
    }
    resizableArray& operator=(const resizableArray &arr) {
        if (this != &arr) {
            delete[] array;
            sz = arr.sz;
            idx = arr.idx;
            array = new Type[sz];
            for (size_t i = 0; i < idx; ++i) {
                array[i] = arr.array[i];
            }
        }
        return *this;
    }
    ~resizableArray() {
        delete[] array;
    }
    void addItem(Type x) {
        if (idx == sz) resize();
        array[idx] = x;
        idx++;
    }
    int size() const { return (int)idx; }
    Type& operator [](size_t x) const {
        return array[x];
    }

    void removeItemAt(size_t index) {
        if (index >= idx) return;
        for (size_t i = index; i < idx - 1; ++i) {
            array[i] = array[i + 1];
        }
        idx--;
    }
};

#endif //SMARTLIBRARYSYSTEM_RESIZABLEARRAY_H