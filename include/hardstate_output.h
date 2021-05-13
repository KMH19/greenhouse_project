#pragma once

class HardstateOutput
{
private:
    double fan_efficiency_{0.98};

    double fan_speed_;
    double watering_speed_;
    double light_intensity_;
    
public:
    void SetFanSpeed(double& set_fan_speed);
    void SetWateringSpeed(double& set_watering_speed);
    void SetLightIntensity(double& set_light_intensity);

    void resetFan();

    double GetFanSpeed()        { return fan_speed_;       };
    double GetFanEfficiency()   { return fan_efficiency_;  };

    double GetWateringSpeed()   { return watering_speed_;  };
    double GetLightIntensity()  { return light_intensity_; };

    void HardstateRead(double fan_current_speed, double watering_current_speed, double light_current_intensity);
};


