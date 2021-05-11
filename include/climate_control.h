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

    // Constructor that can get the target temperature as a double :)
    ClimateControl(double plant_target_temperature){
        target_temperature = plant_target_temperature;
    }
    // Constructor that gets the target temperature from the plant class. :)
     ClimateControl(Plant& plant){
        target_temperature = plant.GetTargetTemperature();
    }
    ~ClimateControl();

    //Void function for compare the temperature and the target temperature, and adjust fanspeed :)
    void controlclimate(HardstateOutput &control_output, SensorInput &control_input);
};


