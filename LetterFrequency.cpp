//
// Created by Rag on 21/11/2016.
//

#include "LetterFrequency.h"

LetterFrequency::LetterFrequency(char letter, size_t count) : letter(letter), count(count) {}

bool LetterFrequency::operator>(const LetterFrequency &other) const {
    return count > other.count;
}
