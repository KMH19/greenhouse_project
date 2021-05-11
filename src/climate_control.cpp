#include <climate_control.h>
#include <sensor_input.h>
#include <hardstate_output.h>

void ClimateControl::controlclimate(){
    SensorInput sensor_input;
    HardstateOutput hardstate_output;

    double temperary_temperture = sensor_input.getTemperature();
    if(temperary_temperture > target_temperature){
        hardstate_output.SetFanSpeed(100);
    }
    else{
        hardstate_output.SetFanSpeed(0);
    }

}