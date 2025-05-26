#include <Core/Application.hpp>
#include <iostream>

namespace KnightEngine {

Application::Application()
{
    std::cout << "Knight Engine initialized!" << std::endl;
}

Application::~Application()
{
    std::cout << "Knight Engine shutting down..." << std::endl;
}

void Application::Run()
{
    while (m_Running)
    {
        // Main game loop
    }
}

} // namespace KnightEngine

int main(int argc, char** argv)
{
    auto app = KnightEngine::CreateApplication();
    app->Run();
    delete app;
    
    return 0;
}
