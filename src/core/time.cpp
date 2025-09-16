#include "../../include/core/time.h"
#include <GLFW/glfw3.h>

void fdse::Time::update() {
    double current_time = glfwGetTime();
    if (last_time == 0) {
        delta_seconds = 0.0f;
    } else {
        delta_seconds = static_cast<float>(current_time - last_time);
    }
    last_time = current_time;
}
