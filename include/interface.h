#pragma once

#include <vector>

#include "interface.h"
#include "plant.h"
#include "sensor_input.h"
#include "climate_control.h"
#include "hardstate_output.h"

/*********************************************************************************************
 * @brief                  namespace Simulation contains both the Controls and Interface class
 *********************************************************************************************/
namespace Simulation 
{

/*********************************************************************************************
 * @brief                   Controls simulation of temperature (outside/inside) of greenhouse      
 * @param current_day_      The current day under simulation
 * @param temperature_      _c = outside the greenhouse, _i = inside the greenhouse
 * @param air_humidity_     Same as above
 * @param soil_humidity_    Same as above
 * @param temp_sim_c        Temperature values for day-by-day simulation
 * 
 * @param first_popup       Used for interface control of welcome popup
 * @param SimDays           Used for interface control of selected days
 *********************************************************************************************/
class Controls
{
private:

    int current_day_{0};

    double temperature_c{20};
    double air_humidity_c{50};
    double soil_humidity_c{2};

    double temperature_i;
    double air_humidity_i;
    double soil_humidity_i;

    std::vector<double> temp_sim_c = {15.4, 15.6, 17, 18, 20, 21, 25, 20, 20, 21, 25, 20, 15.4, 15.6, 17, 18, 15.4, 15.6, 17, 18};

public:
    bool first_popup{true};
    int sim_days{1};

    // For function descriptions refer to src/interface.cpp
    void SimulateDays(int days, Plant& p, SensorInput& s, ClimateControl& c, HardstateOutput& h, Controls& sim);
    void Simulate(int i, Plant& p, SensorInput& s, ClimateControl& c, HardstateOutput& h, Controls& sim);

    void setTemp_i(double& temperature);
    void setAirHum_i(double& air_humidity);
    void setSoilHum_i(double& soil_humidity);

    void setDay(int &d);
    void resetDay();

    // Getters for the private variables
    double getTemp_c()      { return temperature_c;   };
    double getAirHum_c()    { return air_humidity_c;  };
    double getSoilHum_c()   { return soil_humidity_c; };

    double getTemp_i()      { return temperature_i;   };
    double getAirHum_i()    { return air_humidity_i;  };
    double getSoilHum_i()   { return soil_humidity_i; };

    int getDay()            { return current_day_;    };


};  // Class "Controls" end

/*********************************************************************************************
 * @brief                   Interface class - used for initialising the interface      
 *********************************************************************************************/
class Interface
{
private:

public:
    void Init(Plant& p, SensorInput& s, ClimateControl& c, HardstateOutput& h, Controls& sim); 

};  // Class "Interface" end
}   // Namespace "Simulation" end