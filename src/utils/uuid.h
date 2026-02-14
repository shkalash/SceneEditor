#pragma once
#include <cstdint>
#include <random>
// simple UUID but just 64 bits, no need for 128 in this project
inline uint64_t generateUUID() {
    static std::mt19937_64 engine(std::random_device{}());
    static std::uniform_int_distribution<uint64_t> distribution;
    return distribution(engine);
}