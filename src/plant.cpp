#include "plant.h"
#include "plant_lib.h"

    Plant::plant_type Plant::getPlant() const { 
    return type_;
    }

    void Plant::setType(Plant::plant_type v) {
        if (type_ == v) return;
        type_ = v;
    }

    void Plant::grow(int days) {
    growth_rate = 
    height = height + days * growth_rate;
    }