#include <iostream>

#include "plant.h"
#include "interface.h"
#include "sensor_input.h"
#include "climate_control.h"

int main(int argc, char const *argv[])
{

    Plant plant_entity;
    SensorInput sensor1;
    ClimateControl c;
    HardstateOutput h;

    Simulation::Controls sim;
    Simulation::Interface gui;

    plant_entity.setType(Plant::cucumber_plant, 2, 15);

    std::cout << "Initializing GUI.." << std::endl;

    // Startup of the GUI
    gui.Init(plant_entity, sensor1, c, h, sim);
    
    return 0;
}
