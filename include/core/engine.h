#ifndef ENGINE_H
#define ENGINE_H

#include "../../lib/glad/include/glad/glad.h"
#include "shader.h"
#include "./print_info.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace fdse{
    struct Engine{
        ~Engine();
    public:
        void close_window(){ 
            if(window) glfwDestroyWindow(window);
            glfwTerminate(); 
        }

        void start(const char *title, int w, int h);

        static GLFWwindow* get_window(){ return window; }

        void set_screen_effect(GLuint id) {
            screen_shader.id = id;
            use_screen_shader = true;
        }
        void disable_screen_effect() {
            use_screen_shader = false;
        }

        static glm::mat4 projection;
    private:
        virtual void _start() = 0;
        virtual void _loop() = 0;
        virtual void _input() = 0;
        virtual void _draw() = 0;
        virtual void _stop() = 0;
        virtual void _event() = 0;

        void loop();
        void stop();

        static void glfw_error_callback(int error, const char *description);
        void render_screen_effect();

        static GLFWwindow* window;
        GLFWmonitor **monitors;

        int screen_w;
        int screen_h;
        unsigned int screen_fbo = 0;
        unsigned int screen_texture = 0;
        unsigned int screen_vao = 0, screen_vbo = 0;

        static bool use_screen_shader;
        fdse::Shader screen_shader;

        const char* screen_vertex = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec2 aTexCoord;
        out vec2 TexCoord;
        void main(){
        gl_Position = vec4(aPos.xy, 0.0, 1.0);
        TexCoord = aTexCoord; }
        )";
        const char* screen_fragment = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoord;
        uniform sampler2D window;
        void main(){ FragColor = texture(window, TexCoord); }
        )";
    };
}

#endif