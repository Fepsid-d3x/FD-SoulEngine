#include "../../include/core/shader.h"

#include <iostream>
#include "../../include/core/engine.h"

std::string fdse::load_shader_source(const char* path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

fdse::Shader &fdse::Shader::use()
{
    glUseProgram(this->id);
    return *this;
}

void fdse::Shader::compile(const char* vertex_source, const char* fragment_source, const char* geometry_source)
{
    unsigned int sVertex = 0, sFragment = 0, gShader = 0;
	
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertex_source, NULL);
    glCompileShader(sVertex);
    check_compile_errors(sVertex, "VERTEX");
	
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragment_source, NULL);
    glCompileShader(sFragment);
    check_compile_errors(sFragment, "FRAGMENT");
	
    if (geometry_source != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometry_source, NULL);
        glCompileShader(gShader);
        check_compile_errors(gShader, "GEOMETRY");
    }
	
    this->id = glCreateProgram();
    glAttachShader(this->id, sVertex);
    glAttachShader(this->id, sFragment);
    if (geometry_source != nullptr)
        glAttachShader(this->id, gShader);
    glLinkProgram(this->id);
    check_compile_errors(this->id, "PROGRAM");
	
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometry_source != nullptr)
        glDeleteShader(gShader);
}

void fdse::Shader::set_float(const char *name, float value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform1f(glGetUniformLocation(this->id, name), value);
}
void fdse::Shader::set_int(const char *name, int value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->id, name), value);
}
void fdse::Shader::set_vec2f(const char *name, float x, float y, bool useShader)
{
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->id, name), x, y);
}
void fdse::Shader::set_vec2f(const char *name, const glm::vec2 &value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}
void fdse::Shader::set_vec3f(const char *name, float x, float y, float z, bool useShader)
{
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
}
void fdse::Shader::set_vec3f(const char *name, const glm::vec3 &value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}
void fdse::Shader::set_vec4f(const char *name, float x, float y, float z, float w, bool useShader)
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}
void fdse::Shader::set_vec4f(const char *name, const glm::vec4 &value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}
void fdse::Shader::set_mat4(const char *name, const glm::mat4 &matrix, bool useShader)
{
    if (useShader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(matrix));
}


void fdse::Shader::check_compile_errors(unsigned int object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            fdse::print_info(MessageType::Error, "[SHADER]: Compile-time error: Type: ", type.c_str());
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            fdse::print_info(MessageType::Info, "[SHADER]: Link-time error: Type: ", type.c_str());
        }
    }
}
