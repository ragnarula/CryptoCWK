//
// Created by Rag on 15/11/2016.
//

#include <cstdlib>
#include <iostream>
#include "Arg.h"

option::ArgStatus Arg::Required(const option::Option& option, bool msg){
    if(option.arg != NULL){
        return option::ARG_OK;
    }

    if (msg) {
        std::cerr << "Option '" << option.name << "' requires an argument" << std::endl;
    }
    return option::ARG_ILLEGAL;
}