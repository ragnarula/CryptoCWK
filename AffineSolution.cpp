//
// Created by Rag on 21/11/2016.
//

#include "AffineSolution.h"

AffineSolution::AffineSolution(int multiplier, int shift, size_t trigramCount, double chi)
        : multiplier(multiplier), shift(shift), trigramCount(trigramCount), chi(chi) {}

int AffineSolution::getMultiplier() const {
    return multiplier;
}

int AffineSolution::getShift() const {
    return shift;
}

size_t AffineSolution::getTrigramCount() const {
    return trigramCount;
}
