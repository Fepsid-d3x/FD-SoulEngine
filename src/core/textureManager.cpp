#include "../../include/core/textureManager.h"

std::unordered_map<std::string, fdse::Texture> fdse::TextureManager::textures;

fdse::Texture fdse::TextureManager::load_texture(const char *filename, bool smoothing) {
    auto it = textures.find(filename);
    if (it != textures.end()) {
        return it->second;
    }

    fdse::Texture texture;
    texture.set_path(filename);
    int width, height;
    GLuint ID;

    int channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    if(!data){
        fdse::print_info(MessageType::Error, "Failed to load image: ", filename);
        return texture; 
    }
    texture.set_width(width);
    texture.set_height(height);

    GLenum format = GL_RGB;
    if(channels == 1){
        format = GL_RED;
    }else if(channels == 3){
        format = GL_RGB;
    }else if(channels == 4){
        format = GL_RGBA;
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    texture.set_id(ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    if(smoothing == true){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }else{
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, texture.get_width(), texture.get_height(), 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    if(!texture.get_id()){
        fdse::print_info(MessageType::Error, "Failed load texture: ", filename);
    }else{
        fdse::print_info(MessageType::Info, "Load texture: ", filename);
    }

    textures[filename] = texture;

    return texture;
}

void fdse::TextureManager::clear() {
    for (auto& pair : textures) {
        GLuint id = pair.second.get_id();
        glDeleteTextures(1, &id);
    }
    textures.clear();
}