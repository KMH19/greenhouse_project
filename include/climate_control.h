#pragma once
#include <plant.h>
#include <sensor_input.h>
#include <hardstate_output.h>


class ClimateControl
{
private:
    double target_temperature;
    

public:
    ClimateControl(/* args */);
    ClimateControl(double plant_target_temperature){
        target_temperature = plant_target_temperature;
    }
     ClimateControl(Plant& plant){
        target_temperature = plant.GetTargetTemperature();
    }
    ~ClimateControl();
    void controlclimate(HardstateOutput &control_output, SensorInput &control_input);
};


