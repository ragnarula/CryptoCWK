//
// Created by Raghav Narula on 16/11/2016.
//

#include <iostream>
#include "catch.hpp"
#include "Util.h"

TEST_CASE("Extended Euclidean Tests"){
    int x = 0;
    int y = 0;

    int gcd = Util::gcdx(11, 26, &x, &y);

    std::cout << "GCD: " << gcd << " X: " << x << " Y: " << y << std::endl;
}