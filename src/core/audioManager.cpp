#include "../../include/core/audioManager.h"

fdse::AudioManager::AudioManager(){
    ////////////////// Audio Init /////////////////////////
    if (ma_engine_init(NULL, &audio_engine) != MA_SUCCESS) {
        fdse::print_info(MessageType::Error, "Failed to initialize audio engine");
    }else{
        fdse::print_info(MessageType::Info, "Init audio engine");
    }
    ///////////////////////////////////////////////////////
}
void fdse::AudioManager::load(const char *path){
    result = ma_sound_init_from_file(&audio_engine, path, 0, NULL, NULL, &audio);
    initialized = true;
    if(result != MA_SUCCESS){
        fdse::print_info(MessageType::Error, "Failed load sound: ", path);
    }else{
        fdse::print_info(MessageType::Info, "Load sound: ", path);
    }
}
void fdse::AudioManager::start(){
    ma_sound_start(&audio);
}
void fdse::AudioManager::stop(){
    ma_sound_stop(&audio);
}
void fdse::AudioManager::pause(){
    ma_sound_get_cursor_in_pcm_frames(&audio, &paused_frame);
    ma_sound_stop(&audio);
    is_paused = true;
}
void fdse::AudioManager::unpause(){
    if(is_paused){
        ma_sound_start(&audio);
        ma_sound_seek_to_pcm_frame(&audio, paused_frame);
        is_paused = false;
    }
}

fdse::AudioManager::~AudioManager(){
    if (initialized) {
        ma_sound_uninit(&audio);
        ma_engine_uninit(&audio_engine);
    }
}