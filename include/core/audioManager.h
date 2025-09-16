#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "../../lib/miniaudio/miniaudio.h"
#include "./print_info.h"
#include <iostream>

namespace fdse{
    struct AudioManager{
        AudioManager();
        ~AudioManager();
    public:
        void load(const char *path);
        void start();
        void stop();
        void pause();
        void unpause();
        void resume();

    protected:
        ma_result result;
        ma_sound audio;
        ma_engine audio_engine;
        ma_uint64 paused_frame = 0;
        bool is_paused = false;

        bool initialized = false;
    };
}

#endif