//
// Created by Rag on 21/11/2016.
//

#include "MonoSolution.h"

MonoSolution::MonoSolution(int multiplier, int shift, size_t trigramCount, double chi)
        : multiplier(multiplier), shift(shift), trigramCount(trigramCount), chi(chi) {}

bool MonoSolution::operator>(const MonoSolution &other) const {
    return trigramCount > other.trigramCount;
}

int MonoSolution::getMultiplier() const {
    return multiplier;
}

int MonoSolution::getShift() const {
    return shift;
}

size_t MonoSolution::getTrigramCount() const {
    return trigramCount;
}

bool MonoSolution::operator<(const MonoSolution &other) const {
    return chi < other.chi;
}
