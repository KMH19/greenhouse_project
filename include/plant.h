#pragma once
#include "plant_base.h"

class Plant : public plant_base 
{
    private:
    double growth_rate_;

    double target_temperature_;

    float height_{0.};

    public:

    enum plant_type 
    {    
    cactus_plant    = 0, 
    tomato_plant    = 1, 
    cucumber_plant  = 2,
    paradise_tree   = 3
    };

    void grow(int days) override;

    void reset()        override;

    float getHeight() override { return height_; };

    Plant::plant_type getPlant() const;

    void setType(Plant::plant_type v, double growth_rate, double target_temperature);

    double GetTargetTemperature() { return target_temperature_; }

    private:
    plant_type type_;
};
