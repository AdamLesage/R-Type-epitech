#include "RightSidebar.hpp"

Edition::RightSidebar::RightSidebar(sf::RenderWindow &window)
    : _window(window), my_tool_active(true)
{
    // Initialiser ImGui pour SFML
    // ImGui::SFML::Init(_window);

    // Init color
    _color = new float[4];
    _color[0] = 0.45f;
    _color[1] = 0.55f;
    _color[2] = 0.60f;
    _color[3] = 1.00f;
}

Edition::RightSidebar::~RightSidebar()
{
    // Nettoyer ImGui pour SFML
    // ImGui::SFML::Shutdown();

    // Free allocated memory for _color
    delete[] _color;
}

void Edition::RightSidebar::draw()
{
    // sf::Event event;
    // while (_window.pollEvent(event))
    // {
    //     ImGui::SFML::ProcessEvent(event);
    //     if (event.type == sf::Event::Closed)
    //         _window.close();
    // }

    // ImGui::SFML::Update(_window, sf::seconds(1.0f / 60.0f));

    // ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
    // if (ImGui::BeginMenuBar())
    // {
    //     if (ImGui::BeginMenu("File"))
    //     {
    //         if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
    //         if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
    //         if (ImGui::MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
    //         ImGui::EndMenu();
    //     }
    //     ImGui::EndMenuBar();
    // }

    // ImGui::ColorEdit4("Color", _color);

    // float samples[100];
    // for (int n = 0; n < 100; n++)
    //     samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
    // ImGui::PlotLines("Samples", samples, 100);

    // ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
    // ImGui::BeginChild("Scrolling");
    // for (int n = 0; n < 50; n++)
    //     ImGui::Text("%04d: Some text", n);
    // ImGui::EndChild();
    // ImGui::End();

    // // Render ImGui on the window
    // ImGui::SFML::Render(_window);
}
