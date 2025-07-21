#include"GraphicsFactory.hpp"




namespace Knight
{
    std::unique_ptr<GraphicsAPI> CreateGraphicsAPI() {
        KE_TAG_LOG_DEBUG("GraphicsFactory", "Creating GraphicsAPI instance");
        switch (GraphicsAPI::GetAPI()) {
        case GraphicsAPI::API::OpenGL:
            KE_TAG_LOG_DEBUG("GRPHICS FACTORY", "HITTED OPENGL");
            return std::make_unique<OpenGLGraphicsAPI>();
        case GraphicsAPI::API::Vulkan:
            KE_TAG_LOG_CRITICAL("GRPHICS FACTORY", "HITTED VULKAN");
            // return std::make_unique<VulkanGraphicsAPI>();
            return nullptr;
        default:
            KE_TAG_LOG_CRITICAL("GRPHICS FACTORY", "HITTED DEFAULT");
            return nullptr;
        }
    }
}