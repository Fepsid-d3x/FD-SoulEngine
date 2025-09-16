#include "../../include/core/engine.h"
#include "../../include/core/input.h"
#include <GLFW/glfw3.h>

GLFWwindow* fdse::Engine::window = nullptr;
glm::mat4 fdse::Engine::projection = glm::ortho(0.f, 0.f, 0.f, 0.f);
fdse::Shader screen_shader;
bool fdse::Engine::use_screen_shader = 0;

void fdse::Engine::glfw_error_callback(int error, const char *description){
    print_info(MessageType::Warning, "[GLFW]: ", error, " ", description);
}

void fdse::Engine::render_screen_effect(){
    screen_shader.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, screen_texture);
    glUniform1i(glGetUniformLocation(screen_shader.id, "window"), 0);
    glUniform1f(glGetUniformLocation(screen_shader.id, "time"), glfwGetTime());
    glUniform2f(glGetUniformLocation(screen_shader.id, "resolution"), float(screen_w), float(screen_h));

    glBindVertexArray(screen_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void fdse::Engine::start(const char *title, int w, int h){
    screen_w = w;
    screen_h = h;

    print_info(MessageType::Info, "|Start FD-SoulEngine|");

    ////////////////////////// Init /////////////////////////////////////
    glfwSetErrorCallback(glfw_error_callback);

    if(!glfwInit()){
        print_info(MessageType::Error, "[GLFW]: Failed to initialize");
    }else{
        print_info(MessageType::Info, "[GLFW]: Initialized");
    }
    /////////////////////////////////////////////////////////////////////

    //////////////////////// OpenGL Attribute ///////////////////////////
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /////////////////////////////////////////////////////////////////////

    ////////////////// Create Window ////////////////////////////////////
    window = glfwCreateWindow(screen_w, screen_h, title, NULL, NULL);
	if (!window )
	{
        print_info(MessageType::Error, "[GLFW]: Failed to create window");
		glfwTerminate();
	}
    glfwSetWindowSizeLimits(window, screen_w, screen_h, screen_w, screen_h);
    glfwMakeContextCurrent(window);
    /////////////////////////////////////////////////////////////////////

    /////////////////// Load GLAD ///////////////////////////////////////
    if (!gladLoadGL()) {
        print_info(MessageType::Error, "[GLAD]: Failed to initialize GLAD");
    }else {
        print_info(MessageType::Info, "[GLAD]: Initialized");
    }
    /////////////////////////////////////////////////////////////////////

    //////////////////// OpenGL Information /////////////////////////////
    print_info(MessageType::Info, "[OpenGL]: Info:");
    print_info(MessageType::Info, "    > Renderer: ", glGetString(GL_RENDERER));
    print_info(MessageType::Info, "    > Vendor: ", glGetString(GL_VENDOR));
    print_info(MessageType::Info, "    > Version: ", glGetString(GL_VERSION));
    print_info(MessageType::Info, "    > GLSL: ", glGetString(GL_SHADING_LANGUAGE_VERSION));
    /////////////////////////////////////////////////////////////////////

    //////////////////// Monitor Information /////////////////////////////
    int count;
    monitors = glfwGetMonitors(&count);
    for(int i = 0; i < count; i++){
        const char *name = glfwGetMonitorName(monitors[i]);
        print_info(MessageType::Info, "[GLFW]: Info:");
        print_info(MessageType::Info, "    > Monitor: ", i);
        print_info(MessageType::Info, "    > Name: ", name);

        const GLFWvidmode *video_mode = glfwGetVideoMode(monitors[i]);
        print_info(MessageType::Info, "    > Resolution: ", video_mode->width, "x", video_mode->height);
        print_info(MessageType::Info, "    > RefreshRate: ", video_mode->refreshRate, "Hz");
        print_info(MessageType::Info, "    > Color Bits: ", "R: ", video_mode->redBits, " G: ", video_mode->greenBits, " B: ", video_mode->blueBits);
    }
    ///////////////////////////////////////////////////////////////////////

    projection = glm::ortho(0.0f, float(screen_w), float(screen_h), 0.0f);

    glEnable(GL_BLEND);
    glEnable(GL_SCISSOR_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glScissor(0, 0, screen_w, screen_h);
    glViewport(0, 0, screen_w, screen_h);
    

    ///////////////// Create screen framebuffer /////////////////////////
    glGenFramebuffers(1, &screen_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, screen_fbo);

    glGenTextures(1, &screen_texture);
    glBindTexture(GL_TEXTURE_2D, screen_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screen_w, screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screen_texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        print_info(MessageType::Error, "Framebuffer is not complete!");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    float quad_vertices[] = {
    // pos   // tex
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &screen_vao);
    glGenBuffers(1, &screen_vbo);
    glBindVertexArray(screen_vao);
    glBindBuffer(GL_ARRAY_BUFFER, screen_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    /////////////////////////////////////////////////////////////////////

    ////////////////////// Compile Screen Shader ////////////////////////
    screen_shader.compile(screen_vertex, screen_fragment);
    /////////////////////////////////////////////////////////////////////

    _start();

    loop();
    stop();
}
void fdse::Engine::loop(){
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        input_update();
        _input();
        _loop();

        /////////////////////// Render in FBO ///////////////////////////
        glBindFramebuffer(GL_FRAMEBUFFER, screen_fbo);
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        /////////////////////////////////////////////////////////////////

        _draw();

        ///////////////////// Render in Screen //////////////////////////
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        if (use_screen_shader)
            render_screen_effect();
        else {
            glUseProgram(screen_shader.id);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, screen_texture);
            glUniform1i(glGetUniformLocation(screen_shader.id, "window"), 0);
            glUniform1f(glGetUniformLocation(screen_shader.id, "time"), glfwGetTime());
            glUniform2f(glGetUniformLocation(screen_shader.id, "resolution"), float(screen_w), float(screen_h));

            glBindVertexArray(screen_vao);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        //////////////////////////////////////////////////////////////////

        glfwSwapBuffers(window);
    }
}
void fdse::Engine::stop(){
    
}

fdse::Engine::~Engine(){
    if(window) glfwDestroyWindow(window);
    glfwTerminate();
}