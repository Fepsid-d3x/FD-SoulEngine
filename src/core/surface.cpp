#include "../../lib/std_image/stb_image.h"
#include "../../include/core/surface.h"

fdse::Surface::Surface(const char* path) {
    load(path);
}
fdse::Surface::~Surface() {
    if (pixels) {
        stbi_image_free(pixels);
        pixels = nullptr;
    }
}
bool fdse::Surface::load(const char* path) {
    if (pixels) {
        stbi_image_free(pixels);
        pixels = nullptr;
    }
    int width, height;
    pixels = stbi_load(path, &width, &height, &channels, 4);
    if (!pixels) {
        w = h = channels = 0;
        return false;
    }
    pitch = w * 4;
    w = width;
    h = height;
    clip_rect = fdse::Rect{0, 0, static_cast<float>(w), static_cast<float>(h)};
    return true;
}