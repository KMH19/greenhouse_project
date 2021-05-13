#include "plant.h"

    Plant::plant_type Plant::getPlant() const { 
        return type_;
    }

    void Plant::setType(Plant::plant_type v, double growth_rate, double target_temperature) {
        if (type_ == v) return;
        type_ = v;

        if (growth_rate == growth_rate_) return;
        growth_rate_ = growth_rate;

        if (target_temperature == target_temperature_) return;
        target_temperature_ = target_temperature;
    }

    void Plant::grow(int days) {
    if (height_ < max_height_)
    {
        height_ = height_ + days * growth_rate_;
    }else
        return;
    }

    void Plant::reset() {
        height_ = 0.;
    }


    