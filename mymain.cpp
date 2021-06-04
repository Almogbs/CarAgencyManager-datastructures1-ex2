#include "union_find.h"
#include "dynamic_array.h"


using namespace DataStructures;

class Mama {
public:
    int index;
    int sells;
    Mama(int index, int sells) : index(index), sells(sells){}
};

int main(){
    UnionFind<Mama> testi;

    for(int i=0; i<9; i++){
        testi.makeSet(Mama(i,i*i));
    }

    for(int i=0; i<testi.getSize(); i++){
        cout << testi.find(i)->index << endl;
    }

    for(int i=0; i<testi.getSize(); i++){
        cout << testi.find(i)->root->element.sells << endl;
    }


    return 0;
}