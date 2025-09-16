#include "../../include/core/input.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <cstring>

static bool keys[GLFW_KEY_LAST + 1] = {false};
static uint8_t prevKeys[GLFW_KEY_LAST + 1] = {0};

void fdse::input_update() {
    memcpy(prevKeys, keys, sizeof(keys));

    for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; i++) {
        keys[i] = (glfwGetKey(fdse::Engine::get_window(), i) == GLFW_PRESS);
    }
}
bool fdse::is_key_held(int key) {
    return key >= 0 && key <= GLFW_KEY_LAST && keys[key];
}
bool fdse::is_key_pressed(int key) {
    return key >= 0 && key <= GLFW_KEY_LAST && keys[key] && !prevKeys[key];
}
bool fdse::is_key_released(int key) {
    return key >= 0 && key <= GLFW_KEY_LAST && !keys[key] && prevKeys[key];
}