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

void HardstateOutput::HardstateRead(double fan_current_speed, double watering_current_speed, double light_current_intensity){
    fan_speed = fan_current_speed;
    watering_speed = watering_current_speed;
    light_intensity = light_current_intensity;
}

double HardstateOutput::GetFanSpeed(){
    return fan_speed;
}