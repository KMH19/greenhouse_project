#include <iostream>
#include <math.h>

#include "climate_control.h"
#include "sensor_input.h"
#include "plant.h"

    bool ClimateControl::approximatelyEqual(double a, double b, double epsilon)
    {
        return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
    }

    bool ClimateControl::essentiallyEqual(double a, double b, double epsilon)
    {
        return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
    }

    bool ClimateControl::definitelyGreaterThan(double a, double b, double epsilon)
    {
        return (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
    }

    bool ClimateControl::definitelyLessThan(double a, double b, double epsilon)
    {
        return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
    }

    void ClimateControl::changeState(bool& i)
    {
        if (i == auto_state_) return;
        auto_state_ = i;
    }

    void ClimateControl::Automatic(SensorInput& s, Plant& p, HardstateOutput& h)
    {

        std::cout << "Sensor display: " << s.getTemperature() << "\370 C" << std::endl << std::endl;

        std::cout << "Target temperature: " << p.GetTargetTemperature() << "\370 C" << std::endl << std::endl;    

        double a = s.getTemperature();
        double b = p.GetTargetTemperature();
        double epsilon = 0.05;

        std::cout << essentiallyEqual(a, b, epsilon) << std::endl;
        std::cout << approximatelyEqual(a, b, epsilon) << std::endl;
        std::cout << definitelyLessThan(b, a, epsilon) << std::endl;
        std::cout << definitelyGreaterThan(b, a, epsilon) << std::endl;

        if (essentiallyEqual(a, b, epsilon) == true || approximatelyEqual(a, b, epsilon) == true)
        {
            return;

        }else if (definitelyGreaterThan(a, b, epsilon) == true)
        {
            std::cout << "temp > target" << std::endl;
            std::cout << fabs(a)-fabs(b) << std::endl;
            std::cout << (fabs(a)-fabs(b))*epsilon << std::endl;

            double diff = fabs(a)-fabs(b);
            double temp = pow(1.5, diff);
            
            if (temp > 100)
            {
                temp = 100;
                
            }else{

                temp = temp;
            }

            h.SetFanSpeed(temp);

            std::cout << "Fanspeed was set to: " << temp << '%' << std::endl;

        }else if (definitelyLessThan(a, b, epsilon) == true)
        {
            
            std::cout << "temp < target" << std::endl;
            std::cout << fabs(b)-fabs(a) << std::endl;
            std::cout << (fabs(b)-fabs(a))*epsilon << std::endl;
            
            double temp = 0;
            h.SetFanSpeed(temp);

            std::cout << "Fanspeed was set to: " << temp << '%' << std::endl;

        }
    }


    void ClimateControl::Manual()
    {
        return;
    }

//double& temperature, double& air_humidity, double& soil_humidity

// void ClimateControl::controlclimate(HardstateOutput &control_output, SensorInput &control_input){    
//     double temperary_temperture = control_input.getTemperature();
//     if(temperary_temperture > target_temperature){
//         control_output.SetFanSpeed(100);
//     }
//     else{
//         control_output.SetFanSpeed(0);
//     }

// }

// Ambition with software:
// Temperature
// Fan control

// The design must use object-oriented elements, involve at least three classes and at least one case of inheritance; the implementation shall involve at least three different object instances.
// You must demonstrate the use of at least one container type from the C++ standard library (vector, list, deque etc.)