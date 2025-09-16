#include "../../include/core/camera2d.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

glm::mat4 fdse::Camera2D::get_view_matrix(){
    return glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
}
glm::mat4 fdse::Camera2D::get_projection_matrix(){
    float halfW = size.x / 2.0f / zoom;
    float halfH = size.y / 2.0f / zoom;

    return glm::ortho(-halfW, halfW, -halfH, halfH);
}
void fdse::Camera2D::move(const glm::vec2& delta){
    position += delta;
}
void fdse::Camera2D::set_zoom(float z){
    zoom = z;
}
void fdse::Camera2D::follow(const glm::vec2& target_pos, float lerp_factor) {
    position += (target_pos - position) * lerp_factor;
}