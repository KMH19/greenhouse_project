#pragma once

/*********************************************************************************************
 * @brief               basePlant class - Enables polymorfism for the other plants
 *********************************************************************************************/
class plant_base
{
private:

public:
virtual double getHeight() = 0;
virtual void grow(int days) = 0;

}; // Class 'plantBase' end