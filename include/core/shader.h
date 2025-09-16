#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <string>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

namespace fdse{

    std::string load_shader_source(const char* path);

    struct Shader
    {
    public:
        unsigned int id; 
	
        Shader() { }
	
        Shader &use();
	
        void compile(const char *vertex_source, const char *fragment_source, const char *geometry_source = nullptr);
	
        void    set_float    (const char *name, float value, bool use_shader = false);
        void    set_int  (const char *name, int value, bool use_shader = false);
        void    set_vec2f (const char *name, float x, float y, bool use_shader = false);
        void    set_vec2f (const char *name, const glm::vec2 &value, bool use_shader = false);
        void    set_vec3f (const char *name, float x, float y, float z, bool use_shader = false);
        void    set_vec3f (const char *name, const glm::vec3 &value, bool use_shader = false);
        void    set_vec4f (const char *name, float x, float y, float z, float w, bool use_shader = false);
        void    set_vec4f (const char *name, const glm::vec4 &value, bool use_shader = false);
        void    set_mat4  (const char *name, const glm::mat4 &matrix, bool use_shader = false);
    private:
        void check_compile_errors(unsigned int object, std::string type); 
    };
}

#endif