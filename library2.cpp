#include "library2.h"
#include "cdm2.h"


void *Init(){
    CDM2 *DS = new CDM2(); 
    return (void*)DS;
}

StatusType AddAgency(void *DS){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((CDM2 *)DS)->AddAgency();
}

StatusType SellCar(void *DS, int agencyID, int typeID, int k){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((CDM2 *)DS)->SellCar(agencyID, typeID, k);
}

StatusType UniteAgencies(void *DS, int agencyID1, int agencyID2){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((CDM2 *)DS)->UniteAgencies(agencyID1, agencyID2);
}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int* res){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((CDM2 *)DS)->GetIthSoldType(agencyID, i, res);
}

void Quit(void** DS){
    if(*DS == NULL) return;
    delete (CDM2*)(*DS);
    *DS = NULL;   
}
