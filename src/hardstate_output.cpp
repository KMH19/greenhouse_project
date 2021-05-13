#include <hardstate_output.h>

    void HardstateOutput::SetFanSpeed(double& set_fan_speed){

        if (set_fan_speed == fan_speed_) return;
            fan_speed_ = set_fan_speed;
    }

    void HardstateOutput::SetWateringSpeed(double& set_watering_speed){

        if (set_watering_speed == watering_speed_) return;
            watering_speed_ = set_watering_speed;
    }

    void HardstateOutput::SetLightIntensity(double& set_light_intensity){

        if (set_light_intensity == light_intensity_) return;
            light_intensity_ = set_light_intensity;

    }

    void HardstateOutput::resetFan(){
        fan_speed_ = 0; 
    }