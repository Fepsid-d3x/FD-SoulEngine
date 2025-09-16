#ifndef CAMERA_H
#define CAMERA_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>

namespace fdse{
    struct Camera2D{
        Camera2D() = default;
    public:
        glm::mat4 get_view_matrix();
        glm::mat4 get_projection_matrix();

        void move(const glm::vec2& delta);

        void set_zoom(float z);
        void set_position(glm::vec2 pos) { position = pos; }
        void set_size(float w, float h) { size = {w, h}; }

        void follow(const glm::vec2& target_pos, float lerp_factor);
    private:
        glm::vec2 position{0.0f, 0.0f};
        glm::vec2 size{800.0f, 600.0f};
        float zoom = 1.0f;
    };
}

#endif