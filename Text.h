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
#include "MonoSolution.h"
#include "VigenereSolution.h"
#include "LetterFrequency.h"

typedef std::set<MonoSolution, std::greater<MonoSolution>> MonoSolutionSetByTrigrams;
typedef std::set<MonoSolution, std::less<MonoSolution>> MonoSolutionSetByChi;
typedef std::set<VigenereSolution, std::greater<VigenereSolution>> VigenereSolutionSet;
typedef std::set<LetterFrequency, std::greater<LetterFrequency>> LetterFrequencySet;

class Text {



    std::map<char, size_t > countLetters() const;
	std::string content;

public:
    static const std::vector<std::string> trigrams;
    static const std::vector<char> frequentLetters;

	Text(const char *);
	Text(std::string&);
	virtual ~Text();
    bool operator==(const Text& other) const;
    unsigned long size() const;

	double ic() const;
    double mic(const Text&) const;
    size_t englishTrigramCount() const;
	std::vector<Text> groupTo(const int) const;
    LetterFrequencySet getLetterFrequencies() const;

	MonoSolutionSetByTrigrams solveMono() const;
    VigenereSolutionSet solveVigenere() const;
    MonoSolutionSetByTrigrams solveShift() const;

    void shiftForwards();
    void shiftBackwards();
	void shiftBy(int);
    void multiply(int i);
    void vigenereAdd(const std::string&);
    void vigenereSubtract(const std::string&);



    friend std::ostream& operator<<(std::ostream& os, const Text& t);

	double chiSqUnigram() const;

	char bestChiSqShift() const;

	void solvePoly2() const;

    void substitute(const std::string &key);

    double gramFitness() const;

    size_t countOccurancesOf(const std::string &sub) const;

    double chiSqNGram(const std::map<std::string, double> &probs) const;

    double nGramDistance(const std::map<std::string, double> &probs) const;
};

#endif /* TEXT_H_ */
