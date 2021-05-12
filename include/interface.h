#pragma once
#include <vector>
#include "plant.h"
#include "sensor_input.h"
#include "climate_control.h"
#include "hardstate_output.h"

namespace Simulation 
{
class Controls
{
private:
bool fan_c{false};
bool water_c{false};
bool light_c{false};
bool heating_c{false};

double temperature_c{20};
double air_humidity_c{20};
double soil_humidity_c{20};

double x;

std::vector<double> temp_sim_c = {15.4, 15.6, 17, 18, 20, 21, 25, 20, 20, 21, 25, 20, 15.4, 15.6, 17, 18, 15.4, 15.6, 17, 18};

public:
bool getFan()     { return fan_c;     };
bool getWater()   { return water_c;   };
bool getLight()   { return light_c;   };
bool getHeating() { return heating_c; };

void SimulateOneDay(int days, Plant& p, SensorInput& s, ClimateControl& c, HardstateOutput& h);

double getTemp_c()      { return temperature_c;   };
double getAirHum_c()    { return air_humidity_c;  };
double getSoilHum_c()   { return soil_humidity_c; };

};  // Class "Interface" end

class Interface
{
private:

public:
void Init(); 

};



}   // Namespace "Simulation" end