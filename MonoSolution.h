//
// Created by Rag on 21/11/2016.
//

#ifndef CRYPTOCOURSEWORK_MONOSOLUTION_H
#define CRYPTOCOURSEWORK_MONOSOLUTION_H


#include <cstddef>

class MonoSolution {
    int multiplier;
    int shift;
    size_t trigramCount;

public:
    MonoSolution() : multiplier(0), shift(0), trigramCount(0){};
    MonoSolution(int multiplier, int shift, size_t trigramCount);
    bool operator>(const MonoSolution& other) const;
    int getMultiplier() const;
    int getShift() const;
    size_t getTrigramCount() const;
};


#endif //CRYPTOCOURSEWORK_MONOSOLUTION_H
