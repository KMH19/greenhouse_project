#include <plant.h>
#include <iostream>

    // plant_type getPlant() { return m_number; }
    // void setPlant(plant_type number) { m_number = number; }

    // plant_type Plant::getPlant() const { return type_; }

    // void Plant::setPlant(plant_type v) {
    //     if (type_ == v) return;
    //     type_ = v;
    // }

    Plant::plant_type Plant::getPlant() const { 
    return type_;
    }

    void Plant::setType(Plant::plant_type v) {
        if (type_ == v) return;
        type_ = v;
    }