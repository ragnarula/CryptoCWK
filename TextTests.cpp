//
// Created by Rag on 14/11/2016.
//

#include "catch.hpp"
#include "Text.h"

TEST_CASE("IC of empty text should be 0"){
    //given an empty text
    Text t("");

    REQUIRE(t.ic() == 0.0);
}

