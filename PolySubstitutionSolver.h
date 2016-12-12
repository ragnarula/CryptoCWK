//
// Created by Raghav Narula on 12/12/2016.
//

#ifndef CRYPTOCOURSEWORK_POLYSUBSTITUTIONSOLVER_H
#define CRYPTOCOURSEWORK_POLYSUBSTITUTIONSOLVER_H


#include "Text.h"

class PolySubstitutionSolver {
    const Text cipherText;
    int bestChiSqShift(const Text &t) const;

public:
    PolySubstitutionSolver(const Text &t) : cipherText(t) {};
    bool vigenere(std::string &key) const;
};


#endif //CRYPTOCOURSEWORK_POLYSUBSTITUTIONSOLVER_H
