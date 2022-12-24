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

    struct LLPair : std::pair<long long, long long> {
        LLPair();
        LLPair(long long first, long long second);
        bool operator==(const LLPair& other);
    };

};

namespace std {
    template <>
    struct hash<HPair::IIPair> {
        size_t operator()(const HPair::IIPair& iipair) const {
            return hash<string>()(to_string(iipair.first) + ',' + to_string(iipair.second));
        }
    };

    template <>
    struct hash<HPair::LLPair> {
        size_t operator()(const HPair::LLPair& llpair) const {
            return hash<string>()(to_string(llpair.first) + ',' + to_string(llpair.second));
        }
    };
};
