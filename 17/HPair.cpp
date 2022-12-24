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

HPair::LLPair::LLPair() {
    this->first = 0;
    this->second = 0;
}

HPair::LLPair::LLPair(long long first, long long second) {
    this->first = first;
    this->second = second;
}

bool HPair::LLPair::operator==(const HPair::LLPair& other) {
    return this->first == other.first && this->second == other.second;
}
