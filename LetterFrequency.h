//
// Created by Rag on 21/11/2016.
//

#ifndef CRYPTOCOURSEWORK_LETTERFREQUENCY_H
#define CRYPTOCOURSEWORK_LETTERFREQUENCY_H


#include <cstddef>

class LetterFrequency {
public:
    char letter;
    size_t count;

    bool operator>(const LetterFrequency& other) const;

    LetterFrequency(char letter, size_t count);
};


#endif //CRYPTOCOURSEWORK_LETTERFREQUENCY_H
