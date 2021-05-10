#include "climate_change.h"

/*********************************************************************************************
 * @brief               Climate change function 
 * @param days          Days of growth
 * @return              Nothing (Affects temperature and humidity)
 *********************************************************************************************/
void Greenhouses::Climate::climate_change(int days){                    
temp_ = temp_ + (days * climate_factor_ * ventilation_);
hum_ = hum_ - (days - climate_factor_ - ventilation_);
};


