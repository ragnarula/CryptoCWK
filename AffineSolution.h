//
// Created by Rag on 21/11/2016.
//

#ifndef CRYPTOCOURSEWORK_MONOSOLUTION_H
#define CRYPTOCOURSEWORK_MONOSOLUTION_H


#include <cstddef>

class AffineSolution {
    int multiplier;
    int shift;
    size_t trigramCount;
    double chi;

public:
    AffineSolution() : multiplier(0), shift(0), trigramCount(0), chi(0.0){};
    AffineSolution(int multiplier, int shift, size_t trigramCount, double chi);
    int getMultiplier() const;
    int getShift() const;
    size_t getTrigramCount() const;
};


#endif //CRYPTOCOURSEWORK_MONOSOLUTION_H
