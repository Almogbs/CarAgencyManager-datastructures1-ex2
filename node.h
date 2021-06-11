#ifndef NODE_H_
#define NODE_H_

/**
* Generic Node
*
* Implements a Node of generic type.
*
*/

#include "exceptions.h"

#define EMPTY_TREE_HEIGHT -1
#define LEAF_TREE_HEIGHT 0


namespace DataStructures{

	template <class T>
	class Node {
    public:
        T         key;
		int       height;
        int       rank;
		Node*     parent;
		Node*     left;
		Node*     right;
        Node(const T& key, int height = LEAF_TREE_HEIGHT, int rank = 1) : key(key), height(height), rank(rank){
            parent = nullptr;
            left = nullptr;
            right = nullptr;
        };
        void update_height();
        void update_rank();
        T* get_key();
        int get_height() const;
        int get_rank() const;
        int get_left_height();
        int get_left_rank();
        int get_right_height();
        int get_right_rank();
		int get_balanced_factor() const;
	};

    template <class T>
    T* Node<T>::get_key(){
	    return &key;
    }
 
    template <class T>
    void Node<T>::update_height(){
        height = std::max(get_left_height(), get_right_height()) + 1;       
    }

    template <class T>
    void Node<T>::update_rank(){
        rank = get_left_rank() + get_right_rank() + 1;       
    }

    template <class T>
    int Node<T>::get_height() const{
        return height;
    }    
    
    template <class T>
    int Node<T>::get_rank() const{
        return rank;
    }

    template <class T>
    int Node<T>::get_left_height(){
        return (left == nullptr) ? EMPTY_TREE_HEIGHT : left->get_height();
    }

    template <class T>
    int Node<T>::get_right_height(){
        return (right == nullptr) ? EMPTY_TREE_HEIGHT : right->get_height();
    }

    template <class T>
    int Node<T>::get_left_rank(){
        return (left == nullptr) ? LEAF_TREE_HEIGHT : left->get_rank();
    }

    template <class T>
    int Node<T>::get_right_rank(){
        return (right == nullptr) ? LEAF_TREE_HEIGHT : right->get_rank();
    }

    template <class T>
    int Node<T>::get_balanced_factor() const{
        if(left == nullptr && right == nullptr) return 0;
        else if(left == nullptr) return EMPTY_TREE_HEIGHT - right->get_height();
        else if(right == nullptr) return left->get_height() - EMPTY_TREE_HEIGHT;
        return left->get_height() - right->get_height();
    }
}

#endif  /* NODE_H_ */