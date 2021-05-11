

#pragma once

    class Plant
    {

    private:
    double growth_rate_;

    double target_temperature_;

    double height_{0};

    int stalks_{10}; 

    public:

    enum plant_type 
    {    
    cactus_plant    = 0, 
    tomato_plant    = 1, 
    cucumber_plant  = 2,
    paradise_tree   = 3
    };

    Plant::plant_type getPlant() const;
    void setType(Plant::plant_type v, double growth_rate, double target_temperature);

    double GetTargetTemperature() { return target_temperature_; }

    void grow(int days);

    double getHeight() { return height_; };

    private:
    plant_type type_;
    };