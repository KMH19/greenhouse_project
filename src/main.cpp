#include <iostream>
#include "plant.h"
#include "climate_control.h"
#include "temperature.h"
#include "interface.h"


int main(int argc, char const *argv[])
{
    Plant new_plant;

    new_plant.setType(Plant::cucumber_plant, 0.5, 25);

    std::cout << "Current plant: " << new_plant.getPlant() << std::endl;

    Simulation::Interface gui;
    gui.Init();
    
    return 0;
}
