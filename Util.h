//
// Created by Rag on 15/11/2016.
//

#ifndef CRYPTOCOURSEWORK_ARG_H
#define CRYPTOCOURSEWORK_ARG_H


#include "optionparser.h"

class Util {
public:
    static option::ArgStatus Required(const option::Option& option, bool msg);
    static int gcd(int, int);
    static int gcdx(int a, int b, int *x, int *y);
};


#endif //CRYPTOCOURSEWORK_ARG_H
