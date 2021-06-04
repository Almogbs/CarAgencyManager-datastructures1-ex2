#ifndef CAR_TYPE_H_
#define CAR_TYPE_H_

#include "car_type.h"

using namespace DataStructures;

namespace DataStructures {
    class CarType{
        int type_id;
        int sells;

    public: 
        CarType(int type_id, int sells);
        ~CarType() = default;
        void addSales(int k);
        int getSells();
        int getID();
        bool operator==(const CarType&) const;
        bool operator>(const CarType&) const;
        //friend std::ostream& operator<<(std::ostream&, const CarType&);
    };

    //std::ostream& operator<<(std::ostream&, const CarType&);
    bool operator!=(const CarType&, const CarType&);
    bool operator<=(const CarType&, const CarType&);
    bool operator>=(const CarType&, const CarType&);  
    bool operator<(const CarType&, const CarType&);
}


#endif /* CAR_TYPE_H_ */
