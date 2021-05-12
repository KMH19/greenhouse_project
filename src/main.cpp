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


    plant_entity.setType(Plant::cucumber_plant, 0.5, 15);

    std::cout << "Current plant: " << plant_entity.getPlant() << std::endl;

    sim.SimulateOneDay(10, plant_entity, sensor1, c, h, sim);

    Simulation::Interface gui;
    gui.Init();
    
    return 0;
}
