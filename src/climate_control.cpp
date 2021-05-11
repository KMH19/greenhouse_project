#include <climate_control.h>


void ClimateControl::controlclimate(HardstateOutput &control_output, SensorInput &control_input){
    

    double temperary_temperture = control_input.getTemperature();
    if(temperary_temperture > target_temperature){
        control_output.SetFanSpeed(100);
    }
    else{
        control_output.SetFanSpeed(0);
    }


}