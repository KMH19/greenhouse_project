#include <hardstate_output.h>



void HardstateOutput::SetFanSpeed(double fan_speed_1){
    fan_speed = fan_speed_1;
}

void HardstateOutput::SetWateringSpeed(double set_watering_speed){
    watering_speed = set_watering_speed;
}

void HardstateOutput::SetLightIntensity(double set_light_intensity){
    light_intensity = set_light_intensity;
}