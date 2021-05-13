#pragma once
#include <vector>

/*********************************************************************************************
 * @brief                   Controls the input variables from installed sensors
 * @param temperature_      Translated from simulation variables
 * @param air_humidity_     Translated from the simulation temperature
 * @param soil_humidity_    Translated from both simulation temperature and humidity
 * @param sensor_error      Error marigin for simulation realistic sensor readings
 *********************************************************************************************/
class SensorInput
{
private:
    double temperature_;
    double air_humidity_;
    double soil_humidity_;

    std::vector<double> sensor_error = {0.01, -0.02, 0.001, 0.01, -0.003, 0.004, 0.008, 0.02, -0.005, 0.09};

public:
    // For function descriptions refer to plant.cpp
    double getTemperature();
    double getAirHumidity();
    double getSoilHumidity();

    void sensorRead(double &temperature, double &air_humidity, double &soil_humidity);

    double sensorDisp();


};


