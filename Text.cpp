/*
 * Text.cpp
 *
 *  Created on: 10 Nov 2016
 *      Author: rag
 */

#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <random>
#include "stats.h"
#include "Text.h"


using namespace std;

Text::Text(const char* data) {
    for(auto i = data; *i != '\0'; ++i){
        if(isalpha(*i)){
            content.push_back(tolower(*i));
        }
    }
}


Text::Text(std::string &s) {

    for(auto i = s.begin(); i != s.end(); ++i){
        if(isalpha(*i)){
            content.push_back(tolower(*i));
        }
    }
}


Text::~Text() {
}


double Text::ic() const {
	//if there is no content return 0.0 otherwise will get a division by 0
	if(content.size() < 2){
		return 0.0;
	}

    auto freq = countLetters();

	//calculate numerator
	int sum = 0;
	for(auto i = freq.begin(); i != freq.end(); i++){
		if(i->second > 1){
			sum += (i->second * (i->second - 1));
		}
	}

	//calculator denominator
	double divisor = (content.size() * (content.size() - 1));

	//divide
    double icValue = sum/divisor;
	return icValue;
}


std::vector<Text> Text::groupTo(const size_t num) const {

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
    size_t count = 0;
    for(auto t = trigramProbs.begin(); t !=  trigramProbs.end(); ++t){

        count += countOccurrencesOf(t->first);
    }
    return count;
}


size_t Text::countOccurrencesOf(const string &sub) const {
    size_t count = 0;
    for (size_t offset = content.find(sub); offset != string::npos; offset = content.find(sub, offset + sub.length()))
    {
        ++count;
    }
    return count;
}


void Text::multiply(int n) {
    for(size_t i = 0; i < content.size(); i++){
        int tmp = content[i] - 'a';
        tmp = ((tmp * n) % 26 + 26) % 26;   //avoid negative remainders
        content[i] = tmp + 'a';             //safe - has been reduced modulo 26
    }
}

unsigned long Text::size() const {
    return content.size();
}


vector<pair<char, size_t>> Text::countLetters() const {
    //default
    static const map<char, size_t> letterMap = {
            {'a',0},
            {'b',0},
            {'c',0},
            {'d',0},
            {'e',0},
            {'f',0},
            {'g',0},
            {'h',0},
            {'i',0},
            {'j',0},
            {'k',0},
            {'l',0},
            {'m',0},
            {'n',0},
            {'o',0},
            {'p',0},
            {'q',0},
            {'r',0},
            {'s',0},
            {'t',0},
            {'u',0},
            {'v',0},
            {'w',0},
            {'x',0},
            {'y',0},
            {'z',0}
    };

    std::map<char, size_t> freq = letterMap;
    int j = 0;
    for(auto i = content.begin(); i != content.end(); i++){
        //if the letter is not part of the alphabet then continue to the next one
        ++j;
        if(!isalpha(*i)){
            continue;
        }

        //lowercase all letters
        char c = tolower(*i);

        ++freq[c];
    }
    vector<pair<char, size_t>> counts(freq.size());
    copy(freq.begin(), freq.end(), counts.begin());
    return counts;
}




double Text::chiSqUnigram() const{
    auto counts = countLetters();
    double sum = 0;
    for(auto c = counts.begin(); c != counts.end(); ++c){
        size_t count = c->second;
        string letter;
        letter.push_back(c->first);
        double expected = unigramProbs.find(letter)->second;
        double denom = content.length() * expected;
        double num = pow((count - denom), 2);
        sum += (num / denom);
    }
    return sum;
}


double Text::nGramDifference(const map<string, double> &probs) const{
    double sumExpected = 0;
    double sumActual = 0;

    //count occurances of common ngrams
    for(auto b = probs.begin(); b != probs.end(); ++b){
        size_t count = countOccurrencesOf(b->first);
        sumActual += (double) count / (double) content.size();
        sumExpected += b->second * content.size();
    }

    return sumExpected - sumActual;
}


void Text::vigenereAdd(const std::string &key) {
    size_t index = 0;
    for(auto i = content.begin(); i != content.end(); ++i, ++index){
        char plain = *i  - 'a';
        int ki = index % key.size();
        char k =  key.at(ki) - 'a';
        char shifted = ((plain + k) % 26) + 'a';
        *i = shifted;
    }
}


void Text::vigenereSubtract(const std::string &key) {
    size_t index = 0;
    for(auto i = content.begin(); i != content.end(); ++i, ++index){
        char plain = *i  - 'a';
        int ki = index % key.size();
        char k =  key.at(ki) - 'a';
        char shifted = (((plain - k) % 26 + 26) % 26) + 'a';
        *i = shifted;
    }
}




void Text::substitute(const std::string &key) {
    map<char, char> keymap;
    char l = 'a';
    for(auto i = key.begin(); i != key.end(); ++i, ++l){
        keymap[l] = *i;
    }
    string newContent;
    for(auto c = content.begin(); c != content.end(); ++c){
        auto cc = keymap.find(*c);
        if(cc != keymap.end()){
            newContent.push_back(cc->second);
        } else {
            newContent.push_back(*c);
        }
    }
    content = newContent;
}


double Text::nGramFitness() const{
    double uniGramScore = nGramDifference(unigramProbs);
    double biGramScore = nGramDifference(bigramProbs);
    double triGramScore = nGramDifference(trigramProbs);
    double quadGramScore = nGramDifference(quadgramProbs);
    return uniGramScore + (biGramScore) + (triGramScore) + (quadGramScore);
}

bool Text::sample(Text &out, size_t num) const {
    if(num > content.size()) return false;
    std::uniform_int_distribution<unsigned long> unif(0, content.size() - num);
    std::default_random_engine re(time(0));
    size_t start = unif(re);
    string samp = content.substr(start, num);
    out = Text(samp);
    return true;
}

const std::string &Text::getString() const {
    return content;
}
