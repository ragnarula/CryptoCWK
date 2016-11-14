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

class Text {
	std::string content;
	std::map<char, int> freq;
	void buildLetterFrequencyDistribution();
public:
	Text(const char *);
	Text(std::string&);
	virtual ~Text();
	double ic();
	std::vector<Text> goupBy(int);
};

#endif /* TEXT_H_ */
