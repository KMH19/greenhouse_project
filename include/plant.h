#pragma once

    class Plant
    {

    private:
    double growth_rate;

    double target_temperature;

    double height;

    int stalks; 

    public:

    enum plant_type 
    {    
    cactus_plant    = 0, 
    tomato_plant    = 1, 
    cucumber_plant  = 2,
    paradise_tree   = 3
    };

    Plant::plant_type getPlant() const;
    void setType(Plant::plant_type v);

    double GetTargetTemperature() { return target_temperature; }

    void grow(int days);

    private:
    plant_type type_;

    

    };


