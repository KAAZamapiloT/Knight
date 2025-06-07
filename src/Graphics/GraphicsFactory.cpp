#include"GraphicsFactory.hpp"




namespace Knight
{
    std::unique_ptr<GraphicsAPI> CreateGraphicsAPI() {
        KE_TAG_LOG_DEBUG("GraphicsFactory", "Creating GraphicsAPI instance");
        switch (GraphicsAPI::GetAPI()) {
        case GraphicsAPI::API::OpenGL:
            return std::make_unique<OpenGLGraphicsAPI>();
        case GraphicsAPI::API::Vulkan:
            // return std::make_unique<VulkanGraphicsAPI>();
            return nullptr;
        default:
            return nullptr;
        }
    }
}