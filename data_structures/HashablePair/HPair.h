#pragma once
#include <utility>
#include <string>

namespace HPair {
    // Hashable pairs

    struct IIPair : std::pair<int, int> {
        IIPair();
        IIPair(int first, int second);
        bool operator==(const IIPair& other);
    };
};

namespace std {
    template <>
    struct hash<HPair::IIPair> {
        size_t operator()(const HPair::IIPair& iipair) const {
            return hash<string>()(to_string(iipair.first) + ',' + to_string(iipair.second));
        }
    };
};
