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
        if (ImGui::CollapsingHeader("Plant length"))
        {
            if (ImGui::SliderFloat("Length", &stalk_length, 0., 300.)) 
        {
            tomato_stalk.setSize(sf::Vector2f{5.0, stalk_length});
        }
        }


        ImGui::End();

        // clear the window with black color
        window.clear(sf::Color::Black);


        if (stalk_length < 85){
        window.draw(tomato_stalk);
        }else if (stalk_length < 199){
        window.draw(tomato_stalk);
        window.draw(tomato_stalk2);
        window.draw(tomato_stalk3);
        }else if (stalk_length < 301){
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