#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <math.h>

#include "interface.h"

#include "SFML/Graphics.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include "interface.h"
#include "plant.h"
#include "sensor_input.h"
#include "climate_control.h"
#include "hardstate_output.h"

    float stalk_length = 0.;

    bool fan_c = false;
    bool heating_c = false;
    bool water_c = false;
    bool light_c = false;

    void Simulation::Controls::setTemp_i(double& temperature)
    {
        if (temperature == temperature_i) return;
            temperature_i = temperature;
    }

    void Simulation::Controls::setAirHum_i(double& air_humidity)
    {
        if (air_humidity == air_humidity_i) return;
            air_humidity_i = air_humidity;
    }

    void Simulation::Controls::setSoilHum_i(double& soil_humidity)
    {
        if (soil_humidity == soil_humidity_i) return;
            soil_humidity_i = soil_humidity;
    }

    void Simulation::Controls::setDay(int &d)
    {
        d = current_day_;
    }

        void Simulation::Controls::resetDay()
    {
        current_day_ = 0;
    }

    void Simulation::Controls::Simulate(int i, Plant& p, SensorInput& s, ClimateControl& c, HardstateOutput& h, Controls& sim)
    {
        std::cout << "Day no.: " << sim.getDay() << std::endl;
        std::cout << "-----------------------" << std::endl << std::endl;

        p.grow(1);

        double x = temp_sim_c[i];

        // This tells the current air humidity (Polynomial factor)
        air_humidity_c = 0.1*pow(x,2)+10;

        // This tells the current soil humidity, based on atmospheric temperature and humidity (Polynomial factor)
        soil_humidity_c = 0.005*pow(x,2);

        s.sensorRead(temp_sim_c[i], air_humidity_c, soil_humidity_c);   

        std::cout << "Plant height: " << p.getHeight() << std::endl << std::endl;

        std::cout << "Current temperature: " << temp_sim_c[i] << std::endl << std::endl;

        std::cout << "Current air humidity: " << air_humidity_c << std::endl << std::endl;

        std::cout << "Current soil humidity: " << soil_humidity_c << std::endl << std::endl;
        
        if (c.checkAutoState() == true)
        {
            double internal_correction = c.Automatic(s, p, h);

            if (c.approximatelyEqual(0, internal_correction, 0.05))
            {

                std::cout << "Internal temperature was not corrected (0)" << std::endl << std::endl; 

            }else{

                sim.setTemp_i(internal_correction);

                std::cout << "Internal temperature was corrected to: " << internal_correction << std::endl << std::endl; 

            }
            
        }else{

            c.Manual();

        }
    }

    void Simulation::Controls::SimulateDays(int days_, Plant& p, SensorInput& s, ClimateControl& c, HardstateOutput& h, Controls& sim) 
    {

        if (days_ == 1) {

            current_day_ += 1;
            int iRand = rand() % 19;
            sim.Simulate(iRand, p, s, c, h, sim);

        }else{
            current_day_ += days_;

            for (int i = 0; i < days_; i++)
            {
                sim.Simulate(i, p, s, c, h, sim);
            }

            std::cout << sim.SimDays << std::endl << std::endl;
            std::cout << days_ << std::endl << std::endl;
            std::cout << current_day_ << std::endl;
        }

    }

void Simulation::Interface::Init(Plant& p, SensorInput& s, ClimateControl& c, HardstateOutput& h, Controls& sim) 
{

    sf::RectangleShape tomato_stalk {sf::Vector2f{5.0, p.getHeight()}};
    tomato_stalk.setPosition(512, 384);
    tomato_stalk.setRotation(180);
    tomato_stalk.setFillColor(sf::Color{0, 255, 0});

    sf::RectangleShape tomato_stalk2 {sf::Vector2f{5.0, 75}};
    tomato_stalk2.setPosition(512, 300);
    tomato_stalk2.setRotation(150);
    tomato_stalk2.setFillColor(sf::Color{0, 255, 0});

    sf::RectangleShape tomato_stalk3 {sf::Vector2f{5.0, 75}};
    tomato_stalk3.setPosition(512, 300);
    tomato_stalk3.setRotation(-150);
    tomato_stalk3.setFillColor(sf::Color{0, 255, 0});

    sf::RectangleShape tomato_stalk4 {sf::Vector2f{5.0, 90}};
    tomato_stalk4.setPosition(512, 200);
    tomato_stalk4.setRotation(150);
    tomato_stalk4.setFillColor(sf::Color{0, 255, 0});

    sf::RectangleShape tomato_stalk5 {sf::Vector2f{5.0, 100}};
    tomato_stalk5.setPosition(512, 200);
    tomato_stalk5.setRotation(-150);
    tomato_stalk5.setFillColor(sf::Color{0, 255, 0});

    // create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");
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
        if (ImGui::CollapsingHeader("Help"))
        {
            ImGui::Text("USAGE:");
            ImGui::BulletText("Use the hardstates windows to turn fan, heating, watering or light (on/off), \n");
            ImGui::Separator();
        }
        if (ImGui::CollapsingHeader("Control"))
        {
        static bool e = true;
        if (ImGui::RadioButton("Manual", e==false)) 
            { 
            e = false;
            c.changeState(e); 
            }

        ImGui::SameLine();

        if (ImGui::RadioButton("Automatic", e==true)) 
            {
            e = true; 
            c.changeState(e); 
            }

            // Breakpoint KMH

        }
        // if (ImGui::CollapsingHeader("Plant length"))
        // {
        //     if (ImGui::SliderFloat("Height", &stalk_length, 0., 300.)) 
        // {
        //     tomato_stalk.setSize(sf::Vector2f{5.0, stalk_length});
        // }
        // }
        if (ImGui::CollapsingHeader("Simulation"))
        {
        ImGui::Text("Choose between one-day simulation or series below:");
        ImGui::Separator();
        ImGui::Text("The current day is: %i", sim.getDay());
        ImGui::Separator();
        if (ImGui::TreeNode("One day"))
        {
        if (ImGui::Button("Simulate"))
        {
            sim.SimulateDays(1, p, s, c, h, sim);
        }
        ImGui::SameLine();

        ImGui::PushID(3);
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(7.0f, 0.8f, 0.8f));
        if (ImGui::Button("Reset plant / time"))
        {
            p.reset();
            sim.resetDay();
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();

        ImGui::TreePop();
        }
        if (ImGui::TreeNode("Several days"))
        {
        if (ImGui::SliderInt("Days", &sim.SimDays, 1, 20)) {}

            if (ImGui::Button("Simulate"))
            {
                sim.SimulateDays(sim.SimDays, p, s, c, h, sim);
            }

            ImGui::SameLine();

            ImGui::PushID(4);
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.7f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(7.0f, 0.8f, 0.8f));
            if (ImGui::Button("Reset plant / time"))
            {
                p.reset();
                sim.resetDay();
            }
            ImGui::PopStyleColor(3);
            ImGui::PopID();

        ImGui::TreePop();
        }
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
        ImGui::End();

        // clear the window with black color
        window.clear(sf::Color::Black);

        // if (fan_c == true)
        // {
        //     sim.SimulateOneDay(1, p, s, c, h, sim);
        // }
        
        if (p.getHeight() < 85)
        {
        window.draw(tomato_stalk);
        }else if (p.getHeight() < 199)
        {
        window.draw(tomato_stalk);
        window.draw(tomato_stalk2);
        window.draw(tomato_stalk3);
        }else if (p.getHeight() < 301)
        {
        window.draw(tomato_stalk);
        window.draw(tomato_stalk2);
        window.draw(tomato_stalk3);
        window.draw(tomato_stalk4);
        window.draw(tomato_stalk5);
        }

        ImGui::SFML::Render(window);

        // end the current frame
        window.display();
    }
} 



