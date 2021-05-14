#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <math.h>

#include "interface.h"

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Color.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

#include "interface.h"
#include "plant.h"
#include "sensor_input.h"
#include "climate_control.h"
#include "hardstate_output.h"

    // The next (4) functions are setters for the private variables in the "Controls" class
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

    // Simulates one day, has a lot of parameters
    // All std::cout is used for logging to external console
    void Simulation::Controls::Simulate(int i, Plant& p, SensorInput& s, ClimateControl& c, HardstateOutput& h, Controls& sim)
    {
        std::cout << "Day no.: " << sim.getDay() << std::endl;
        std::cout << "-----------------------" << std::endl << std::endl;

        // Call grow function
        p.grow(1);

        // Store a simulation variable from the temperature vectord
        temperature_c = temp_sim_c[i];

        // This tells the current air humidity (Polynomial factor)
        air_humidity_c = 0.1*pow(temperature_c,2)+10;

        // This tells the current soil humidity, based on atmospheric temperature and humidity (Polynomial factor)
        soil_humidity_c = 0.005*pow(temperature_c,2);

        //Read values and store them in the sensor_input obj
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
                h.resetFan();

            }else{

                static double new_temp = c.getNewTemp();

                sim.setTemp_i(new_temp);

                std::cout << "Internal temperature was corrected by: " << internal_correction << std::endl << std::endl; 

                s.sensorRead(new_temp, air_humidity_c, soil_humidity_c);  
            }

        }else{

            c.Manual();
            return;
        }
    }   // Function "Simulate" end

    // This enables the posibillity to simulate day-by-day and several days at once.
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
        }
    }

void Simulation::Interface::Init(Plant& p, SensorInput& s, ClimateControl& c, HardstateOutput& h, Controls& sim) 
{
    // The cylinder glass for the tube
    sf::RectangleShape tube;
    tube.setSize(sf::Vector2f(190, 700));
    tube.setFillColor(sf::Color::Black);
    tube.setOutlineColor(sf::Color::Black);
    tube.setOutlineThickness(5);
    tube.setPosition(115, 15);
    //  The glass inside the tube 
    sf::RectangleShape glass;
    glass.setSize(sf::Vector2f(180, 480));
    glass.setFillColor(sf::Color::White);
    glass.setOutlineColor(sf::Color::Black);
    glass.setOutlineThickness(1);
    glass.setPosition(120, 20);
    // Compost door  
    sf::RectangleShape door;
    door.setSize(sf::Vector2f(120, 160));
    door.setFillColor(sf::Color::Transparent);
    door.setOutlineColor(sf::Color::White);
    door.setOutlineThickness(1);
    door.setPosition(150, 530);
    // Knob to the compost door
    sf::CircleShape knob;
    knob.setRadius(5);
    knob.setFillColor(sf::Color::Transparent);
    knob.setOutlineColor(sf::Color::White);
    knob.setOutlineThickness(1);
    knob.setPosition(255, 610);
    // Background for the floor
    sf::RectangleShape gulv;
    gulv.setSize(sf::Vector2f(1920,500));
    gulv.setFillColor(sf::Color{240, 185, 137});
    gulv.setOutlineColor(sf::Color{240, 185, 137});
    gulv.setOutlineThickness(1);
    gulv.setPosition(0, 720);
    // Floor lines 
    sf::RectangleShape streg;
    streg.setSize(sf::Vector2f(1920,2.5));
    streg.setFillColor(sf::Color{0, 0, 0});
    streg.setOutlineColor(sf::Color{240, 185, 137});
    streg.setOutlineThickness(1);
    streg.setPosition(0, 750);

    sf::RectangleShape streg1;
    streg1.setSize(sf::Vector2f(1920,2.5));
    streg1.setFillColor(sf::Color{0, 0, 0});
    streg1.setOutlineColor(sf::Color{240, 185, 137});
    streg1.setOutlineThickness(1);
    streg1.setPosition(0, 800);

    sf::RectangleShape streg2;
    streg2.setSize(sf::Vector2f(1920,2.5));
    streg2.setFillColor(sf::Color{0, 0, 0});
    streg2.setOutlineColor(sf::Color{240, 185, 137});
    streg2.setOutlineThickness(1);
    streg2.setPosition(0, 850);

    sf::RectangleShape streg3;
    streg3.setSize(sf::Vector2f(1920,2.5));
    streg3.setFillColor(sf::Color{0, 0, 0});
    streg3.setOutlineColor(sf::Color{240, 185, 137});
    streg3.setOutlineThickness(1);
    streg3.setPosition(0, 900);

    sf::RectangleShape streg4;
    streg4.setSize(sf::Vector2f(1920,2.5));
    streg4.setFillColor(sf::Color{0, 0, 0});
    streg4.setOutlineColor(sf::Color{240, 185, 137});
    streg4.setOutlineThickness(1);
    streg4.setPosition(0, 950);

    sf::RectangleShape streg5;
    streg5.setSize(sf::Vector2f(1920,2.5));
    streg5.setFillColor(sf::Color{0, 0, 0});
    streg5.setOutlineColor(sf::Color{240, 185, 137});
    streg5.setOutlineThickness(1);
    streg5.setPosition(0, 1000);

    sf::RectangleShape streg6;
    streg6.setSize(sf::Vector2f(1920,2.5));
    streg6.setFillColor(sf::Color{0, 0, 0});
    streg6.setOutlineColor(sf::Color{240, 185, 137});
    streg6.setOutlineThickness(1);
    streg6.setPosition(0, 1050);

    sf::RectangleShape windowframe;
    windowframe.setSize(sf::Vector2f(600,100));
    windowframe.setFillColor(sf::Color{77, 70, 207});
    windowframe.setOutlineColor(sf::Color::White);
    windowframe.setOutlineThickness(5);
    windowframe.setPosition(1200, 200);

    sf::CircleShape lampe;
    lampe.setRadius(75);
    lampe.setFillColor(sf::Color{255, 247, 33});
    lampe.setOutlineColor(sf::Color{255, 247, 33});
    lampe.setOutlineThickness(5);
    lampe.setPosition(800, 100);
  
    sf::RectangleShape skaerm;
    skaerm.setSize(sf::Vector2f(152,76));
    skaerm.setFillColor(sf::Color{0, 0, 0});
    skaerm.setOutlineColor(sf::Color{0, 0,0});
    skaerm.setOutlineThickness(5);
    skaerm.setPosition(800, 100);

    sf::RectangleShape haengsel;
    haengsel.setSize(sf::Vector2f(1.5,200));
    haengsel.setFillColor(sf::Color{0, 0, 0});
    haengsel.setOutlineColor(sf::Color{0, 0,0});
    haengsel.setOutlineThickness(5);
    haengsel.setPosition(876, -100);
    
    sf::RectangleShape tube1 {sf::Vector2f{5.0, 200}};
    tube1.setPosition(110, 10);
    tube1.setRotation(-90);
    tube1.setFillColor(sf::Color{0, 255, 0});

    sf::RectangleShape dør;
    dør.setSize(sf::Vector2f(300, 700));
    dør.setFillColor(sf::Color{82, 60, 34});
    dør.setOutlineColor(sf::Color::White);
    dør.setOutlineThickness(5);
    dør.setPosition(860, 15);

    sf::RectangleShape liste;
    liste.setSize(sf::Vector2f(1920,2.5));
    liste.setFillColor(sf::Color::White);
    liste.setOutlineColor(sf::Color::White);
    liste.setOutlineThickness(10);
    liste.setPosition(0, 710);

    sf::CircleShape haandtag;
    haandtag.setRadius(10);
    haandtag.setFillColor(sf::Color{213,178,64});
    haandtag.setOutlineColor(sf::Color{213,178,64});
    haandtag.setOutlineThickness(5);
    haandtag.setPosition(870, 325);

    sf::RectangleShape planke;
    planke.setSize(sf::Vector2f(1,699));
    planke.setFillColor(sf::Color{0, 0, 0});
    planke.setOutlineColor(sf::Color{0, 0,0});
    planke.setOutlineThickness(1);
    planke.setPosition(1010, 16);

    sf::RectangleShape planke1;
    planke1.setSize(sf::Vector2f(299,1));
    planke1.setFillColor(sf::Color{0, 0, 0});
    planke1.setOutlineColor(sf::Color{0, 0, 0});
    planke1.setOutlineThickness(1);
    planke1.setPosition(860, 200);

     sf::RectangleShape dørbund;
    dørbund.setSize(sf::Vector2f(292, 1));
    dørbund.setFillColor(sf::Color{82, 60, 34});
    dørbund.setOutlineColor(sf::Color{82, 60, 34});
    dørbund.setOutlineThickness(4);
    dørbund.setPosition(864, 715);

    sf::RectangleShape hus;
    hus.setSize(sf::Vector2f(35, 76));
    hus.setFillColor(sf::Color{175, 171, 179});
    hus.setOutlineColor(sf::Color{175, 171, 179});
    hus.setOutlineThickness(4);
    hus.setPosition(1500, 220); 

     sf::RectangleShape hus1;
    hus1.setSize(sf::Vector2f(35, 66));
    hus1.setFillColor(sf::Color{120, 118, 122});
    hus1.setOutlineColor(sf::Color{120, 118, 122});
    hus1.setOutlineThickness(4);
    hus1.setPosition(1465, 230);

    sf::RectangleShape hus2;
    hus2.setSize(sf::Vector2f(35, 26));
    hus2.setFillColor(sf::Color{74, 74, 79});
    hus2.setOutlineColor(sf::Color{74, 74, 79});
    hus2.setOutlineThickness(4);
    hus2.setPosition(1430, 270);

    sf::RectangleShape skygge;
    skygge.setSize(sf::Vector2f(180, 660));
    skygge.setFillColor(sf::Color{140, 110, 84});
    skygge.setOutlineColor(sf::Color{140, 110, 84});
    skygge.setOutlineThickness(5);
    skygge.setPosition(70, 35);

    sf::RectangleShape skygge1;
    skygge1.setSize(sf::Vector2f(180, 680));
    skygge1.setFillColor(sf::Color{181, 175, 167});
    skygge1.setOutlineColor(sf::Color{181, 175, 167});
    skygge1.setOutlineThickness(5);
    skygge1.setPosition(70, 35);

    sf::CircleShape sol;
    sol.setRadius(10);
    sol.setFillColor(sf::Color{245, 182, 98});
    sol.setOutlineColor(sf::Color{245, 182, 98});
    sol.setOutlineThickness(5);
    sol.setPosition(1740, 215);

   

    // (7) Plant objects below
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

    // Create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Greenhouse simulator");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    // Run the program as long as the window is open
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

        // Create a new window
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
        ImGui::Begin("Greenhouse Simulation");

        // Show popup, if this is the first time
        if (sim.first_popup == true){
        ImGui::OpenPopup("Hello");

        if (ImGui::BeginPopupModal("Hello", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Welcome to the greenhouse simulation of the tube\n\nPlease simulate one day before referring to the data display window!\n\nAlso, refer to the help section if needed.");
            ImGui::Separator();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
            ImGui::PopStyleVar();

            if (ImGui::Button("OK", ImVec2(120, 0))) 
            { 
                ImGui::CloseCurrentPopup();
                sim.first_popup = false;
            }
            ImGui::EndPopup();
        }
        }

        if (ImGui::CollapsingHeader("Help"))
        {
            ImGui::Text("USAGE:");
            ImGui::BulletText("Select a plant of choice in plant attributes tab, \n");
            ImGui::BulletText("Change between automatic and manual control in the control tab, \n");
            ImGui::BulletText("For simulation of one day or several day use the simulation tab, \n");
            ImGui::BulletText("The second window shows the data display window, please simulate one day before referring to this \n");
            ImGui::Separator();
        }

        if (ImGui::CollapsingHeader("Plant attributes"))
        {

        // Since we are looping, it is smart to define our local variables as static (hint: Because they remain in memory throughout program life)
        static int plant = 0;
        
        // Printing formatted data using the principles of printf
        ImGui::Text("The current plant is: %i", p.getPlant());

        static float color[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
        ImGui::Combo("Selection", &plant, " 0. Cactus plant\0 1. Tomato plant\0 2. Cucumber plant\0 3. Paradise tree\0\0");    
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
                p.reset();
                sim.resetDay(); 

                if (plant == 0)
                {
                p.setType(Plant::cactus_plant, 2, 15);
                }else if (plant == 1)
                {
                p.setType(Plant::tomato_plant, 4, 15);
                }else if (plant == 2)
                {
                p.setType(Plant::cucumber_plant, 4, 15);
                }else if (plant == 3)
                {
                p.setType(Plant::paradise_tree, 1, 15);
                } 

                ImGui::CloseCurrentPopup();
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
            ImGui::Text("Manual is not available at this time, but this is how is would look");
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
        ImGui::PopStyleColor(3);
        ImGui::PopID();

        ImGui::TreePop();
        }
        if (ImGui::TreeNode("Several days"))
        {
        if (ImGui::SliderInt("Days", &sim.sim_days, 1, 20)) {}

            if (ImGui::Button("Simulate"))
            {
                sim.SimulateDays(sim.sim_days, p, s, c, h, sim);
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
        ImGui::End();

        ImGui::Begin("Data Display");
            ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
            if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
            {
                if (ImGui::BeginTabItem("Plant attributes"))
                {
                    
                    ImGui::Text("This is where the plant variables are displayed\n");
                    ImGui::Separator();
                    ImGui::Text("\n");

                    if (ImGui::BeginTable("table1", 3))
                    {
                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Plant Type");
                            ImGui::TableNextColumn();
                            ImGui::Text("%s",p.plant_names[p.getPlant()]);
                            ImGui::TableNextColumn();
                            ImGui::Text("-");
                
                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Plant height");
                            ImGui::TableNextColumn();
                            ImGui::Text("%f",p.getHeight());
                            ImGui::TableNextColumn();
                            ImGui::Text("mm");

                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Growth Rate");
                            ImGui::TableNextColumn();
                            ImGui::Text("%f",p.getGrowthRate());
                            ImGui::TableNextColumn();
                            ImGui::Text("mm");

                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Target temperature");
                            ImGui::TableNextColumn();
                            ImGui::Text("%f",p.GetTargetTemperature());
                            ImGui::TableNextColumn();
                            ImGui::Text("celius");

                            ImGui::EndTable();

                    }
                    ImGui::EndTabItem();
                }
                
                if (ImGui::BeginTabItem("Sensor data"))
                {

                    ImGui::Text("This is where the sensor variables are displayed\n");
                    ImGui::Separator();
                    ImGui::Text("\n");

                    if (ImGui::BeginTable("table2", 3))
                    {
                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Target temperature");
                            ImGui::TableNextColumn();
                            ImGui::Text("%f",p.GetTargetTemperature());
                            ImGui::TableNextColumn();
                            ImGui::Text("celius");

                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Curr. temperature");
                            ImGui::TableNextColumn();
                            ImGui::Text("%f",s.getTemperature());
                            ImGui::TableNextColumn();
                            ImGui::Text("celius");

                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Curr. air humidity");
                            ImGui::TableNextColumn();
                            ImGui::Text("%f",s.getAirHumidity());
                            ImGui::TableNextColumn();
                            ImGui::Text("celius");

                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text(" ");
                            ImGui::TableNextColumn();
                            ImGui::Text(" ");
                            ImGui::TableNextColumn();
                            ImGui::Text(" ");

                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Fan speed");
                            ImGui::TableNextColumn();
                            ImGui::Text("%f",h.GetFanSpeed());
                            ImGui::TableNextColumn();
                            ImGui::Text("percent");

                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Fan efficiency");
                            ImGui::TableNextColumn();
                            ImGui::Text("%f",h.GetFanEfficiency());
                            ImGui::TableNextColumn();
                            ImGui::Text("factor");

                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Fan T change");
                            ImGui::TableNextColumn();
                            ImGui::Text("%f",c.getLastCorrection());
                            ImGui::TableNextColumn();
                            ImGui::Text("celius");

                            ImGui::EndTable();

                    }
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Simulation data"))
                {

                            ImGui::Text("This is where the simulation variables are displayed\n");
                            ImGui::Separator();
                            ImGui::Text("\n");

                            if (ImGui::BeginTable("table3", 3))
                            {
                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Sim temperature (out)");
                            ImGui::TableNextColumn();
                            ImGui::Text("%f",sim.getTemp_c());
                            ImGui::TableNextColumn();
                            ImGui::Text("celius");

                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Sim temperature (in)");
                            ImGui::TableNextColumn();
                            ImGui::Text("%f",sim.getTemp_i());
                            ImGui::TableNextColumn();
                            ImGui::Text("celius");

                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::Text("Sim humidity (out)");
                            ImGui::TableNextColumn();
                            ImGui::Text("%f",sim.getAirHum_c());
                            ImGui::TableNextColumn();
                            ImGui::Text("percent");

                            ImGui::EndTable();
                }
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar(); 
        }
        ImGui::End();

        // Setting background color
        window.clear(sf::Color{237, 213, 192});

        // Draw previously defined objects
        
        window.draw(liste);
        window.draw(skygge1);
        window.draw(skygge);
        window.draw(tube);
        window.draw(glass);
        window.draw(door);
        window.draw(knob);
        window.draw(gulv);
        window.draw(streg);
        window.draw(streg1);
        window.draw(streg2);
        window.draw(streg3);
        window.draw(streg4);
        window.draw(streg5);
        window.draw(streg6);
        window.draw(windowframe);
        window.draw(dør);
        window.draw(dørbund);
        window.draw(planke1);
        window.draw(planke);
        window.draw(haandtag);                
        window.draw(lampe);
        window.draw(skaerm);
        window.draw(haengsel);
        window.draw(hus2);  
        window.draw(hus1);
        window.draw(hus);
        window.draw(sol);
        
        
              
        

        // Plant growth logic ()
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

        ImGui::SFML::Render(window);

        // end the current frame
        window.display();
    }
} 



