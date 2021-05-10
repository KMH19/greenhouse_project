#pragma once

class HardstateOutput
{
private:
    double fan_speed;
    double watering_speed;
    double light_intensity;
public:
    // HardstateOutput(/* args */);
    // ~HardstateOutput();

    void SetFanSpeed(double fan_speed_1);
    void SetWateringSpeed(double set_watering_speed);
    void SetLightIntensity(double set_light_intensity);
};


