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

TEST_CASE("ShiftForwards increments characters"){
    //given a text
    Text t("abcde");

    //when shifted should move letters by one
    t.shiftForwards();
    REQUIRE(t == Text("bcdef"));
    t.shiftForwards();
    REQUIRE(t == Text("cdefg"));
    t.shiftForwards();
    REQUIRE(t == Text("defgh"));
    t.shiftForwards();
    REQUIRE(t == Text("efghi"));
    t.shiftForwards();
    REQUIRE(t == Text("fghij"));
    t.shiftForwards();
    REQUIRE(t == Text("ghijk"));

    t = Text("abz");
    t.shiftForwards();
    REQUIRE(t == Text("bca"));
}

TEST_CASE("ShiftBackwards decrements characters"){
    //given a text
    Text t("ghijk");

    //when shifted should move letters by one
    t.shiftBackwards();
    REQUIRE(t == Text("fghij"));
    t.shiftBackwards();
    REQUIRE(t == Text("efghi"));
    t.shiftBackwards();
    REQUIRE(t == Text("defgh"));
    t.shiftBackwards();
    REQUIRE(t == Text("cdefg"));
    t.shiftBackwards();
    REQUIRE(t == Text("bcdef"));
    t.shiftBackwards();
    REQUIRE(t == Text("abcde"));

    t = Text("abz");
    t.shiftBackwards();
    REQUIRE(t == Text("zay"));
}

TEST_CASE("English trigrams are counted correctly"){
    //given a text with 5 common trigrams
    Text t("thehasionfornce");

    //should have a trigram count of 5
    REQUIRE(t.englishTrigramCount() == 5);
}

TEST_CASE("Multiply does modulo multiplication of content"){
    //given a text
    Text t("abcz");

    //when multiplied by 3
    t.multiply(3);

    //result should be
    Text r("adgx");
    REQUIRE(t == r);
}

TEST_CASE("Vigenere add subtract"){
//    std::string key("key");
//
//    Text t("thisandthat");
//    t.vigenereAdd(key);
//
//    REQUIRE(t == Text("dlgcelnxfkx"));
//
//    t = Text("dlgcelnxfkx");
//
//    t.vigenereSubtract("key");
//
//    REQUIRE(t == Text("thisandthat"));
}

TEST_CASE("Solve Poly"){
    std::string key("keyw");

    Text t("aaaathisthataaaawherethistherethataaaatoisthisthat");
    t.vigenereAdd(key);

    VigenereSolutionSet s = t.solvePoly();

    REQUIRE(s.begin()->getKey() == "keyw");
}