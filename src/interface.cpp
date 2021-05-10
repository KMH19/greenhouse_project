#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

#include "interface.h"

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "interface.h"

    float stalk_length = 0.;
    float stalk_length2 = 0.;

    bool fan_c = false;
    bool heating_c = false;
    bool water_c = false;
    bool light_c = false;

void Simulation::Interface::Init() 
{

    sf::RectangleShape tomato_stalk {sf::Vector2f{5.0, stalk_length}};
    tomato_stalk.setPosition(512, 384);
    tomato_stalk.setRotation(180);
    tomato_stalk.setFillColor(sf::Color{0, 255, 0});

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

        ImGui::End();

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(tomato_stalk);

        ImGui::SFML::Render(window);

        // end the current frame
        window.display();
        }
    }
}