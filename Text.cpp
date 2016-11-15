/*
 * Text.cpp
 *
 *  Created on: 10 Nov 2016
 *      Author: rag
 */

#include <cstdlib>
#include "Text.h"

using namespace std;

Text::Text(const char* data) {
	buildLetterFrequencyDistribution(data);
}

Text::Text(std::string &s) {
    buildLetterFrequencyDistribution(s);
}

Text::~Text() {
}

void Text::buildLetterFrequencyDistribution(const string &s) {
	for(auto i = s.begin(); i != s.end(); i++){
		//if the letter is not part of the alphabet then continue to the next one
		if(!isalpha(*i)){
			continue;
		}

		//lowercase all letters
		char c = tolower(*i);

		auto k = freq.find(c);
		//if exists in map, incrememnt count, else add 1
		if(k != freq.end()){
			k->second++;
		} else {
			freq.insert(pair<char, int>(c, 1));
		}

        content.push_back(c);
	}
}

double Text::ic() const {
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

std::vector<Text> Text::groupTo(const int num) const {

    vector<Text> groups;

    for(size_t i = 0; i < num; i++){
        string s;
        for(size_t j = 0; j < content.size(); j++){
            if(j % num == i){
                s.push_back(content[j]);
            }
        }
        groups.push_back(Text(s));
    }

	return groups;
}

bool Text::operator==(const Text &other) const {
    if(&other == this){
        return true;
    }

    return content == other.content;
}

void Text::shiftForwards() {
    for(size_t i = 0; i < content.length(); i++){
        content[i] += 1;
        if(content[i] > 'z'){
            content[i] = 'a';
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Text &t) {
    os << t.content;
    return os;
}

void Text::shiftBy(int n) {
	if(n > 0){
		for(size_t i = 0; i < n; i++){
			shiftForwards();
		}
	} else {
		for(size_t i = 0; i < abs(n); i++){
			shiftBackwards();
		}
	}

}

void Text::shiftBackwards() {
	for(size_t i = 0; i < content.length(); i++){
		content[i] -= 1;
		if(content[i] < 'a'){
			content[i] = 'z';
		}
	}
}


