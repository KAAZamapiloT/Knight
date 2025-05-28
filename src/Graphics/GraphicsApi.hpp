#pragma once

namespace Knight {

    class GraphicsAPI {
    public:
        virtual void Init() = 0;
        virtual void SetViewport(int x, int y, int width, int height) = 0;
        virtual void Clear(float r, float g, float b, float a) = 0;
        virtual void DrawIndexed(unsigned int indexCount) = 0;

        virtual ~GraphicsAPI() = default;

        enum class API {
            None = 0, OpenGL = 1, Vulkan = 2
        };

       // static API GetAPI();
    };

} // namespace Knight
