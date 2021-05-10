#include <iostream>
#include <plant.h>
#include <climate_control.h>
#include <temperature.h>
#include "interface.h"



int main(int argc, char const *argv[])
{
    // Simulation::Interface gui;
    // gui.Init();
    Plant new_plant;

    new_plant.setType(Plant::cucumber_plant);

    //Plant::plant_type a = new_plant.getPlant();

    std::cout << "Current plant: " << new_plant.getPlant() << std::endl;

    return 0;

}
