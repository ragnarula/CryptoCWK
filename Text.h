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
#include <set>

class Text {

	std::string content;
public:

	Text(const char *);
    Text(std::string&);
    virtual ~Text();

    std::vector<Text> groupTo(const size_t) const;
    std::vector<std::pair<char, size_t>> countLetters() const;

    size_t englishTrigramCount() const;
    size_t countOccurrencesOf(const std::string &sub) const;

    unsigned long size() const;

    double ic() const;
    double chiSqUnigram() const;
    double nGramFitness() const;
    double nGramDifference(const std::map<std::string, double> &probs) const;


	void substitute(const std::string &key);
	void shiftForwards();
	void shiftBackwards();
	void shiftBy(int);
	void multiply(int i);
	void vigenereAdd(const std::string&);
    void vigenereSubtract(const std::string&);


	bool operator==(const Text& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Text& t);
};

#endif /* TEXT_H_ */
