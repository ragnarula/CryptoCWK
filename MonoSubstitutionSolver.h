//
// Created by Raghav Narula on 10/12/2016.
//

#ifndef CRYPTOCOURSEWORK_GENETICSOLVER_H
#define CRYPTOCOURSEWORK_GENETICSOLVER_H


#include "Text.h"

class MonoSubstitutionSolver {

    const Text cipherText;
public:
    MonoSubstitutionSolver(const Text& t) : cipherText(t){};
    std::string HillClimb();

    std::string frequencySubstitute();
};


#endif //CRYPTOCOURSEWORK_GENETICSOLVER_H
