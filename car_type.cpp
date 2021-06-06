#include "car_type.h"

CarType::CarType() : type_id(0), sells(0) {};

CarType::CarType(int type_id, int sells = 0) :  type_id(type_id), sells(sells) {}

void CarType::addSales(int k){
    sells += k;
}

int CarType::getSells() const{
    return this->sells;
}

int CarType::getID() const{
    return this->type_id;
}


bool CarType::operator==(const CarType& type) const{
    return (type_id == type.type_id); 
}  

bool CarType::operator>(const CarType& type) const{
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

//!!!

CarTypeBySells::CarTypeBySells(int type_id, int sells = 0) : CarType(type_id,sells){};

CarTypeBySells::CarTypeBySells() : CarType() {};


bool CarTypeBySells::operator==(const CarType& type) const{
    return (type_id == type.getID() && sells == type.getSells()); 
}  

bool CarTypeBySells::operator>(const CarType& type) const{
    if (sells > type.getSells())
    {
        return true;
    }
    else if (sells < type.getSells()) return false;
    return type_id > type.getID(); 
}


bool DataStructures::operator!=(const CarTypeBySells& type1, const CarTypeBySells& type2){
    return !(type1 == type2);
} 

bool DataStructures::operator<=(const CarTypeBySells& type1, const CarTypeBySells& type2){
    return !(type1 > type2); 
}

bool DataStructures::operator>=(const CarTypeBySells& type1, const CarTypeBySells& type2){
    return !(type1 < type2);
}

bool DataStructures::operator<(const CarTypeBySells& type1, const CarTypeBySells& type2){
        return (type1 <= type2) && (type1 != type2); 
}
