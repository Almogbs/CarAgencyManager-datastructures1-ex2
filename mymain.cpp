#include "union_find.h"


using namespace DataStructures;


int main(){
    UnionFind<int> testi;
    testi.MakeSet(2);

    for(int i=0; i<9; i++){
        testi.MakeSet(i*i);
    }



    return 0;
}