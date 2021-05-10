#pragma once

class PlantLib
{
private:
    double plant_info[4][2] = {{1,1},{2,2},{3,3},{4,4}};
    

public:
    PlantLib(/* args */);
    ~PlantLib();
    
    void GetPlantInfo(int plant_number, double &grow_rate, double &target_temperature);
};

