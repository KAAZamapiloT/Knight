#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>
#include "Graphics/Shader.hpp"
#include <chrono>
class Shapes {
public:
	Shader* shader = new Shader();
    const char* linevertex = R"(	#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 uMVP; // Model-View-Projection matrix

void main()
{
    gl_Position = uMVP * vec4(aPos, 1.0);
})";

    const char* linefragment = R"(#version 330 core
out vec4 FragColor;

uniform vec3 uColor; // Line color

void main()
{
    FragColor = vec4(uColor, 1.0);
})";
	GLuint VAO = 0, VBO = 0;
	void InitLineShader() {
        if (!shader) {
            std::cerr << "Shader pointer is null.\n";
            return;
        }

        shader->Compile(linevertex, linefragment);

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
	}

	void render() {
		shader->Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);
	}
	void Cleanup() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		shader->Delete();
	}
};