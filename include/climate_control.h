#pragma once

#include "hardstate_output.h"
#include "sensor_input.h"
#include "plant.h"

class ClimateControl
{
private:
bool auto_state_{true};


public:

void Automatic(SensorInput& s, Plant& p, HardstateOutput& h);

void Manual();

bool checkAutoState() { return auto_state_; }
void changeState(bool& i);

bool approximatelyEqual(double a, double b, double epsilon);
bool essentiallyEqual(double a, double b, double epsilon);
bool definitelyGreaterThan(double a, double b, double epsilon);
bool definitelyLessThan(double a, double b, double epsilon);


    // ClimateControl(double plant_target_temperature){
    //     target_temperature = plant_target_temperature;
    // }
    
    //  ClimateControl(Plant& plant){
    //     target_temperature = plant.GetTargetTemperature();
    // }

    // void controlclimate(HardstateOutput &control_output, SensorInput &control_input);


};  // Class "ClimateControl" end