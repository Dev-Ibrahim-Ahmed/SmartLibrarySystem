//
// Created by Ibrahim on 8/30/2026.
//

#include "../include/resizableArray.h"

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
