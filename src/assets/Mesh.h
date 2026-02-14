#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "Vertex.h"

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    uint32_t gpuVAOHandle = 0;
    uint32_t gpuVBOHandle = 0;
    uint32_t gpuEBOHandle = 0;
    std::string filePath;
};
