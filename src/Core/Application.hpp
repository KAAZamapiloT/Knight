#pragma once

namespace KnightEngine {

class Application
{
public:
    Application();
    virtual ~Application();

    void Run();

private:
    bool m_Running = true;
};

// To be defined in client
Application* CreateApplication();

} // namespace KnightEngine
