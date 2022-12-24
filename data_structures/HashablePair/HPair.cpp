#include "HPair.h"

HPair::IIPair::IIPair() {
    this->first = 0;
    this->second = 0;
}

HPair::IIPair::IIPair(int first, int second) {
    this->first = first;
    this->second = second;
}

bool HPair::IIPair::operator==(const HPair::IIPair& other) {
    return this->first == other.first && this->second == other.second;
}

