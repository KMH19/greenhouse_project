#pragma once

class HardstateOutput
{
private:
    double fan_speed_;
    double watering_speed_;
    double light_intensity_;
    
public:
    void SetFanSpeed(double& set_fan_speed);
    void SetWateringSpeed(double& set_watering_speed);
    void SetLightIntensity(double& set_light_intensity);

    double GetFanSpeed();

    void HardstateRead(double fan_current_speed, double watering_current_speed, double light_current_intensity);
};


