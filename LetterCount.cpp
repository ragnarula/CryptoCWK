//
// Created by Rag on 21/11/2016.
//

#include "LetterCount.h"

LetterCount::LetterCount(char letter, size_t count) : letter(letter), count(count) {}

bool LetterCount::operator<(const LetterCount &other) const {
    return count > other.count;
}
