
#pragma once
#include <vector>
#include "plant.h"
#include "sensor_input.h"

namespace Simulation 
{
class Controls
{
private:
bool fan_c{false};
bool water_c{false};
bool light_c{false};
bool heating_c{false};

double current_temperature{20};
double current_humidity{20};

public:
bool getFan()     { return fan_c;     };
bool getWater()   { return water_c;   };
bool getLight()   { return light_c;   };
bool getHeating() { return heating_c; };

void SimulateOneDay(int days, Plant &p, SensorInput &s);

double getTemp_c()  { return current_temperature; };
double getHum_c()   { return current_humidity; };


};  // Class "Interface" end

class Interface
{
private:

public:
void Init(); 

};



}   // Namespace "Simulation" end