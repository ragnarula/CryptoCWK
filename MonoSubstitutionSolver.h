//
// Created by Raghav Narula on 10/12/2016.
//

#ifndef CRYPTOCOURSEWORK_GENETICSOLVER_H
#define CRYPTOCOURSEWORK_GENETICSOLVER_H


#include "Text.h"

class MonoSubstitutionSolver {

    const Text cipherText;
    std::string frequencySubstitute() const;
public:

    MonoSubstitutionSolver(const Text& t) : cipherText(t){};

    bool hillClimb(std::string &key) const;
    bool affine(int &multiplier, int &shift) const;
    bool shift(int &bestSolution) const;
};


#endif //CRYPTOCOURSEWORK_GENETICSOLVER_H
