#ifndef CDM2_H_
#define CDM2_H_

#include "car_type.h"
#include "union_find.h"
#include "avl_tree.h"
#include "node.h"
#include "exceptions.h"
#include "library2.h"

#define INIT 0

class CDM2{
private:
    int num_of_agencies;
    UnionFind<CarType, CarTypeBySells> agencies;
public:
    CDM2();
    StatusType AddAgency();
    StatusType SellCar(int agencyID, int typeID, int k);
    StatusType UniteAgencies(int agencyID1, int agencyID2);
    StatusType GetIthSoldType(int agencyID, int i, int* res);
};

#endif /* CDM2_H_ */