
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

class Stalks 
{
private:
float size{0.};

public:
bool getSize()     { return size;     };

void addStalk(float  &setStalks_c) {}
void growStalk(float &amount) {}
};

}   // Namespace "Simulation" end