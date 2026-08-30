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


#endif //SMARTLIBRARYSYSTEM_RESIZABLEARRAY_H