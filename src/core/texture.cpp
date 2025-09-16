#include "../../include/core/texture.h"
#include <cstring>

fdse::Texture create_texture_from_surface(fdse::Surface* surface) {
    fdse::Texture texture;
    GLuint ID;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    texture.set_id(ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 surface->w,
                 surface->h,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 surface->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    texture.set_width(surface->w);
    texture.set_height(surface->h);

    return texture;
}

GLuint fdse::Texture::get_id(){ return id; }
int fdse::Texture::get_width(){ return width; }
int fdse::Texture::get_height(){ return height; }
const char *fdse::Texture::get_path(){ return path; }

void fdse::Texture::set_id(GLuint id){
    if(id != 0){
        this->id = id;
    }else{
        fdse::print_info(MessageType::Error, "Texture id can not be equal to 0: ", path);
    }
}
void fdse::Texture::set_width(int width){
    this->width = width;
}
void fdse::Texture::set_height(int height){
    this->height = height;
}
void fdse::Texture::set_path(const char *path){
    if(strcmp(path, "\n") == 0){
        fdse::print_info(MessageType::Error, "Texture file path cannot start with ' ' or be empty: ");
    }else{
        this->path = path;
    }
}