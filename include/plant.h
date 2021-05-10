#pragma once
#include <string>

class Plant
{
private:
    double grow_rate;
    std::string plant_type;
public:
    Plant(/* args */);
    ~Plant();
    void GetCurrentPlantInfo();
    void SetPlantType();

};

Plant::Plant(/* args */)
{
}

Plant::~Plant()
{
}
