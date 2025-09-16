#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "./engine.h"
#include "../../lib/std_image/stb_image.h"
#include "./texture.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <cstdint>

namespace fdse {
    struct TextureManager {
    private:
        static std::unordered_map<std::string, fdse::Texture> textures;

    public:
        //static fdse::Texture load_texture(const std::string& filename, bool smoothing);
        static fdse::Texture load_texture(const char *filename, bool smoothing);
        static void clear();
    };

}

#endif