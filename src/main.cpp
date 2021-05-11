#include <iostream>

#include "plant.h"
#include "interface.h"
#include "temperature.h"
#include "sensor_input.h"
#include "climate_control.h"


int main(int argc, char const *argv[])
{
    Plant plant_entity;

    Simulation::Controls sim;
    
    SensorInput sensor1;

    plant_entity.setType(Plant::cucumber_plant, 0.5, 25);

    

    std::cout << "Current plant: " << plant_entity.getPlant() << std::endl;

    sim.SimulateOneDay(10, plant_entity, sensor1);

    // Simulation::Interface gui;
    // gui.Init();
    
    return 0;
}
