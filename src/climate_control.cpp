#include <climate_control.h>

// Compareing the temperature with the target temperature and adjust the fanspeed if the temperature is to high. :)
void ClimateControl::controlclimate(HardstateOutput &control_output, SensorInput &control_input){
    

    double temperary_temperture = control_input.getTemperature();
    if(temperary_temperture > target_temperature){
        control_output.SetFanSpeed(100);
    }
    else{
        control_output.SetFanSpeed(0);
    }

}