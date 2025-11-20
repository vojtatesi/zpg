#pragma once
#include <string>
#include <GL/glew.h>

class Texture {
public:
    Texture() = default;
    ~Texture();

    bool loadFromFile(const std::string& path);
    void bind(GLuint unit = 0) const;

private:
    GLuint textureID = 0;
    int width = 0, height = 0, channels = 0;
    std::string path;
};
