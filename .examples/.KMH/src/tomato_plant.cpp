#include <tomato_plant.h> 

/*********************************************************************************************
 * @brief               tomatoPlant growth function 
 * @param days          Days of growth
 * @return              Nothing (Affects plant height)
 *********************************************************************************************/
void Greenhouses::tomatoPlant::grow(int days) {
height_ = height_ + days * growth_rate_;
};
