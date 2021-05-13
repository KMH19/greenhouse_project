#pragma once

/*********************************************************************************************
 * @brief                   Controls the output states in the controller
 * @param fan_efficiency_   The fan efficiency (Simulation variable)
 * @param fan_speed_        The fan speed (before simulation variables)
 * @param watering_speed_   Not implemented ATM
 * @param light_intensity_  Not implemented ATM
 *********************************************************************************************/
class HardstateOutput
{
private:
    double fan_efficiency_{0.98};

    double fan_speed_;
    double watering_speed_;
    double light_intensity_;
    
public:
    // For function descriptions refer to src/hardstate_output.cpp
    void HardstateRead(double fan_current_speed, double watering_current_speed, double light_current_intensity);
    void SetFanSpeed(double& set_fan_speed);
    void resetFan();

    // Getters for the fan parameters
    double GetFanSpeed()        { return fan_speed_;       };
    double GetFanEfficiency()   { return fan_efficiency_;  };

    // Not implemented ATM (4)
    double GetWateringSpeed()   { return watering_speed_;  };
    double GetLightIntensity()  { return light_intensity_; };
    void SetWateringSpeed(double& set_watering_speed);
    void SetLightIntensity(double& set_light_intensity);


};


