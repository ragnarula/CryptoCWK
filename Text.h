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

class Text {
	std::string content;
	std::map<char, int> freq;
	void buildLetterFrequencyDistribution();

public:

	Text(const char *);
	Text(std::string&);
	virtual ~Text();
	double ic() const;
	std::vector<Text> groupTo(const int) const;

    void shift();
	void shiftBy(size_t);
	bool operator==(const Text& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Text& t);
};

#endif /* TEXT_H_ */
