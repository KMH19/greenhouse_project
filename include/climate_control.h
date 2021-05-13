#pragma once

#include "hardstate_output.h"
#include "sensor_input.h"
#include "plant.h"

/*********************************************************************************************
 * @brief                   Controls the climate inside the greenhouse
 * @param auto_state_       Checks whether the auto state is on
 * @param manual_state_     Checks whether the manual state is on 
 * @param last_correction_  Last correction of the temperature due changes in climate (fan)
 * @param new_temp_         New temperature after the correction is applied
 *********************************************************************************************/
class ClimateControl
{
private:
    bool auto_state_{true};
    bool manual_state_{false};
    double last_correction_{0.};
    double new_temp_{0.};


public:
    // For function descriptions refer to src/climate_control.cpp
    double Automatic(SensorInput& s, Plant& p, HardstateOutput& h);
    void Manual();
    void changeState(bool& i);
    bool approximatelyEqual(double a, double b, double epsilon);
    bool essentiallyEqual(double a, double b, double epsilon);
    bool definitelyGreaterThan(double a, double b, double epsilon);
    bool definitelyLessThan(double a, double b, double epsilon);

    // Getters for the private variables
    bool checkAutoState()       { return auto_state_;      }
    bool checkManualState()     { return auto_state_;      }
    double getLastCorrection()  { return last_correction_; }
    double getNewTemp()         { return new_temp_;        }

};  // Class "ClimateControl" end

