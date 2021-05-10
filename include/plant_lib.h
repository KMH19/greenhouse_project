#pragma once

class PlantLib
{
private:
    double plant_info[4][2] = {{1,1},{2,2},{3,3},{4,4}};
    double tomato_info[2] = {2,2};
    double cucumber_info[2] = {3,3};
    double paradise_tree_info[2] = {4,4};
    double cactus_info[2] = {1,1};

public:
    PlantLib(/* args */);
    ~PlantLib();
    double GetCactusInfo();
    double GetTomatoInfo();
    double GetCucumberInfo();
    double GetParadiseInfo();
    void GetPlantInfo(int plant_number);
};

