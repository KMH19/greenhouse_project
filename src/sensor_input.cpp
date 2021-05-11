#include <sensor_input.h>

double SensorInput::getTemperature(){
    return temperature_ ;
}

double SensorInput::getAirHumidity(){
    return air_humidity_;
}

double SensorInput::getSoilHumidity(){
    return soil_humidity_;
}

void SensorInput::sensorRead(double &temperature, double &air_humidity, double &soil_humidity)
{
    if (temperature == temperature_) return;
    temperature_ = temperature;

    if (air_humidity == air_humidity_) return;
    air_humidity_ = air_humidity;

    if (soil_humidity == soil_humidity_) return;
    soil_humidity_ = soil_humidity;
}

