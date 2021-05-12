#pragma once
#include <vector>

class SensorInput
{
private:
    double temperature_;
    double air_humidity_;
    double soil_humidity_;

    // Deviation of the measured value from the actual value of the property being measured (Factor based)
    std::vector<double> sensor_error = {0.001, -0.002, 0.0001, 0.01, -0.003, 0.004, 0.008, 0.02, -0.005, 0.009};

public:
    double getTemperature();
    double getAirHumidity();
    double getSoilHumidity();

    double sensorDisp();

    void sensorRead(double &temperature, double &air_humidity, double &soil_humidity);
};


