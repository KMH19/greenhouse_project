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

    sf::RectangleShape tube;
    tube.setSize(sf::Vector2f(190, 700));
    tube.setFillColor(sf::Color::Transparent);
    tube.setOutlineColor(sf::Color::White);
    tube.setOutlineThickness(5);
    tube.setPosition(115, 15);

    sf::RectangleShape glass;
    glass.setSize(sf::Vector2f(180, 480));
    glass.setFillColor(sf::Color::Transparent);
    glass.setOutlineColor(sf::Color::White);
    glass.setOutlineThickness(1);
    glass.setPosition(120, 20);

    sf::RectangleShape door;
    door.setSize(sf::Vector2f(120, 160));
    door.setFillColor(sf::Color::Transparent);
    door.setOutlineColor(sf::Color::White);
    door.setOutlineThickness(1);
    door.setPosition(150, 530);

    sf::CircleShape knob;
    knob.setRadius(5);
    knob.setFillColor(sf::Color::Transparent);
    knob.setOutlineColor(sf::Color::White);
    knob.setOutlineThickness(1);
    knob.setPosition(255, 610);

    sf::RectangleShape tube1 {sf::Vector2f{5.0, 200}};
    tube1.setPosition(110, 10);
    tube1.setRotation(-90);
    
    tube1.setFillColor(sf::Color{0, 255, 0});

    sf::RectangleShape tomato_stalk {sf::Vector2f{5.0, p.getHeight()}};
    tomato_stalk.setPosition(210, 484);
    tomato_stalk.setRotation(180);
    tomato_stalk.setFillColor(sf::Color{0, 255, 0});

    sf::RectangleShape tomato_stalk2 {sf::Vector2f{3.0, 0}};
    tomato_stalk2.setPosition(210, 400);
    tomato_stalk2.setRotation(150);
    tomato_stalk2.setFillColor(sf::Color{0, 255, 0});

    sf::RectangleShape tomato_stalk3 {sf::Vector2f{3.0, 0}};
    tomato_stalk3.setPosition(210, 400);
    tomato_stalk3.setRotation(-150);
    tomato_stalk3.setFillColor(sf::Color{0, 255, 0});

    sf::RectangleShape tomato_stalk4 {sf::Vector2f{3.0, 0}};
    tomato_stalk4.setPosition(210, 300);
    tomato_stalk4.setRotation(150);
    tomato_stalk4.setFillColor(sf::Color{0, 255, 0});

    sf::RectangleShape tomato_stalk5 {sf::Vector2f{3.0, 0}};
    tomato_stalk5.setPosition(210, 300);
    tomato_stalk5.setRotation(-150);
    tomato_stalk5.setFillColor(sf::Color{0, 255, 0});

    sf::RectangleShape tomato_stalk6 {sf::Vector2f{3.0, 0}};
    tomato_stalk6.setPosition(210, 200);
    tomato_stalk6.setRotation(150);
    tomato_stalk6.setFillColor(sf::Color{0, 255, 0});

    sf::RectangleShape tomato_stalk7 {sf::Vector2f{3.0, 0}};
    tomato_stalk7.setPosition(210, 200);
    tomato_stalk7.setRotation(-150);
    tomato_stalk7.setFillColor(sf::Color{0, 255, 0});

    // create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Greenhouse simulator");
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

        if (ImGui::CollapsingHeader("Plant attributes"))
        {
        ImGui::Text("The current plant is: %i", p.getPlant());
        static int plant = 0;
        static float color[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
        ImGui::Combo("Combo", &plant, "Cactus plant\0Tomato plant\0Chili plant\0Paradise tree\0\0");    
        std::cout << plant << std::endl;
        if (ImGui::Button("Select plant"))
        {
            ImGui::OpenPopup("Select plant");
        }
                    
        if (ImGui::BeginPopupModal("Select plant", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Are you sure that you want to change the current plant?\nThis operation cannot be undone!\n\n");
            ImGui::Separator();

            static bool dont_ask_me_next_time = false;
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
            ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
            ImGui::PopStyleVar();

            if (ImGui::Button("OK", ImVec2(120, 0))) 
            { 
                ImGui::CloseCurrentPopup();
                p.reset();
                sim.resetDay(); 

                if (plant == 0)
                p.setType(Plant::cucumber_plant, 0.5, 15);
                }else if (plant == 1)
                {
                    
                } 

            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::EndPopup();
        }
        }


        if (ImGui::CollapsingHeader("Control"))
        {
        static bool e = true;
        static bool f = false;
        if (ImGui::RadioButton("Manual", e==false)) 
            { 
            e = false;
            f = true;
            c.changeState(e); 
            }

        ImGui::SameLine();

        if (ImGui::RadioButton("Automatic", e==true)) 
            {
            e = true; 
            f = false;
            c.changeState(e); 
            }

        if (ImGui::CollapsingHeader("Manual Control", &f))
        {
            ImGui::Text("Manual control is chosen, use the sliders below to control the system");
            ImGui::Text("\n");
            ImGui::Text("Fan control");
            ImGui::Separator();

            static int fan_;
            static int water_;
            static int light_;

            if (ImGui::SliderInt("Fan", &fan_, 0, 100)) {
                static double fan = fan_+0.;
                h.SetFanSpeed(fan);
            }

            ImGui::Text("Water control");
            ImGui::Separator();


            if (ImGui::SliderInt("Water", &water_, 0, 100)) {
                static double water = water_+0.;
                h.SetWateringSpeed(water);
            }

            ImGui::Text("Light control");
            ImGui::Separator();

            if (ImGui::SliderInt("Light", &light_, 0, 100)) {
                static double light = light_+0.;
                h.SetLightIntensity(light);
            }
            ImGui::Text("\n");
        }
        }

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

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
        ImGui::OpenPopup("Reset plant/time?");

        if (ImGui::BeginPopupModal("Reset plant/time?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Are you sure that you want to clear the current plant and reset time?\nThis operation cannot be undone!\n\n");
            ImGui::Separator();

            static bool dont_ask_me_next_time = false;
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
            ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
            ImGui::PopStyleVar();

            if (ImGui::Button("OK", ImVec2(120, 0))) 
            { 
                ImGui::CloseCurrentPopup();
                p.reset();
                sim.resetDay(); 
            }
            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::EndPopup();
        }
        
        // {
        //     p.reset();
        //     sim.resetDay();
        // }
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
            ImGui::OpenPopup("Reset plant/time?");

            if (ImGui::BeginPopupModal("Reset plant/time?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Are you sure that you want to clear the current plant and reset time?\nThis operation cannot be undone!\n\n");
                ImGui::Separator();

                static bool dont_ask_me_next_time = false;
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
                ImGui::PopStyleVar();

                if (ImGui::Button("OK", ImVec2(120, 0))) 
                { 
                    ImGui::CloseCurrentPopup();
                    p.reset();
                    sim.resetDay(); 
                }
                ImGui::SetItemDefaultFocus();
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
                ImGui::EndPopup();
            }

            ImGui::PopStyleColor(3);
            ImGui::PopID();

        ImGui::TreePop();
        }
        }


        // if (ImGui::CollapsingHeader("Hardstates",fan))
        // {
        //     if (ImGui::BeginTable("split", 4))
        //     {
        //         ImGui::TableNextColumn(); ImGui::Checkbox("Fan",        &fan);
        //         // ImGui::TableNextColumn(); ImGui::Checkbox("Heating",    &heating_c);
        //         // ImGui::TableNextColumn(); ImGui::Checkbox("Watering",   &water_c);
        //         // ImGui::TableNextColumn(); ImGui::Checkbox("Light",      &light_c);
        //         ImGui::EndTable();
        //     }
        // }
        ImGui::End();

        // clear the window with black color
        window.clear(sf::Color::Black);

        window.draw(tube);
        window.draw(glass);
        window.draw(door);
        window.draw(knob);


        if (p.getHeight() < 85)
        {
        tomato_stalk.setSize(sf::Vector2f{5.0, p.getHeight()});
        window.draw(tomato_stalk);

        }else if (p.getHeight() < 199)
        {
        tomato_stalk.setSize(sf::Vector2f{5.0, p.getHeight()});
        tomato_stalk2.setSize(sf::Vector2f{5.0, p.getHeight()-85});
        tomato_stalk3.setSize(sf::Vector2f{5.0, p.getHeight()-85});
        window.draw(tomato_stalk);
        window.draw(tomato_stalk2);
        window.draw(tomato_stalk3);
        }else if (p.getHeight() < 299)
        {
        tomato_stalk.setSize(sf::Vector2f{5.0, p.getHeight()});
        tomato_stalk4.setSize(sf::Vector2f{5.0, p.getHeight()-199});
        tomato_stalk5.setSize(sf::Vector2f{5.0, p.getHeight()-199});
        window.draw(tomato_stalk);
        window.draw(tomato_stalk2);
        window.draw(tomato_stalk3);
        window.draw(tomato_stalk4);
        window.draw(tomato_stalk5);
        }else if (p.getHeight() < 399)
        {
        tomato_stalk.setSize(sf::Vector2f{5.0, p.getHeight()});
        tomato_stalk6.setSize(sf::Vector2f{5.0, p.getHeight()-299});
        tomato_stalk7.setSize(sf::Vector2f{5.0, p.getHeight()-299});
        window.draw(tomato_stalk);
        window.draw(tomato_stalk2);
        window.draw(tomato_stalk3);
        window.draw(tomato_stalk4);
        window.draw(tomato_stalk5);
        window.draw(tomato_stalk6);
        window.draw(tomato_stalk7);
        }else{
        window.draw(tomato_stalk);
        window.draw(tomato_stalk2);
        window.draw(tomato_stalk3);
        window.draw(tomato_stalk4);
        window.draw(tomato_stalk5);
        window.draw(tomato_stalk6);
        window.draw(tomato_stalk7);
        }

        //450

        ImGui::SFML::Render(window);

        // end the current frame
        window.display();
    }
} 



