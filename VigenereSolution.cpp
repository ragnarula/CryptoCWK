//
// Created by Rag on 21/11/2016.
//

#include "VigenereSolution.h"

VigenereSolution::VigenereSolution(const std::string &key, const size_t trigramCount)
        : key(key), trigramCount(trigramCount) {}

const std::string &VigenereSolution::getKey() const {
    return key;
}

size_t VigenereSolution::getTrigramCount() const {
    return trigramCount;
}

bool VigenereSolution::operator>(const VigenereSolution &other) const {
    return trigramCount > other.trigramCount;
}
