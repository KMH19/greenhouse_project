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

    float stalk_length = 0.;

    bool fan_c = false;
    bool heating_c = false;
    bool water_c = false;
    bool light_c = false;

    void Simulation::Controls::SimulateOneDay(int days_, Plant& p, SensorInput& s, ClimateControl& c) 
    {

    using namespace std::chrono_literals;
    for (int i = 0; i < days_; i++)
    {
        std::cout << "Day no.: " << 1+i << std::endl;
        std::cout << "-----------------------" << std::endl << std::endl;

        p.grow(1);

        double x = temp_sim_c[i];

        // This tells the current air humidity (Polynomial factor)
        air_humidity_c = 0.1*pow(x,2)+10;

        // This tells the current soil humidity, based on atmospheric temperature and humidity
        soil_humidity_c = 0.005*pow(x,2);
      
        s.sensorRead(temp_sim_c[i], air_humidity_c, soil_humidity_c);   

        std::cout << "Plant height: " << p.getHeight() << std::endl << std::endl;

        std::cout << "Current temperature: " << temp_sim_c[i] << std::endl << std::endl;

        std::cout << "Current air humidity: " << air_humidity_c << std::endl << std::endl;

        std::cout << "Current soil humidity: " << soil_humidity_c << std::endl << std::endl;
        
        if (c.checkAutoState() == true)
        {
            c.Automatic(s);

        }else{

            c.Manual();
            
        }
        
        std::this_thread::sleep_for(2s);
    }
}

void Simulation::Interface::Init() 
{
    sf::RectangleShape tomato_stalk {sf::Vector2f{5.0, stalk_length}};
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
        if (ImGui::CollapsingHeader("Plant length"))
        {
            if (ImGui::SliderFloat("Height", &stalk_length, 0., 300.)) 
        {
            tomato_stalk.setSize(sf::Vector2f{5.0, stalk_length});
        }
        }
        ImGui::End();

        // clear the window with black color
        window.clear(sf::Color::Black);

        
        if (stalk_length < 85)
        {
        window.draw(tomato_stalk);
        }else if (stalk_length < 199)
        {
        window.draw(tomato_stalk);
        window.draw(tomato_stalk2);
        window.draw(tomato_stalk3);
        }else if (stalk_length < 301)
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



