#pragma once

namespace Greenhouses {

/*********************************************************************************************
 * @brief               basePlant class - Enables polymorfism for the other plants
 *********************************************************************************************/
class plantBase
{
private:

public:
virtual double getHeight() = 0;
virtual void grow(int days) = 0;

}; // Class 'plantBase' end

} // Namespace 'Greenhouses' end 
