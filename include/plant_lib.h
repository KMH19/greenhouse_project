#pragma once
#include "plant.h"

class PlantLib
{
private:
    double plant_info[4][2] = {{1,1},{2,2},{3,3},{4,4}};
    

public:
    
    
    void GetPlantInfo(int plant_number, double &grow_rate, double &target_temperature);

    // Maybe implement reading plant growth rate and target temperature to be read from here.

};

