#include <plant.h>
#include <climate_control.h>
#include <temperature.h>

int main(int argc, char const *argv[])
{
    /* code */
    int k = 5;
    Plant new_plant;
    new_plant.SetPlantType();
    TempSensor t;
    Control ctrl(new_plant, t);
    
    return 0;
    //hahahhahahahahha
}

Control::Control(Plant& p, TempSensor& t_senor) {
    t_sensor.getTemperature()
}