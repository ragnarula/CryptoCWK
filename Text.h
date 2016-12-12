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
#include "AffineSolution.h"
#include "VigenereSolution.h"
#include "LetterCount.h"

typedef std::set<AffineSolution, std::greater<AffineSolution>> MonoSolutionSetByTrigrams;
typedef std::set<VigenereSolution, std::greater<VigenereSolution>> VigenereSolutionSet;

class Text {

	std::string content;
public:

	Text(const char *);

    Text(std::string&);
    virtual ~Text();
    std::vector<Text> groupTo(const int) const;
    unsigned long size() const;

    std::vector<std::pair<char, size_t>> countLetters() const;
    double ic() const;
    size_t englishTrigramCount() const;
    double chiSqUnigram() const;
    double nGramFitness() const;
    char bestChiSqShift() const;
    size_t countOccurancesOf(const std::string &sub) const;
    double nGramDifference(const std::map<std::string, double> &probs) const;

    VigenereSolutionSet solveVigenere() const;
	MonoSolutionSetByTrigrams solveShift() const;

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
