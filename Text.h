/*
 * Text.h
 *
 *  Created on: 10 Nov 2016
 *      Author: rag
 */

#ifndef TEXT_H_
#define TEXT_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <string>

class Text {

    static const std::vector<std::string> trigrams;

    std::map<char, size_t > countLetters() const;
	std::string content;

public:

	Text(const char *);
	Text(std::string&);
	virtual ~Text();
	double ic() const;
	std::vector<Text> groupTo(const int) const;

    void shiftForwards();
    void shiftBackwards();

    std::multimap<size_t, char> getLetterFrequencies() const;
    size_t englishTrigramCount();

	bool operator==(const Text& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Text& t);

    void multiply(int i);
};

#endif /* TEXT_H_ */
