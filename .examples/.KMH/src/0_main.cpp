#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

#include "climate_change.h"
#include "hard_states.h"
#include "tomato_plant.h"
#include "cucumber_plant.h"

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

Greenhouses::tomatoPlant tp_1;
Greenhouses::tomatoPlant tp_2;
Greenhouses::tomatoPlant tp_3;

Greenhouses::cucumberPlant cp_1;
Greenhouses::cucumberPlant cp_2;
Greenhouses::cucumberPlant cp_3;

std::vector<Greenhouses::tomatoPlant>   tomatoPlants;
std::vector<Greenhouses::cucumberPlant> cucumberPlants;

void simulateOneDay(
    std::vector<Greenhouses::tomatoPlant>   &t_vector, 
    std::vector<Greenhouses::cucumberPlant> &c_vector,
    int days) 
{
    using namespace std::chrono_literals;
    for (int i = 0; i < days; i++)
    {
        std::cout << "Day no.: " << 1+i << std::endl;
        std::cout << "-----------------------" << std::endl << std::endl;

        for (int j = 0; j < t_vector.size(); j++)
        {
            t_vector[j].grow(1);
            std::cout << "Tomato plant no.:" << j << std::endl; 
            std::cout << "Height: " << t_vector[j].getHeight() << " cm" << std::endl << std::endl;
        }

        for (int k = 0; k < c_vector.size(); k++)
        {
            c_vector[k].grow(1);
            std::cout << "Cucumber plant no.:" << k << std::endl; 
            std::cout << "Height: " << c_vector[k].getHeight() << " cm" << std::endl << std::endl;
        }   // Grow end
        
    std::this_thread::sleep_for(2s);

    }       // Days end
}           // Function end

void plantPlanter() {
    tomatoPlants.push_back(tp_1);
    tomatoPlants.push_back(tp_2);
    tomatoPlants.push_back(tp_3);

    cucumberPlants.push_back(cp_1);
    cucumberPlants.push_back(cp_2);
    cucumberPlants.push_back(cp_3);
}           // Function end


int main(int argc, char const *argv[])
{
    //Creating an object of the climate and hardstate class
    // // Greenhouses::Climate    Greenhouse1;
    // // Greenhouses::hardStates hardwareStates;

    // // plantPlanter();

    // // simulateOneDay(tomatoPlants, cucumberPlants, 3);

    float stalk_length = 0.;
    float stalk_length2 = 0.;

    bool fan_c = false;
    bool heating_c = false;
    bool water_c = false;
    bool light_c = false;

    sf::RectangleShape tomato_stalk {sf::Vector2f{5.0, stalk_length}};
    sf::RectangleShape tomato_stalk2 {sf::Vector2f{5.0, stalk_length2}};
    tomato_stalk.setPosition(512, 384);
    tomato_stalk.setRotation(180);
    tomato_stalk.setFillColor(sf::Color{0, 255, 0});
    tomato_stalk2.setPosition(512, 384);
    tomato_stalk2.setRotation(160);
    tomato_stalk2.setFillColor(sf::Color{255, 255, 0});

    // create the window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "My window");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    // run the program as long as the window is open
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
        ImGui::Begin("Menu");
        if (ImGui::CollapsingHeader("Plant length"))
        {
            if (ImGui::SliderFloat("Length", &stalk_length, 0., 300.)) {
        }
        }
        if (ImGui::CollapsingHeader("Help"))
        {
            ImGui::Text("USAGE:");
            ImGui::BulletText("Use the hardstates windows to turn fan, heating, watering or light (on/off), \n");
            ImGui::Separator();
        }
        if (ImGui::CollapsingHeader("Hardstates"))
        {
            if (ImGui::BeginTable("split", 4))
            {
                ImGui::TableNextColumn(); ImGui::Checkbox("Fan",        &fan_c);
                ImGui::TableNextColumn(); ImGui::Checkbox("Heating",    &heating_c);
                ImGui::TableNextColumn(); ImGui::Checkbox("Watering",   &water_c);
                ImGui::TableNextColumn(); ImGui::Checkbox("Light",      &light_c);
                ImGui::EndTable();
            }
        }
        if (ImGui::CollapsingHeader("Climate"))
        {
        if (ImGui::TreeNode("Temperature"))
        {
        static bool animate = true;
        ImGui::Checkbox("Animate", &animate);

        static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
        ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));

        // Fill an array of contiguous float values to plot
        // Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float
        // and the sizeof() of your structure in the "stride" parameter.
        static float values[90] = {};
        static int values_offset = 0;
        static double refresh_time = 0.0;
        if (!animate || refresh_time == 0.0)
            refresh_time = ImGui::GetTime();
        while (refresh_time < ImGui::GetTime()) // Create data at fixed 60 Hz rate for the demo
        {
            static float phase = 0.0f;
            values[values_offset] = cosf(phase);
            values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
            phase += 0.10f * values_offset;
            refresh_time += 1.0f / 60.0f;
        }

        // Plots can display overlay texts
        // (in this example, we will display an average value)
        {
            float average = 0.0f;
            for (int n = 0; n < IM_ARRAYSIZE(values); n++)
                average += values[n];
            average /= (float)IM_ARRAYSIZE(values);
            char overlay[32];
            sprintf(overlay, "avg %f", average);
            ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, overlay, -1.0f, 1.0f, ImVec2(0, 80.0f));
        }
        ImGui::TreePop();
        }
        if (ImGui::TreeNode("Humidity"))
        {
        static bool animate = true;
        ImGui::Checkbox("Animate", &animate);

        static float arr[] = { 10.0f, 11.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f };
        ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));

        // Fill an array of contiguous float values to plot
        // Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float
        // and the sizeof() of your structure in the "stride" parameter.
        static float values[90] = {};
        static int values_offset = 0;
        static double refresh_time = 0.0;
        if (!animate || refresh_time == 0.0)
            refresh_time = ImGui::GetTime();
        while (refresh_time < ImGui::GetTime()) // Create data at fixed 60 Hz rate for the demo
        {
            static float phase = 1.0f;
            values[values_offset] = sinf(phase);
            values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
            phase += 0.10f * values_offset;
            refresh_time += 1.0f / 60.0f;
        }

        // Plots can display overlay texts
        // (in this example, we will display an average value)
        {
            float average = 0.0f;
            for (int n = 0; n < IM_ARRAYSIZE(values); n++)
                average += values[n];
            average /= (float)IM_ARRAYSIZE(values);
            char overlay[32];
            sprintf(overlay, "avg %f", average);
            ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, overlay, -1.0f, 1.0f, ImVec2(0, 80.0f));
        }
        ImGui::TreePop();
        }
                if (ImGui::TreeNode("Air flow"))
        {
        static bool animate = true;
        ImGui::Checkbox("Animate", &animate);

        static float arr[] = { 1.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.9f };
        ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));

        // Fill an array of contiguous float values to plot
        // Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float
        // and the sizeof() of your structure in the "stride" parameter.
        static float values[90] = {};
        static int values_offset = 0;
        static double refresh_time = 0.0;
        if (!animate || refresh_time == 0.0)
            refresh_time = ImGui::GetTime();
        while (refresh_time < ImGui::GetTime()) // Create data at fixed 60 Hz rate for the demo
        {
            static float phase = 0.0f;
            values[values_offset] = cosf(phase);
            values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
            phase += 0.10f * values_offset;
            refresh_time += 1.0f / 60.0f;
        }

        // Plots can display overlay texts
        // (in this example, we will display an average value)
        {
            float average = 0.0f;
            for (int n = 0; n < IM_ARRAYSIZE(values); n++)
                average += values[n];
            average /= (float)IM_ARRAYSIZE(values);
            char overlay[32];
            sprintf(overlay, "avg %f", average);
            ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, overlay, -1.0f, 1.0f, ImVec2(0, 80.0f));
        }
        ImGui::TreePop();
        }
        }

        if (ImGui::CollapsingHeader("Plant attributes"))
        {
        if (ImGui::TreeNode("Plant selector"))
        {
        ImGui::TextWrapped("Choose from the available options below");

        if (ImGui::Button("Clear plant selection"))
            ImGui::OpenPopup("Clear?");

        // Always center this window when appearing
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal("Clear?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Are you sure that you want to clear the current plant?\nThis operation cannot be undone!\n\n");
            ImGui::Separator();

            static bool dont_ask_me_next_time = false;
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
            ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
            ImGui::PopStyleVar();

            if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::EndPopup();
        }

        if (ImGui::Button("Select plant"))
            ImGui::OpenPopup("Plant selection");
        if (ImGui::BeginPopupModal("Plant selection", NULL, ImGuiWindowFlags_MenuBar))
        {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Close")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::Text("This is where the current plant is selected\nRemember to set the initial height of the plant.");

        // Testing behavior of widgets stacking their own regular popups over the modal.
        static int item = 1;
        static float color[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
        ImGui::Combo("Combo", &item, "Cucumber\0Tomato\0Chili\0\0");

        if (ImGui::Button("Select plant size"))
            ImGui::OpenPopup("Plant size");

        // Also demonstrate passing a bool* to BeginPopupModal(), this will create a regular close button which
        // will close the popup. Note that the visibility state of popups is owned by imgui, so the input value
        // of the bool actually doesn't matter here.
        bool unused_open = true;
        if (ImGui::BeginPopupModal("Plant size", &unused_open))
        {
            if (ImGui::SliderFloat("Length", &stalk_length, 0., 100.)) {

                tomato_stalk.setSize(sf::Vector2f{5.0, stalk_length});

            }
            ImGui::Text("The initial plant size is set here");
            if (ImGui::Button("Close"))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }

        if (ImGui::Button("Close"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
        }

        ImGui::TreePop();
        }
        }

        ImGui::End();

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(tomato_stalk);

        ImGui::SFML::Render(window);

        // end the current frame
        window.display();

    }
    return 0;
}   //Main end