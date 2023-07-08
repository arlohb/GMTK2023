#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-copy"
#pragma clang diagnostic ignored "-Wunused-function"

#include <raylib-cpp.hpp>
namespace rl = raylib;

#pragma clang diagnostic pop

typedef rl::Vector2 V2;

// Allow V2 to be used in an unordered_map

template<>
struct std::hash<V2> {
    std::size_t operator()(const V2& v) const {
        const int& first = reinterpret_cast<const int&>(v.x) << 4;
        const int& second = reinterpret_cast<const int&>(v.y);

        return first | second;
    }
};

template<>
struct std::equal_to<V2> {
    bool operator() (V2 const& v1, V2 const& v2) const {
        return v1.x == v2.x && v1.y == v2.y;
    }
};

