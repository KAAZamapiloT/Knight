#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>
#include <iostream>
#include <string>
#include "Graphics/Shader.hpp"
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Triangle {
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
public:
    GLuint VAO = 0, VBO = 0;
    Shader shader;

    // Vertex shader source code
    const char* vertexShaderSrc = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    // Fragment shader source code
    const char* fragmentShaderSrc = R"(
    #version 330 core
    out vec4 FragColor;
    uniform float u_time;

    void main() {
        float r = 0.5 + 0.5 * sin(u_time);
        float g = 0.5 + 0.5 * sin(u_time + 2.0);
        float b = 0.5 + 0.5 * sin(u_time + 4.0);
        FragColor = vec4(r, g, b, 1.0);
    }
)";


    void Init() {
        startTime = std::chrono::high_resolution_clock::now();
        // Compile shader program
        shader.Compile(vertexShaderSrc, fragmentShaderSrc);
       
        // Triangle vertices
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        // Generate VAO and VBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Vertex attribute pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Render() {
        shader.Use();
        auto now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float>(now - startTime).count();

        GLuint timeLocation = glGetUniformLocation(shader.ID, "u_time");
        glUniform1f(timeLocation, time);

      
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void Cleanup() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        shader.Delete();
    }
};

#endif // TRIANGLE_H
