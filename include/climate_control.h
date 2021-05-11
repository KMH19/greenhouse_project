#pragma once
#include <plant.h>
#include <sensor_input.h>
#include <hardstate_output.h>

class ClimateControl
{
private:
bool auto_state_{true};

public:
void Automatic() 
{
}

void Manual() 
{
}

bool getState() { return auto_state_; }
void changeState(bool& i);

    // ClimateControl(double plant_target_temperature){
    //     target_temperature = plant_target_temperature;
    // }
    
    //  ClimateControl(Plant& plant){
    //     target_temperature = plant.GetTargetTemperature();
    // }

    // void controlclimate(HardstateOutput &control_output, SensorInput &control_input);


};  // Class "ClimateControl" end


