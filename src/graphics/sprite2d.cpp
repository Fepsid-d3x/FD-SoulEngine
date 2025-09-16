#include "../../include/graphics/sprite2d.h"
#include <cstdint>
#include <glm/common.hpp>
#include <glm/trigonometric.hpp>

bool fdse::Sprite2D::is_animated() const {
    return total_frames > 1;
}

////////////////////////// Settings ///////////////////////////
void fdse::Sprite2D::set_position(float x, float y){
    rect.x = x;
    rect.y = y;
}
void fdse::Sprite2D::set_size(float w, float h){
    rect.w = w;
    rect.h = h;
}
void fdse::Sprite2D::set_fps(int fps) {
    this->fps = fps;
}
void fdse::Sprite2D::set_flipped(bool flip){
    flipped = flip;
}
void fdse::Sprite2D::set_rotation(float angle){
    rotation = angle;
}
void fdse::Sprite2D::set_speed(float speed){
    this->speed = speed;
}
void fdse::Sprite2D::set_state(const char *name){    
    if (current_state == name) return;

    auto it = states.find(name);
    if(it != states.end()) {
        current_state = name;
        current_frame = 0;
        last_update = static_cast<uint32_t>(glfwGetTime() * 1000);

        const State& s = it->second;
        start_frame_x = s.start_frame_x;
        row = s.row;
        total_frames = s.total_frames;
        frame_width = s.frame_width;
        frame_height = s.frame_height;
    }
}
void fdse::Sprite2D::add_state(const char *name, int startX, int row, int totalFrames, float frame_width, float frame_height){
    states[name] = State{ startX, row, totalFrames, frame_width, frame_height};
}
void fdse::Sprite2D::set_origin(int x, int y){
    origin = glm::vec2(static_cast<float>(x), static_cast<float>(y));
}
void fdse::Sprite2D::set_shader(fdse::Shader &shader){
    this->shader = shader;
    use_shader = true;
}
void fdse::Sprite2D::set_texture(fdse::Texture &texture){
    this->texture = texture;

    surface.load(texture.get_path());

    generate_pixel_mask();

    current_frame = 0;
    last_update = static_cast<uint32_t>(glfwGetTime() * 1000);

    if(use_shader == false){
        shader.compile(default_shader_vertex, default_shader_fragment);
    }

    setup_buffers();
}
void fdse::Sprite2D::move(int x, int y){
    rect.x += x;
    rect.y += y;
}
///////////////////////////////////////////////////////////////

////////////////////// Settings ///////////////////////////////
glm::mat4 fdse::Sprite2D::get_model_matrix() {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(rect.x, rect.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-origin.x, -origin.y, 0.0f));
    model = glm::scale(model, glm::vec3(rect.w, rect.h, 1.0f));

    return model;
}
///////////////////////////////////////////////////////////////

void fdse::Sprite2D::setup_buffers() {
    float vertices[] = {
         0.f, 0.f,    0.f, 0.f,
         1.f, 0.f,    1.f, 0.f,
         1.f, 1.f,    1.f, 1.f,
         0.f, 1.f,    0.f, 1.f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    if (vao == 0) glGenVertexArrays(1, &vao);
    if (vbo == 0) glGenBuffers(1, &vbo);
    if (ebo == 0) glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void fdse::Sprite2D::update() {
    /////// UV ///////
    if (!is_animated()) {
        u0 = v0 = 0.f;
        u1 = v1 = 1.f;
        return;
    }
    /////// UV ///////
    
    uint32_t now = static_cast<uint32_t>(glfwGetTime() * 1000);
    uint32_t frame_time = 1000u / fps;

    if (now - last_update >= frame_time) {
        current_frame = (current_frame + 1) % total_frames;
        last_update = now;

        ////////// UV ////////////////////
        float tex_width = static_cast<float>(texture.get_width());
        float tex_height = static_cast<float>(texture.get_height());

        float x = (start_frame_x + current_frame) * frame_width;
        float y = row * frame_height;

        u0 = x / tex_width;
        v0 = y / tex_height;
        u1 = (x + frame_width) / tex_width;
        v1 = (y + frame_height) / tex_height;
        //////////////////////////////////
    }
}

/////////////////////// Draw ///////////////////////////
void fdse::Sprite2D::draw() {
    if (texture.get_id() == 0) return;

    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(rect.x + origin.x, rect.y + origin.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-origin.x, -origin.y, 0.0f));
    model = glm::scale(model, glm::vec3(rect.w, rect.h, 1.0f));
    
    shader.set_mat4("model", model);
    shader.set_mat4("projection", fdse::Engine::projection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.get_id());
    shader.set_int("sprite", 0);

    shader.set_vec4f("texOffset", glm::vec4(u0, v0, u1, v1));

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
/////////////////////////////////////////////////////////

/////////////////// Generate PixelMask //////////////////
void fdse::Sprite2D::generate_pixel_mask() {
    if (!surface.pixels || surface.channels < 4) return;

    if (surface.channels < 4) {
        fdse::print_info(MessageType::Warning, "Image has no alpha channel. PixelMask will be empty");
        return;
    }

    pixel_mask = PixelMask(surface.h, std::vector<bool>(surface.w, false));

    for (int y = 0; y < surface.h; ++y) {
        for (int x = 0; x < surface.w; ++x) {
            int index = (y * surface.w + x) * surface.channels;
            unsigned char a = surface.pixels[index + 3];
            
            if (a > 0) {
                pixel_mask[y][x] = true;
            }
        }
    }

    int count = 0;
    for (size_t y = 0; y < pixel_mask.size(); ++y) {
        for (size_t x = 0; x < pixel_mask[0].size(); ++x) {
            if (pixel_mask[y][x]) count++;
        }
    }
    (void)count;
}
/////////////////////////////////////////////////////////

fdse::Sprite2D::Sprite2D(){

}
fdse::Sprite2D::~Sprite2D(){
}