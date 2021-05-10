#pragma once
#include <plant.h>

class CimateControl
{
private:
    double target_temperature;
public:
    CimateControl(/* args */);
    CimateControl(double plant_target_temperature){
        target_temperature = plant_target_temperature;
    }
     CimateControl(Plant& plant){
        target_temperature = plant.GetTargetTemperature();
    }
    ~CimateControl();
    void controlclimate();
};


