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

TEST_CASE("Text with same content should return true for operator =="){
    //given two texts the same
    Text t1("AAA");
    Text t2("AAA");

    //and one text different
    Text t3("BBB");

    //when t1 is compared to t2
    bool res1 = t1 == t2;

    //the result should be true
    REQUIRE(res1);

    //when t1 is compared to t3
    bool res2 = t1 == t3;

    //the result should be false
    REQUIRE(!res2);
}

TEST_CASE("group by should return the correct number of texts in vector with the correct content"){
    //given a text
    Text t("abcdeabcde");

    //when grouped into 5
    std::vector<Text> groups = t.groupTo(5);

    //the result should be 5 groups
    REQUIRE(groups.size() == 5);

    //each result should have the correct content
    Text r0("aa");
    REQUIRE(groups[0] == r0);
    Text r1("bb");
    REQUIRE(groups[1] == r1);
    Text r2("cc");
    REQUIRE(groups[2] == r2);
    Text r3("dd");
    REQUIRE(groups[3] == r3);
    Text r4("ee");
    REQUIRE(groups[4] == r4);
}

TEST_CASE("Shift increments characters"){
    //given a text
    Text t("abcde");

    //when shifted should move letters by one
    t.shift();
    REQUIRE(t == Text("bcdef"));
    t.shift();
    REQUIRE(t == Text("cdefg"));
    t.shift();
    REQUIRE(t == Text("defgh"));
    t.shift();
    REQUIRE(t == Text("efghi"));
    t.shift();
    REQUIRE(t == Text("fghij"));
    t.shift();
    REQUIRE(t == Text("ghijk"));

    t = Text("abz");
    t.shift();
    REQUIRE(t == Text("bca"));
}