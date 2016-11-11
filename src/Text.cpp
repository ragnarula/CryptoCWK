/*
 * Text.cpp
 *
 *  Created on: 10 Nov 2016
 *      Author: rag
 */

#include "Text.h"
#include <cctype>

using namespace std;

Text::Text(const char* data) : content(data) {
	buildLetterFrequencyDistribution();
}

Text::Text(std::string& data) : content(data) {
	buildLetterFrequencyDistribution();
}

Text::~Text() {
	// TODO Auto-generated destructor stub
}

void Text::buildLetterFrequencyDistribution() {
	for(auto i = content.begin(); i != content.end(); i++){
		//if the letter is no part of the alpabet then continue to the next one
		if(!isalpha(*i)){
			continue;
		}

		//lowercase all letters, mutating content
		*i = tolower(*i);


		auto k = freq.find(*i);
		//if exists in map, incrememnt count, else add 1
		if(k != freq.end()){
			k->second++;
		} else {
			freq.insert(pair<char, int>(*i, 1));
		}

	}
}

double Text::ic() {
	//if there is no content return 0.0 otherwise will get a division by 0
	if(content.size() < 1){
		return 0.0;
	}

	//calculate numerator
	int sum = 0;
	for(auto i = freq.begin(); i != freq.end(); i++){
		if(i->second == 1){
			sum++;
		} else if(i->second > 1){
			sum += (i->second * (i->second - 1));
		}
	}

	//calculator denominator
	double divisor = 0.0;
	if(content.size() == 1){
		divisor = 1/26;
	} else if(content.size() > 1){
		divisor = (content.size() * (content.size() -1))/26;
	}

	//divide
	return sum/divisor;
}

std::vector<Text> Text::goupBy(int int1) {
	return vector<Text>();
}
