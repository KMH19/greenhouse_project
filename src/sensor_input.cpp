#include <sensor_input.h>



double SensorInput::getTemperature(){
    return temperature;
}

double SensorInput::getAirHumidity(){
    return air_humidity;
}

double SensorInput::getSoilHumidity(){
    return soil_humidity;
}