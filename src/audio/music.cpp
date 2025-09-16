#include "../../include/audio/music.h"

void fdse::Music::load(const char *path){
    result = ma_sound_init_from_file(&audio_engine, path, MA_SOUND_FLAG_STREAM, NULL, NULL, &audio);
    if(result != MA_SUCCESS){
        fdse::print_info(MessageType::Error, "Failed load sound: ", path);
    }else{
        fdse::print_info(MessageType::Info, "Load sound: ", path);
    }
}