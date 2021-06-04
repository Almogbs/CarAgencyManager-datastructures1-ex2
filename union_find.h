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
    class set;

///////////////////////////////////////////////////////////////////////////////////////////////////          NODE
    template <class T>
    class node
    {
        public:
            T element;
            node<T>* parent;
            set<T>* set_ptr;
            node(const T& element);
    };

    template <class T>
    node<T>::node(const T& element) : element(element), parent(nullptr), set_ptr(nullptr) {};

///////////////////////////////////////////////////////////////////////////////////////////////////          SET
    template <class T>  
    class set
    {
        public:
            int size;
            int index;
            node<T>* root;
            AVLTree<T>* types;
            set();
            set(int index, node<T>* root);
            ~set();
    };

    template <class T>
    set<T>::set(int index, node<T>* root) : size(1), index(index), root(root){
        types = new AVLTree<T>();
    };

    template <class T>
    set<T>::~set(){
        if(types != nullptr) delete types;
    }

    template <class T>
    set<T>::set() : size(1), index(0){};

///////////////////////////////////////////////////////////////////////////////////////////////////

    template <class T>
    class UnionFind 
    {
        private:
            DynamicArray<set<T>*> groups;
            int size;
        public:
            UnionFind();
            void makeSet(const T& element);
            int getSize();
            void unite(int key1, int key2);
            set<T>* find(int index);
            AVLTree<T>* getTypesTree(int index);
            AVLTree<T>* getSortedCombainedTree(AVLTree<T>* t1, AVLTree<T>* t2);

            ~UnionFind();
    };
}


template <class T>
UnionFind<T>::UnionFind() : size(0) {}

template <class T>
int UnionFind<T>::getSize(){
    return size;
}


template <class T>
void UnionFind<T>::makeSet(const T& element){
    node<T>* to_push_node = new node<T>(element);
    set<T>* to_push_set = new set<T>(size, to_push_node);
    to_push_node->set_ptr = to_push_set;
    groups.push(to_push_set);
    size++;
}

template <class T>
AVLTree<T>* UnionFind<T>::getTypesTree(int index){
    set<T>* owner_set = find(index);
    return owner_set->types;
}


template <class T>
void UnionFind<T>::unite(int key1, int key2){
    set<T>* set1 = find(key1);
    set<T>* set2 = find(key2);
    //key2 join to key1 
    if(set1->size > set2->size){
        set2->root->parent = set1->root;
        AVLTree<T>* combined_tree = getSortedCombainedTree(set1->types, set2->types);
        set1->size += set2->size;
        delete set1->types;
        delete set2->types;
        set1->types = combined_tree;
        set2->types = nullptr;
    }
    //key1 join to key2
    else{
        set1->root->parent = set2->root;
        AVLTree<T>* combined_tree = getSortedCombainedTree(set1->types, set2->types);
        set2->size += set1->size;
        delete set1->types;
        delete set2->types;
        set2->types = combined_tree;
        set1->types = nullptr;
    }
}

template <class T>
AVLTree<T>* UnionFind<T>::getSortedCombainedTree(AVLTree<T>* t1, AVLTree<T>* t2){
    int size1 = t1->getSize(), size2 = t2->getSize();
    T* arr = new T[size1+size2];
    T* arr1 = new T[size1];
    T* arr2 = new T[size2];
    arr1[0] = t1.InOrderGetFirst();
    for(int i=1; i<size1; i++){
        arr1[i] = t1.InOrderGetNext();
    }
    arr2[0] = t2.InOrderGetFirst();
    for(int i=1; i<size2; i++){
        arr2[i] = t2.InOrderGetNext();
    }
    int counter1=0, counter2=0, total_counter = 0;
    while(size1>counter1 && size2>counter2){
        if(arr1[counter1] < arr2[counter2]) arr[total_counter++] = arr1[counter1++];
        else arr[total_counter++] = arr2[counter2++];
    }
    while(size1 > counter1) arr[total_counter++] = arr1[counter1++];
    while(size2 > counter2) arr[total_counter++] = arr2[counter2++];
    
    AVLTree<T>* result = new AVLTree<T>(arr, size1+size2);
    delete[] arr1;
    delete[] arr2;
    delete[] arr;
    return result;
}



template <class T>
set<T>* UnionFind<T>::find(int index){
    node<T>* element_in_group = (*groups.get(index))->root;
    node<T>* set_leader = element_in_group;
    node<T>* temp = element_in_group;
    while (set_leader->parent != nullptr)
    {
        set_leader = set_leader->parent;
    }
    while (element_in_group->parent != nullptr)
    {
        temp = element_in_group->parent;
        element_in_group->parent = set_leader;
        element_in_group = temp;
    }

    return set_leader->set_ptr;
}


template <class T>
UnionFind<T>::~UnionFind(){
    for(int i = 0; i < groups.size(); i++){
        delete (*groups.get(i))->root;
        delete *groups.get(i);
    }
}


#endif  /* UNION_FIND_H_ */
