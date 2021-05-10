#pragma once

class PlantLib
{
private:
    double cactus_info[3] = {1,1,1};
    double tomato_info[3] = {2,2,2};
    double cucumber_info[3] = {3,3,3};
    double paradise_tree_info[3] = {4,4,4};

public:
    PlantLib(/* args */);
    ~PlantLib();
    double GetCactusInfo();
    double GetTomatoInfo();
    double GetCucumberInfo();
    double GetParadiseInfo();
    void GetPlantInfo();
};

