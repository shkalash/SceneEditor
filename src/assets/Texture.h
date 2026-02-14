#pragma once
#include <string>
#include <cstdint>

struct Texture {
    uint32_t textureId;
    uint32_t width;
    uint32_t height;
    std::string filePath;
};
