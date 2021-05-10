
#pragma once
#include <vector>

namespace Simulation 
{
class Controls
{

private:
bool fan_c{false};
bool water_c{false};
bool light_c{false};
bool heating_c{false};

public:
bool getFan()     { return fan_c;     };
bool getWater()   { return water_c;   };
bool getLight()   { return light_c;   };
bool getHeating() { return heating_c; };
};  // Class "Interface" end

class Interface
{
private:

public:
void Init(); 

};



}   // Namespace "Simulation" end