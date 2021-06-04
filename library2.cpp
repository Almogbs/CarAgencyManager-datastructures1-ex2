#include "library2.h"
#include "cdm2.h"


void *Init(){
    CDM2 *DS = new CDM2 (); 
    return (void*)DS;
}

StatusType AddAgency(void *DS){

}

StatusType SellCar(void *DS, int agencyID, int typeID, int k){

}

StatusType UniteAgencies(void *DS, int agencyID1, int agencyID2){

}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int* res){

}

void Quit(void** DS){
    if(*DS == NULL) return;
    delete (CDM*)(*DS);
    *DS = NULL;   
}
