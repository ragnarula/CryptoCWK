//
// Created by Rag on 15/11/2016.
//

#ifndef CRYPTOCOURSEWORK_ARG_H
#define CRYPTOCOURSEWORK_ARG_H


#include "optionparser.h"

class Arg {
public:
    static option::ArgStatus Required(const option::Option& option, bool msg);
};


#endif //CRYPTOCOURSEWORK_ARG_H
