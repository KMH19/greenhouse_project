#pragma once

class SensorInput
{
private:
    double temperature;
    double air_humidity;
    double soil_humidity;

public:
    // SensorInput(/* args */);
    // ~SensorInput();
    double getTemperature();
    double getAirHumidity();
    double getSoilHumidity();
};


