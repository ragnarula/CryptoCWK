//
// Created by Rag on 15/11/2016.
//

#include <cstdlib>
#include <iostream>
#include "Helper.h"

option::ArgStatus Helper::Required(const option::Option& option, bool msg){
    if(option.arg != NULL){
        return option::ARG_OK;
    }

    if (msg) {
        std::cerr << "Option '" << option.name << "' requires an argument" << std::endl;
    }
    return option::ARG_ILLEGAL;
}

int Helper::gcd(int a, int b) {
    while(b != 0){
        int tmp = b;
        b = (a%b+b)%b; //avoid negative remainder
        a = tmp;
    }
    return a;
}

int Helper::gcdx(int a, int b, int *x, int *y){

    // Base Case
//    if (a == 0)
//    {
//        *x = 0;
//        *y = 1;
//        return b;
//    }

    while(b != 0){
        int tmp = b;
        b = (a%b+b) % b;
        a = tmp;
        *x = 
        *y = tmp / b;
    }
    return a;
}