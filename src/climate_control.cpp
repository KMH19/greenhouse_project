#include <climate_control.h>

void ClimateControl::changeState(bool& i)
{
    if (i == auto_state_) return;
    auto_state_ = i;
}

// void ClimateControl::controlclimate(HardstateOutput &control_output, SensorInput &control_input){
    
//     double temperary_temperture = control_input.getTemperature();
//     if(temperary_temperture > target_temperature){
//         control_output.SetFanSpeed(100);
//     }
//     else{
//         control_output.SetFanSpeed(0);
//     }

// }

// Ambition with software:
// Temperature
// Fan control

// The design must use object-oriented elements, involve at least three classes and at least one case of inheritance; the implementation shall involve at least three different object instances.
// You must demonstrate the use of at least one container type from the C++ standard library (vector, list, deque etc.)