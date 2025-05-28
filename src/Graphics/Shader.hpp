#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>

class Shader {
public:
    GLuint ID = 0;
	Shader() = default;
    void Compile(const char* vertexSrc, const char* fragmentSrc) {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSrc, NULL);
        glCompileShader(vertexShader);
        CheckCompileErrors(vertexShader, "VERTEX");

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
        glCompileShader(fragmentShader);
        CheckCompileErrors(fragmentShader, "FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        CheckCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Use() {
        glUseProgram(ID);
    }

    void Delete() {
        glDeleteProgram(ID);
    }

private:
    void CheckCompileErrors(GLuint shader, std::string type) {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                    << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                    << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

#endif // SHADER_H
