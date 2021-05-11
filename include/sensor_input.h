#pragma once

class SensorInput
{
private:
    double temperature_;
    double air_humidity_;
    double soil_humidity_;

public:
    // SensorInput(/* args */);
    // ~SensorInput();
    double getTemperature();
    double getAirHumidity();
    double getSoilHumidity();

    void sensorRead(double &temperature, double &air_humidity, double &soil_humidity);

};


