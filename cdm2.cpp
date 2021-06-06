#include "cdm2.h"

static bool isLegalK(int k){
    return k > 0;
}

static bool isLegalAgencyID(int agencyID){
    return agencyID >= 0;
}


CDM2::CDM2() : num_of_agencies(INIT) {}

StatusType CDM2::AddAgency(){
    try{
        agencies.makeSet(CarType(num_of_agencies, INIT));
    }
    catch(const std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
    num_of_agencies++;
    return SUCCESS;
}

StatusType CDM2::SellCar(int agencyID, int typeID, int k){
    if(!isLegalAgencyID(agencyID) || !isLegalK(k)){
        return INVALID_INPUT;
    }
    else if (agencyID >= num_of_agencies){
        return FAILURE;
    }
    set<CarType, CarTypeBySells>* agency_set = agencies.find(agencyID);
    AVLTree<CarType>* types_tree_by_id = agency_set->types_by_id;
    AVLTree<CarTypeBySells>* types_tree_by_sells = agency_set->types_by_sells;
    try{
        Node<CarType>* type = types_tree_by_id->getNode(CarType(typeID, INIT));
        type->key.addSales(k);
        types_tree_by_sells->remove(CarTypeBySells(typeID, type->key.getSells() - k));
        types_tree_by_sells->insert(CarTypeBySells(typeID, type->key.getSells()));
    }
    catch (const DataStructures::NodeNotExist &e){
        types_tree_by_id->insert(CarType(typeID, k));
        types_tree_by_sells->insert(CarTypeBySells(typeID, k));
    }
    catch(const std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType CDM2::UniteAgencies(int agencyID1, int agencyID2){
    if(!isLegalAgencyID(agencyID1) || !isLegalAgencyID(agencyID2)){
        return INVALID_INPUT;
    }
    else if (agencyID1 >= num_of_agencies || agencyID2 >= num_of_agencies ){
        return FAILURE;
    }
    try{
        agencies.unite(agencyID1, agencyID2);
    }
    catch(const std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType CDM2::GetIthSoldType(int agencyID, int i, int* res){
    *res = 0;
    return SUCCESS;
}
