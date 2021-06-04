#include "car_type.h"

CarType::CarType(int type_id, int sells = 0) :  type_id(type_id), sells(sells) {}

void CarType::addSales(int k){
    sells += k;
}

int CarType::getSells(){
    return this->sells;
}

int CarType::getID(){
    return this->type_id;
}


bool CarType::operator==(const CarType& type) const{
    return (  (sells == type.sells)  && (type_id == type.type_id)  ); 
}  

bool CarType::operator>(const CarType& type) const{
    if (sells > type.sells)
    {
        return true;
    }
    else if (sells < type.sells) return false;
    return type_id > type.type_id; 
}

bool DataStructures::operator!=(const CarType& type1, const CarType& type2){
    return !(type1 == type2);
} 

bool DataStructures::operator<=(const CarType& type1, const CarType& type2){
    return !(type1 > type2); 
}

bool DataStructures::operator>=(const CarType& type1, const CarType& type2){
    return !(type1 < type2);
}

bool DataStructures::operator<(const CarType& type1, const CarType& type2){
        return (type1 <= type2) && (type1 != type2); 
}
