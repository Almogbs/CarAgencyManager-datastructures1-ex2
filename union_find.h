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

    template <class T, class K>
    class set;

///////////////////////////////////////////////////////////////////////////////////////////////////          NODE
    template <class T, class K>
    class node
    {
        public:
            T element;
            node<T, K>* parent;
            set<T, K>* set_ptr;
            node(const T& element);
    };

    template <class T, class K>
    node<T, K>::node(const T& element) : element(element), parent(nullptr), set_ptr(nullptr) {};

///////////////////////////////////////////////////////////////////////////////////////////////////          SET
    template <class T, class K>  
    class set
    {
        public:
            int size;
            int index;
            node<T, K>* root;
            AVLTree<T>* types_by_id;
            AVLTree<K>* types_by_sells;
            set();
            set(int index, node<T, K>* root);
            ~set();
    };

    template <class T, class K>
    set<T, K>::set(int index, node<T, K>* root) : size(1), index(index), root(root){
        types_by_id = new AVLTree<T>();
        types_by_sells = new AVLTree<K>();
    };

    template <class T, class K>
    set<T, K>::~set(){
        if(types_by_id != nullptr) delete types_by_id;
        if(types_by_sells != nullptr) delete types_by_sells;
    }

    template <class T, class K>
    set<T, K>::set() : size(1), index(0){};

///////////////////////////////////////////////////////////////////////////////////////////////////

    template <class T, class K>
    class UnionFind 
    {
        private:
            DynamicArray<set<T, K>*> groups;
            int size;
            AVLTree<T>* getSortedCombainedIDTree(AVLTree<T>* t1, AVLTree<T>* t2);
            AVLTree<K>* getSortedCombainedSalesTree(AVLTree<K>* t1, AVLTree<K>* t2);
        public:
            UnionFind();
            void makeSet(const T& element);
            int getSize();
            void unite(int key1, int key2);
            set<T, K>* find(int index);
            //AVLTree<T>* getTypesTree(int index);
            ~UnionFind();
    };
}


template <class T, class K>
UnionFind<T, K>::UnionFind() : size(0) {}

template <class T, class K>
int UnionFind<T, K>::getSize(){
    return size;
}


template <class T, class K>
void UnionFind<T, K>::makeSet(const T& element){
    node<T, K>* to_push_node = new node<T, K>(element);
    set<T, K>* to_push_set = new set<T, K>(size, to_push_node);
    to_push_node->set_ptr = to_push_set;
    groups.push(to_push_set);
    size++;
}

/*
template <class T, class K>
AVLTree<T>* UnionFind<T>::getTypesTree(int index){
    set<T>* owner_set = find(index);
    return owner_set->types;
}
*/

template <class T, class K>
void UnionFind<T, K>::unite(int key1, int key2){
    set<T, K>* set1 = find(key1);
    set<T, K>* set2 = find(key2);
    if(set1 == set2) return;
    //key2 join to key1 
    if(set1->size > set2->size){
        set2->root->parent = set1->root;
        AVLTree<T>* combined_id_tree = getSortedCombainedIDTree(set1->types_by_id, set2->types_by_id);
        AVLTree<K>* combined_sales_tree = getSortedCombainedSalesTree(set1->types_by_sells, set2->types_by_sells);
        set1->size += set2->size;
        delete set1->types_by_id;
        delete set2->types_by_id;
        delete set1->types_by_sells;
        delete set2->types_by_sells;
        set1->types_by_id = combined_id_tree;
        set1->types_by_sells = combined_sales_tree;
        set2->types_by_id = nullptr;
        set2->types_by_sells = nullptr;
    }
    //key1 join to key2
    else{
        set1->root->parent = set2->root;
        AVLTree<T>* combined_id_tree = getSortedCombainedIDTree(set1->types_by_id, set2->types_by_id);
        AVLTree<K>* combined_sales_tree = getSortedCombainedSalesTree(set1->types_by_sells, set2->types_by_sells);
        set2->size += set1->size;
        delete set1->types_by_id;
        delete set2->types_by_id;
        delete set1->types_by_sells;
        delete set2->types_by_sells;
        set2->types_by_id = combined_id_tree;
        set2->types_by_sells = combined_sales_tree;
        set1->types_by_id = nullptr;
        set1->types_by_sells = nullptr;
    }
}

template <class T, class K>
AVLTree<T>* UnionFind<T, K>::getSortedCombainedIDTree(AVLTree<T>* t1, AVLTree<T>* t2){
    int size1 = t1->getSize(), size2 = t2->getSize();
    T* arr = new T[size1+size2];
    T* arr1 = new T[size1];
    T* arr2 = new T[size2];
    if(size1>0){
        arr1[0] = *t1->InOrderGetFirst();
        for(int i=1; i<size1; i++){
            arr1[i] = *t1->InOrderGetNext();
        }
    }
    if(size2>0){
        arr2[0] = *t2->InOrderGetFirst();
        for(int i=1; i<size2; i++){
            arr2[i] = *t2->InOrderGetNext();
        }
    }
    int counter1=0, counter2=0, total_counter = 0;
    while(size1>counter1 && size2>counter2){
        if(arr1[counter1] < arr2[counter2]) arr[total_counter++] = arr1[counter1++];
        else arr[total_counter++] = arr2[counter2++];
    }
    while(size1 > counter1) arr[total_counter++] = arr1[counter1++];
    while(size2 > counter2) arr[total_counter++] = arr2[counter2++];
    
    AVLTree<T>* result = (size1+size2 == 0) ? new AVLTree<T>() : new AVLTree<T>(arr, size1+size2);
    //AVLTree<T>* result = new AVLTree<T>(arr, size1+size2);
    delete[] arr1;
    delete[] arr2;
    delete[] arr;
    return result;
}

template <class T, class K>
AVLTree<K>* UnionFind<T, K>::getSortedCombainedSalesTree(AVLTree<K>* t1, AVLTree<K>* t2){
    int size1 = t1->getSize(), size2 = t2->getSize();
    K* arr = new K[size1+size2];
    K* arr1 = new K[size1];
    K* arr2 = new K[size2];
    if(size1>0){
        arr1[0] = *t1->InOrderGetFirst();
        for(int i=1; i<size1; i++){
            arr1[i] = *t1->InOrderGetNext();
        }
    }
    if(size2>0){
        arr2[0] = *t2->InOrderGetFirst();
        for(int i=1; i<size2; i++){
            arr2[i] = *t2->InOrderGetNext();
        }
    }
    int counter1=0, counter2=0, total_counter = 0;
    while(size1>counter1 && size2>counter2){
        if(arr1[counter1] < arr2[counter2]) arr[total_counter++] = arr1[counter1++];
        else arr[total_counter++] = arr2[counter2++];
    }
    while(size1 > counter1) arr[total_counter++] = arr1[counter1++];
    while(size2 > counter2) arr[total_counter++] = arr2[counter2++];
    
    AVLTree<K>* result = (size1+size2 == 0) ? new AVLTree<K>() : new AVLTree<K>(arr, size1+size2);
    //AVLTree<T>* result = new AVLTree<T>(arr, size1+size2);
    delete[] arr1;
    delete[] arr2;
    delete[] arr;
    return result;
}



template <class T, class K>
set<T, K>* UnionFind<T, K>::find(int index){
    node<T, K>* element_in_group = (*groups.get(index))->root;
    node<T, K>* set_leader = element_in_group;
    node<T, K>* temp = element_in_group;
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


template <class T, class K>
UnionFind<T, K>::~UnionFind(){
    for(int i = 0; i < groups.size(); i++){
        delete (*groups.get(i))->root;
        delete *groups.get(i);
    }
}


#endif  /* UNION_FIND_H_ */
