#pragma once
#include <string>
#include "plant_base.h"

class Plant : public plant_base 
{
    private:
    double growth_rate_;

    double target_temperature_;

    float height_{0.};

    float max_height_{360};

    public:

    enum plant_type 
    {    
    cactus_plant    = 0, 
    tomato_plant    = 1, 
    cucumber_plant  = 2,
    paradise_tree   = 3
    };

    const char* plant_names[4] = {
        "Cactus Plant",
        "Tomato Plant",
        "Cucumber Plant",
        "Paradise Tree",
    };

    void grow(int days) override;

    void reset()        override;

    float getHeight() override { return height_; };
    float getGrowthRate() { return growth_rate_; };

    Plant::plant_type getPlant() const;

    // std::string getName(Plant& p);


    void setType(Plant::plant_type v, double growth_rate, double target_temperature);

    double GetTargetTemperature() { return target_temperature_; }

    private:
    plant_type type_;
};


            // ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
            // if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
            // {
            //     if (ImGui::BeginTabItem("Avocado"))
            //     {
            //         ImGui::Text("This is the Avocado tab!\nblah blah blah blah blah");
            //         ImGui::EndTabItem();
            //     }
            //     if (ImGui::BeginTabItem("Broccoli"))
            //     {
            //         ImGui::Text("This is the Broccoli tab!\nblah blah blah blah blah");
            //         ImGui::EndTabItem();
            //     }
            //     if (ImGui::BeginTabItem("Cucumber"))
            //     {
            //         ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
            //         ImGui::EndTabItem();
            //     }
            //     ImGui::EndTabBar();
            // }