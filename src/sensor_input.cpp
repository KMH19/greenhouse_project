#include <sensor_input.h>

// In the following (3) getter functions, we randomize a number between 0 and 9 
// This is used to subtract the sensor error before returning
double SensorInput::getTemperature(){
    int iRand = rand() % 9;
    return temperature_-sensor_error[iRand];
}

double SensorInput::getAirHumidity(){
    int iRand = rand() % 9;
    return air_humidity_-sensor_error[iRand];
}

double SensorInput::getSoilHumidity(){
    int iRand = rand() % 9;
    return soil_humidity_-sensor_error[iRand];
}

// Used to read values to the sensor
void SensorInput::sensorRead(double &temperature, double &air_humidity, double &soil_humidity)
{
    if (temperature == temperature_) return;
    temperature_ = temperature;

    if (air_humidity == air_humidity_) return;
    air_humidity_ = air_humidity;

    if (soil_humidity == soil_humidity_) return;
    soil_humidity_ = soil_humidity;
}
