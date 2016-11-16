/*
 * Text.cpp
 *
 *  Created on: 10 Nov 2016
 *      Author: rag
 */

#include <cstdlib>
#include "Text.h"

using namespace std;

//top few english trigrams
const vector<string> Text::trigrams = {
        "the",
        "and",
        "tha",
        "ent",
        "ing",
        "ion",
        "tio",
        "for",
        "nde",
        "has",
        "nce",
        "edt",
        "tis",
        "oft",
        "sth",
        "men"
};

Text::Text(const char* data) : content(data) {

}

Text::Text(std::string &s) : content(s){

}

Text::~Text() {
}

multimap<size_t, char> Text::getLetterFrequencies() const {

    map<char, size_t > counts = countLetters();
    multimap<size_t, char> sortedCounts;

    for(auto i = counts.begin(); i != counts.end(); i ++){
        sortedCounts.insert(pair<size_t, char>(i->second, i->first));
    }

    return sortedCounts;
}

double Text::ic() const {
	//if there is no content return 0.0 otherwise will get a division by 0
	if(content.size() < 1){
		return 0.0;
	}

    map<char, size_t > freq = countLetters();
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
    shiftBy(1);
}

std::ostream &operator<<(std::ostream &os, const Text &t) {
    os << t.content;
    return os;
}

void Text::shiftBy(int n) {
    for(size_t i = 0; i < content.length(); i++){
        int tmp = content[i] - 'a';
        tmp = ((tmp + n) % 26 + 26) % 26;   //avoid negative remainders
        content[i] = tmp + 'a';             //safe - has been reduced modulo 26
    }
}

void Text::shiftBackwards() {
    shiftBy(-1);
}

size_t Text::englishTrigramCount() const {
    size_t sum = 0;

    for(size_t i = 0; i < trigrams.size(); i++){
        size_t pos = 0;
        while(pos != string::npos){
            pos = content.find(trigrams[i], pos);
            if(pos != string::npos){
                sum++;
                pos++;
            }
        }
    }

    return sum;
}

void Text::multiply(int n) {
    for(size_t i = 0; i < content.size(); i++){
        int tmp = content[i] - 'a';
        tmp = ((tmp * n) % 26 + 26) % 26;   //avoid negative remainders
        content[i] = tmp + 'a';             //safe - has been reduced modulo 26
    }
}

unsigned int Text::size() const {
    return content.size();
}

std::map<char, size_t> Text::countLetters() const {
    std::map<char, size_t > freq;
    for(auto i = content.begin(); i != content.end(); i++){
        //if the letter is not part of the alphabet then continue to the next one
        if(!isalpha(*i)){
            continue;
        }

        //lowercase all letters
        char c = tolower(*i);

        auto k = freq.find(c);
        //if exists in map, increment count, else add 1
        if(k != freq.end()){
            (k->second)++;
        } else {
            freq.insert(pair<char, int>(c, 1));
        }
    }
    return freq;
}
