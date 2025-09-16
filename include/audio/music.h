#ifndef MUSIC_H
#define MUSIC_H

#include "../core/audioManager.h"
#include <iostream>

namespace fdse{
    struct Music : AudioManager{
    public:
        void load(const char *path);
    };
}

#endif