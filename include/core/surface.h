#ifndef SURFACE_H
#define SURFACE_H

#include "./rect.h"
#include <cstdint>

namespace fdse{
    struct Surface {
        Surface() = default;
        explicit Surface(const char* path);
        ~Surface();

        uint8_t flags = 0;
        int w = 0;
        int h = 0;
        int pitch = 0;
        int locked = 0;
        int refcount = 1;
        int channels = 0;
        unsigned char* pixels = nullptr;

        fdse::Rect clip_rect;

        bool load(const char* path);
        unsigned char* get_data() { return pixels; }
    };
}

#endif