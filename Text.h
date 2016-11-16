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

	std::string content;
	std::map<char, int> freq;
	void buildLetterFrequencyDistribution(const std::string&);

public:

	Text(const char *);
	Text(std::string&);
	virtual ~Text();
    bool operator==(const Text& other) const;
    size_t size() const;

	double ic() const;
    size_t englishTrigramCount() const;
	std::vector<Text> groupTo(const int) const;

    void shiftForwards();
    void shiftBackwards();
	void shiftBy(int);
    void multiply(int i);

    friend std::ostream& operator<<(std::ostream& os, const Text& t);

};

#endif /* TEXT_H_ */
