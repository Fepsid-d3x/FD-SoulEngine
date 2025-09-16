#ifndef SPRITE2D_H
#define SPRITE2D_H

#include "../core/textureManager.h"
#include "../core/rect.h"
#include "../core/shader.h"
#include <glm/ext/vector_float2.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
#include <vector>

struct State {
    int start_frame_x;
    int row;
    int total_frames;
    float frame_width;
    float frame_height;
};

namespace fdse{
    using PixelMask = std::vector<std::vector<bool>>;

    struct Sprite2D{
        Sprite2D();
        ~Sprite2D();
    public:
        ////////////// Settings ////////////////
        void set_position(float x, float y);
        void set_size(float w, float h);
        void set_fps(int fps);
        void set_flipped(bool flip);
        void set_rotation(float angle);
        void set_speed(float speed);
        void set_state(const char *name);
        void set_origin(int x, int y);
        void set_shader(fdse::Shader &shader);
        void set_texture(fdse::Texture &texture);

        void move(int x, int y);
        void rotate(float angle){ rotation += angle; }

        void add_state(const char *name, int startX, int row, int totalFrames, float frame_width, float frame_height);
        ////////////////////////////////////////

        /////////////// Gettings ///////////////
        const PixelMask& get_pixel_mask() const { return pixel_mask; }
        fdse::Rect get_rect(){ return rect; }
        float get_speed(){ return speed; }
        float get_rotation(){ return rotation; }
        bool get_flipped(){ return flipped; }
        std::string get_state(){ return current_state; }
        glm::mat4 get_model_matrix();
        glm::vec2 get_position(){ return glm::vec2(rect.x, rect.y); }
        /////////////////////////////////////////

        void draw();

        void update();
    private:
        void setup_buffers();
        void generate_pixel_mask();
        bool is_animated() const;

        ////////////// State ////////////////
        std::unordered_map<std::string, State> states;
        std::string current_state;
        /////////////////////////////////////

        ////////////// Shader ///////////////
        Shader shader;
        bool use_shader      = false;
        /////////////////////////////////////

        ////////////// Frame ////////////////
        int start_frame_x    = 0;
        int row              = 0;
        int current_frame    = 0;
        int total_frames     = 0;
        float frame_width    = 0.f;
        float frame_height   = 0.f;
        std::vector<PixelMask> frame_masks;
        /////////////////////////////////////

        //////////// Settings ///////////////
        bool flipped         = false;
        float rotation       = 0.f;
        float speed          = 100.f;
        glm::vec2 origin{0, 0};

        fdse::Texture texture;
        fdse::Surface surface;
        fdse::Rect rect;
        /////////////////////////////////////

        ////////////// Time /////////////////
        uint32_t last_update = 0;
        int fps              = 6;
        /////////////////////////////////////

        /////////////// UV //////////////////
        float u0 = 0.f, 
              v0 = 0.f, 
              u1 = 0.f, 
              v1 = 0.f;
        /////////////////////////////////////

        ///////// VBA & VBO & EBO ///////////
        GLuint vao = 0, 
               vbo = 0, 
               ebo = 0;
        /////////////////////////////////////

        PixelMask pixel_mask;

        ////////// default Shader ///////////
        const char *default_shader_vertex = R"(
        #version 330 core
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in vec2 aTexCoord;
        out vec2 TexCoord;
        uniform mat4 model;
        uniform mat4 projection;
        uniform vec4 texOffset;
        void main() {gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
        TexCoord = mix(texOffset.xy, texOffset.zw, aTexCoord); })";
        const char *default_shader_fragment = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoord;
        uniform sampler2D sprite;
        void main()
        { FragColor = texture(sprite, TexCoord); })";
        ///////////////////////////////////////
    };
}

#endif