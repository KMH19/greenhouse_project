#pragma once

#include <vector>

#include "interface.h"
#include "plant.h"
#include "sensor_input.h"
#include "climate_control.h"
#include "hardstate_output.h"

namespace Simulation 
{
class Controls
{
private:
bool fan_c{true};
bool water_c{false};
bool light_c{false};
bool heating_c{false};

int current_day_{0};
// int sim_days_{0};

// Global temperature -> Fan speed -> Difference -> Local temperature
// Temperature outside the greenhouse
double temperature_c{20};
double air_humidity_c{20};
double soil_humidity_c{20};

//temperature inside the greenhouse
double temperature_i;
double air_humidity_i;
double soil_humidity_i;

double x;

std::vector<double> temp_sim_c = {15.4, 15.6, 17, 18, 20, 21, 25, 20, 20, 21, 25, 20, 15.4, 15.6, 17, 18, 15.4, 15.6, 17, 18};

public:
bool first_popup{true};

int SimDays{1};

bool getFan()           { return fan_c;           };
bool getWater()         { return water_c;         };
bool getLight()         { return light_c;         };
bool getHeating()       { return heating_c;       };

void SimulateDays(int days, Plant& p, SensorInput& s, ClimateControl& c, HardstateOutput& h, Controls& sim);
void Simulate(int i, Plant& p, SensorInput& s, ClimateControl& c, HardstateOutput& h, Controls& sim);

double getTemp_c()      { return temperature_c;   };
double getAirHum_c()    { return air_humidity_c;  };
double getSoilHum_c()   { return soil_humidity_c; };

double getTemp_i()      { return temperature_i;   };
double getAirHum_i()    { return air_humidity_i;  };
double getSoilHum_i()   { return soil_humidity_i; };

void setTemp_i(double& temperature);
void setAirHum_i(double& air_humidity);
void setSoilHum_i(double& soil_humidity);

// int setSimDays(int &d);
// int getSimDays()        { return sim_days_;       };
void setDay(int &d);
void resetDay();
int getDay()            { return current_day_;    };


};  // Class "Interface" end

class Interface
{
private:

public:
void Init(Plant& p, SensorInput& s, ClimateControl& c, HardstateOutput& h, Controls& sim); 

};
}   // Namespace "Simulation" end