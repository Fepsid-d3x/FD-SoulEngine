#ifndef TEXTURE_H
#define TEXTURE_H

#include "./engine.h"
#include "./surface.h"

namespace fdse{
    struct Texture {
    public:
        GLuint get_id();
        int get_width();
        int get_height();

        const char *get_path();

        void set_width(int width);
        void set_height(int height);
        void set_path(const char *path);
        void set_id(GLuint id);
    private:
        GLuint id = 0;
        int width = 0;
        int height = 0;

        const char *path;
    };
}

#endif