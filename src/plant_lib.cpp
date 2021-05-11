#include <plant_lib.h>

void PlantLib::GetPlantInfo(int plant_number, double &grow_rate, double &target_temperature ){
    grow_rate = plant_info[plant_number][0];
    target_temperature = plant_info[plant_number][1];

}
