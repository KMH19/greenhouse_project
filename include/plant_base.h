#pragma once

/*********************************************************************************************
 * @brief               basePlant class - Enables polymorfism for the other plants
 *********************************************************************************************/
class plant_base
{
private:

public:
    virtual float getHeight() = 0;
    virtual void grow(int days) = 0;
    virtual void reset() = 0;

}; // Class 'plantBase' end