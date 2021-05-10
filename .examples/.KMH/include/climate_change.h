#pragma once

namespace Greenhouses {

/*********************************************************************************************
 * @brief                   Climate class for reading and controlling the climate simulation
 * @param temp_             Temperature in climate object
 * @param hum_              Humidity in climate object
 * @param climate_factor_   Climate change factor
 * @param ventilation_      Ventilation factor (should be moved to hardStates)
 *********************************************************************************************/
class Climate {
private:
float temp_{20.0}; 
                        
float hum_{60.0};                         
float climate_factor_{1.04};              
float ventilation_{0.98};                    

public:
//Function to get the temperature
float getTemp() {                               
    return temp_;
};

//Function to get the humidity
float getHumidity() {                           
    return hum_;  
};

void climate_change(int days);

}; // Class 'Climate' end

} // Namsespace 'Greenhouses' end