#pragma once
#include <plant_base.h>

namespace Greenhouses {

/*********************************************************************************************
 * @brief               tomatoPlant class - for controlling plant growth
 * @param height_       Plant object height
 * @param num_tomatoes_ Number of tomatoes on plant object (currently not used)
 * @param growth_rate_  Rate of growth (affects height)
 *********************************************************************************************/
class tomatoPlant : public plantBase {
private:
double height_{0.0};                            //Plant height
int num_tomates_{0};                            //Number of tomates on the plant
double growth_rate_{1.2};                       //Rate of growth

public:
double getHeight() override { return height_; };
int getNumTomatoes() { return num_tomates_; };

void grow(int days) override;

};  // Class 'tomatoPlant' end 

}   // Namespace 'Greenhouses' end