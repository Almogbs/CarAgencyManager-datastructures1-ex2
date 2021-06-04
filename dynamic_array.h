#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#include "exceptions.h"
#include <stdlib.h>
#include <iostream>

#define INIT_SIZE 4
#define FACTOR 2
#define EMPTY 0

using namespace DataStructures;
using std::endl;
using std::cout;

namespace DataStructures {

    template <class T>
    class DynamicArray {
    private:
        T* arr;
        int max_size;
        int curr_size;
        void resizeUp();
        //void resizeDown();

    public:
        DynamicArray(int size = INIT_SIZE);
        void push(const T& element);
        int size();
        T* get(int index);
        ~DynamicArray();
        //DynamicArray(const DynamicArray& darr);
        //void insert(int index, const T& element);
        //void removeTop(int index);
        //void remove(int index);
    };
}

template <class T>
DynamicArray<T>::DynamicArray(int size) : max_size(size), curr_size(EMPTY) {
    arr = new T[max_size];
}

template <class T>
void DynamicArray<T>::push(const T& element){
    if(curr_size >=  max_size){
        resizeUp();
    }
    arr[curr_size] = element;
    curr_size++;
}

template <class T>
int DynamicArray<T>::size(){
    return curr_size;
}

template <class T>
T* DynamicArray<T>::get(int index){
    if(index >= curr_size){
        throw InvalidArg();
    }
    return arr + index;
}

template <class T>
void DynamicArray<T>::resizeUp(){
    max_size *= FACTOR;
    T* new_arr = new T[max_size];
    for(int i=0; i<curr_size; i++){
        new_arr[i] = arr[i];
    }
    delete[] arr;
    arr = new_arr;
}

template <class T>
DynamicArray<T>::~DynamicArray(){
    delete[] arr;
}


#endif  /* DYNAMIC_ARRAY_H_ */