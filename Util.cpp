//
// Created by Rag on 15/11/2016.
//

#include <cstdlib>
#include <iostream>
#include "Util.h"

option::ArgStatus Util::Required(const option::Option& option, bool msg){
    if(option.arg != NULL){
        return option::ARG_OK;
    }

    if (msg) {
        std::cerr << "Option '" << option.name << "' requires an argument" << std::endl;
    }
    return option::ARG_ILLEGAL;
}

int Util::gcd(int a, int b) {
    while(b != 0){
        int tmp = b;
        b = (a%b+b)%b; //avoid negative remainder
        a = tmp;
    }
    return a;
}

int Util::gcdx(int a, int b, int *x, int *y){

    int x0 = 1; int x1 = 0;
    int y0 = 0; int y1 = 1;

    while(b != 0){

        int q = a / b;
        int r = (a % b + b) % b;

        a = b;
        b = r;

        int xi = x0;
        int yi = y0;

        x0 = x1;
        x1 = xi - q * x1;
        y0 = y1;
        y1 = yi - q * y1;

//        std::cout << "Q: " << q << " R: " << r << std::endl;

    }
    *x = x0;
    *y = y0;
    return a;
}