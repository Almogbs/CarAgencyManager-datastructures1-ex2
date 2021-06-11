#ifndef CAR_TYPE_H_
#define CAR_TYPE_H_

#include "car_type.h"

namespace DataStructures {
    class CarType{
    protected:
        int type_id;
        int sells;
    public: 
        CarType();
        CarType(int type_id, int sells);
        ~CarType() = default;
        void addSales(int k);
        int getSells() const;
        int getID() const;
        virtual bool operator==(const CarType&) const;
        virtual bool operator>(const CarType&) const;
    };

    bool operator!=(const CarType&, const CarType&);
    bool operator<=(const CarType&, const CarType&);
    bool operator>=(const CarType&, const CarType&);  
    bool operator<(const CarType&, const CarType&);

    class CarTypeBySells : public CarType {
    public:
        CarTypeBySells();
        CarTypeBySells(int type_id, int sells);
        bool operator==(const CarType&) const override;
        bool operator>(const CarType&) const override;
    };
    bool operator!=(const CarTypeBySells&, const CarTypeBySells&);   
    bool operator>=(const CarTypeBySells&, const CarTypeBySells&);
    bool operator<(const CarTypeBySells&, const CarTypeBySells&);
    bool operator<=(const CarTypeBySells&, const CarTypeBySells&);
}
using namespace DataStructures;


#endif /* CAR_TYPE_H_ */
