#pragma once

namespace Greenhouses {

/*********************************************************************************************
 * @brief           Hardstates class (Currently not used initialized as false)
 * @param heat_     Heating controller
 * @param fan_      Fan controller
 * @param pump_     Pump controller
 *********************************************************************************************/
class hardStates {
private:
bool heat_{false};                          
bool fan_{false};                         
bool pump_{false};                    

public:

void hardState_change(int i);


}; // Class 'hardStates' end

} // Namespace 'Greenhouses' end
