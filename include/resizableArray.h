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
    size_t sz , idx;
    void resize();
public :
    resizableArray();
    resizableArray(size_t);
    ~resizableArray();
    void addItem(Type);
    [[nodiscard]] int size() const{return idx;}
    Type& operator [](size_t) const;
};

template<class Type>
void resizableArray<Type>::resize() {
    Type *arr = new Type[2 * sz];
    for (int i = 0; i < idx; ++i)arr[i] = array[i];
    delete[] array;
    array = arr;
}

template<class Type>
resizableArray<Type>::resizableArray() : sz(16) , idx(0){
    array = new Type[sz];
}

template<class Type>
resizableArray<Type>::~resizableArray() {
    delete[] array;
}

template<class Type>
resizableArray<Type>::resizableArray(size_t x) : idx(x) , sz(2*x){
    array = new Type[sz];
}

template<class Type>
Type& resizableArray<Type>::operator[](size_t x) const{
    return array[x];
}

template<class Type>
void resizableArray<Type>::addItem(Type x) {
    if (idx == sz)resize();
    array[idx] = x;
    idx++;
}


#endif //SMARTLIBRARYSYSTEM_RESIZABLEARRAY_H