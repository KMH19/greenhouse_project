#include <iostream>
#include <math.h>

#include "climate_control.h"

    // Comparison of double values
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
        manual_state_ = !i;
    }

    double ClimateControl::Automatic(SensorInput& s, Plant& p, HardstateOutput& h)
    {

        std::cout << "Sensor display: " << s.getTemperature() << "\370 C" << std::endl << std::endl;

        std::cout << "Target temperature: " << p.GetTargetTemperature() << "\370 C" << std::endl << std::endl;    

        double a = s.getTemperature();
        double b = p.GetTargetTemperature();
        double epsilon = 0.05;

        std::cout << essentiallyEqual(a, b, epsilon) << std::endl;
        std::cout << approximatelyEqual(a, b, epsilon) << std::endl;
        std::cout << definitelyLessThan(b, a, epsilon) << std::endl;
        std::cout << definitelyGreaterThan(b, a, epsilon) << std::endl << std::endl;

        if (essentiallyEqual(a, b, epsilon) == true || approximatelyEqual(a, b, epsilon) == true)
        {
            last_correction_ = 0.;

        }else if (definitelyGreaterThan(a, b, epsilon) == true)
        {
            std::cout << "temp > target" << std::endl;
            std::cout << fabs(a)-fabs(b) << std::endl;
            std::cout << (fabs(a)-fabs(b))*epsilon << std::endl;

            // Linear function fan control
            double diff = fabs(a)-fabs(b);
            double temp = 10*diff;
            
            if (temp > 100)
            {

                temp = 100;
                
            }else{

                temp = temp;
            }

            h.SetFanSpeed(temp);

            // Correction of internal temperature according to fan efficiency
            last_correction_ = fabs(a)-fabs(b)*h.GetFanEfficiency();
            new_temp_ = a - last_correction_;


            std::cout << "Fanspeed was set to: " << temp << '%' << std::endl;

        }else if (definitelyLessThan(a, b, epsilon) == true)
        {

            std::cout << "temp < target" << std::endl;
            std::cout << fabs(b)-fabs(a) << std::endl;
            std::cout << (fabs(b)-fabs(a))*epsilon << std::endl;
            
            double temp = 0;
            h.SetFanSpeed(temp);

            std::cout << "Fanspeed was set to: " << temp << '%' << std::endl;

            // Heating could be added here (Not considered at this point)
            last_correction_ = 0.;
            new_temp_ = a;

        }
        return last_correction_;
    }


    void ClimateControl::Manual()
    {
        std::cout << "Manual control not available" << std::endl;
        return;
    }

// Ambition with software:
// Temperature
// Fan control

// The design must use object-oriented elements, involve at least three classes and at least one case of inheritance; the implementation shall involve at least three different object instances.
// You must demonstrate the use of at least one container type from the C++ standard library (vector, list, deque etc.)