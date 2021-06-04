#ifndef UNION_FIND_H_
#define UNION_FIND_H_

#include "exceptions.h"
#include "avl_tree.h"
#include "dynamic_array.h"
#include <stdlib.h>
#include <iostream>

using namespace DataStructures;
using std::endl;
using std::cout;

namespace DataStructures {

    template <class T>
    class node{
    public:
        node<T>* parent;
        T element;
        node(const T& element);
    };

    template <class T>
    node<T>::node(const T& element) : element(element), parent(nullptr) {};

    template <class T>
    class set{
    public:
        node<T>* root;
        int size;
        int index;
        set(int index, node<T>* root);
    };

    template <class T>
    set<T>::set(int index, node<T>* root) : index(index), size(1), root(root){};

    template <class T>
    class UnionFind {
    private:
        DynamicArray<set<T>> groups;
        DynamicArray<node<T>*> elements;
        int size;
    public:
        UnionFind();
        void MakeSet(const T& element);
        //void Union(int key1, int key2);
        //T Find(const T& element);
        ~UnionFind();
    };
}

template <class T>
UnionFind<T>::UnionFind() : size(0) {}

template <class T>
void UnionFind<T>::MakeSet(const T& element){
    node<T>* to_push = new node<T>(element);
    elements.push(to_push);
    groups.push(set<T>(size, to_push));

    size++;
}

/*
template <class T>
void UnionFind<T>::Union(int key1, int key2){
    //key2 join to key1 
    if(darr->get(key1).size > darr->get(key2).size){
        
    }
    else{

    }
}

template <class T>
T UnionFind<T>::Find(const T& element)
{
    set<T> element_in_group = elements->get(element);
    while (element_in_group.parent)
    {
        element_in_group = element_in_group.parent;
    }
    return element_in_group.index;

}*/

template <class T>
UnionFind<T>::~UnionFind(){
    for(int i = 0; i < elements.size(); i++){
        delete elements.get(i)
    }
}


#endif  /* UNION_FIND_H_ */