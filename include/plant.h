#pragma once
#include <string>
#include "plant_base.h"

/*********************************************************************************************
 * @brief                       Controls simulation of the instantiated plant object  
 * @param growth_rate_          Growth rate of the plant object
 * @param target_temperature_   The temperature needed for optimal growth
 * @param height_               Current height used for simulating growth in GUI
 * @param max_height_           Max height used for stopping growth in simulation
 * @param plant_type            Available plant types in enum (0, 1, 2 ,3)
 * @param plant_names           Names of the plants as const char* (in order)
 * @param type_                 The current plant type 
 *********************************************************************************************/
class Plant : public plant_base 
{
private:
    double growth_rate_;
    double target_temperature_;
    float height_{0.};
    float max_height_{360};

public:
    enum plant_type 
    {    
    cactus_plant    = 0, 
    tomato_plant    = 1, 
    cucumber_plant  = 2,
    paradise_tree   = 3
    };

    const char* plant_names[4] = {
        "Cactus Plant",
        "Tomato Plant",
        "Cucumber Plant",
        "Paradise Tree",
    };

    // For function descriptions refer to plant.cpp
    void setType(Plant::plant_type v, double growth_rate, double target_temperature);
    void grow(int days)  override;
    void reset()         override;


    // Getters for the "Plant" class
    Plant::plant_type getPlant() const;
    float getHeight()    override { return height_;      };
    float getGrowthRate()         { return growth_rate_; };
    double GetTargetTemperature() { return target_temperature_; }

    private:
    plant_type type_;
};  // Class "Plant" end