#include <iostream>
#include <math.h>

#include "climate_control.h"

    // std::cout << "Is used for logging to external console" << std::endl;

    // The essentials about the next (4) functions, is that they evaluate two parameters 
    // Against an epsilon value, to determine their differences or lack of the same.
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

    // Changes states of the auto and manual boolean (flip/flop)
    void ClimateControl::changeState(bool& i)
    {
        if (i == auto_state_) return;
        auto_state_ = i;
        manual_state_ = !i;
    }

    // The automatic function for controlling the climate within the greennhouse
    double ClimateControl::Automatic(SensorInput& s, Plant& p, HardstateOutput& h)
    {

        std::cout << "Sensor display: " << s.getTemperature() << "\370 C" << std::endl << std::endl;

        std::cout << "Target temperature: " << p.GetTargetTemperature() << "\370 C" << std::endl << std::endl;    

        double a = s.getTemperature();
        double b = p.GetTargetTemperature();
        double epsilon = 0.05;

        if (essentiallyEqual(a, b, epsilon) == true || approximatelyEqual(a, b, epsilon) == true)
        {
            last_correction_ = 0.;

        }else if (definitelyGreaterThan(a, b, epsilon) == true)
        {

            // Fan control (Linear function)
            double diff = fabs(a)-fabs(b);
            double temp = 10*diff;
            
            if (temp > 100)
            {

                temp = 100;
                
            }else{

                temp = temp;
            }

            // Set fan speed to the temporary variables
            h.SetFanSpeed(temp);

            // Correction of internal temperature according to fan efficiency
            last_correction_ = fabs(a)-fabs(b)*h.GetFanEfficiency();
            new_temp_ = a - last_correction_;

            std::cout << "Fanspeed was set to: " << temp << '%' << std::endl;

        }else if (definitelyLessThan(a, b, epsilon) == true)
        {
            
            double temp = 0;
            h.SetFanSpeed(temp);

            std::cout << "Fanspeed was set to: " << temp << '%' << std::endl;

            // Heating could be added here (Not considered at this point)
            last_correction_ = 0.;
            new_temp_ = a;

        }
        return last_correction_;
    }

    // Only implemented to tell that it is not ATM
    void ClimateControl::Manual()
    {
        std::cout << "Manual control not available" << std::endl;
        return;
    }

