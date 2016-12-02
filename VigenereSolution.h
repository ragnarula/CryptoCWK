//
// Created by Rag on 21/11/2016.
//

#ifndef CRYPTOCOURSEWORK_VIGENERESOLUTION_H
#define CRYPTOCOURSEWORK_VIGENERESOLUTION_H


#include <cstddef>
#include <string>

class VigenereSolution {
    std::string key;
    size_t trigramCount;
public:
    VigenereSolution() : key(""), trigramCount(0){};
    VigenereSolution(const std::string &key, const size_t trigramCount);
    bool operator>(const VigenereSolution& other) const;
    const std::string &getKey() const;
    size_t getTrigramCount() const;
};


#endif //CRYPTOCOURSEWORK_VIGENERESOLUTION_H
