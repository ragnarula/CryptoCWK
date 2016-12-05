/*
 * Text.cpp
 *
 *  Created on: 10 Nov 2016
 *      Author: rag
 */

#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include "Text.h"
#include "Util.h"
#include <limits>


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

//frequent english letters in order
const vector<char> Text::frequentLetters = {'e','t','a','o','i','n','s','h','r','d','l','c','u','m','w','f','g','y','p','b','v','k','j','x','q','z'};

const map<char, size_t> letterMap = {
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

const map<char, double> englishLetterProbabilities = {
        {'e', 0.12702},
        {'t', 0.09056},
        {'a', 0.08167},
        {'o', 0.07507},
        {'i', 0.06996},
        {'n', 0.06749},
        {'s', 0.06327},
        {'h', 0.06094},
        {'r', 0.05987},
        {'d', 0.04253},
        {'l', 0.04025},
        {'c', 0.02782},
        {'u', 0.02758},
        {'m', 0.02406},
        {'w', 0.02360},
        {'f', 0.02228},
        {'g', 0.02015},
        {'y', 0.01974},
        {'p', 0.01929},
        {'b', 0.01492},
        {'v', 0.00978},
        {'k', 0.00772},
        {'j', 0.00153},
        {'x', 0.00150},
        {'q', 0.00095},
        {'z', 0.00074}
};
Text::Text(const char* data) : content(data) {
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

LetterFrequencySet Text::getLetterFrequencies() const {

    auto counts = countLetters();
    LetterFrequencySet s;
    for(auto i = counts.begin(); i != counts.end(); i++){
        if(i->second != 0){
            s.insert(LetterFrequency(i->first, i->second));
        }
    }

    return s;
}

double Text::ic() const {
	//if there is no content return 0.0 otherwise will get a division by 0
	if(content.size() < 2){
		return 0.0;
	}

    map<char, size_t> freq = countLetters();
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

unsigned long Text::size() const {
    return content.size();
}


std::map<char, size_t> Text::countLetters() const {
    std::map<char, size_t> freq = letterMap;
    int j = 0;
    for(auto i = content.begin(); i != content.end(); i++){
        //if the letter is not part of the alphabet then continue to the next one
        ++j;
        if(!isalpha(*i)){
//            i++;
            continue;
        }

        //lowercase all letters
        char c = tolower(*i);

        ++freq[c];
    }
    return freq;
}

MonoSolutionSetByTrigrams Text::solveMono() const {
    LetterFrequencySet freqs = getLetterFrequencies();

    int c1 = freqs.begin()->letter - 'a';
    int c2 = (++freqs.begin())->letter - 'a';
    int cDiff = c1 - c2;

    MonoSolutionSetByTrigrams solutions;
    for(auto i = frequentLetters.begin(); i != frequentLetters.end(); i++){
        for(auto j = frequentLetters.begin(); j != frequentLetters.end(); j++){

            if(i == j){
                continue;
            }

            //solve two linear congruences
            // Ax + b = c mod 26
            // A = (c1 - c2)(x1 - x1)^-1 mod 26
            // where c1 and c2 are the two most frequent letters in cipher text
            // and x1 and x2 are pairs of the most frequent letters in english

            int x1 = *i - 'a';
            int x2 = *j - 'a';
            int xDiff = x1 - x2;
            int xDiffInv = 0;
            int y = 0;

            int gcd = Util::gcdx(xDiff, 26, &xDiffInv, &y);

            int A = (cDiff * xDiffInv) % 26;

            int check = Util::gcd(A, 26);
            if(check == 1){

                int aInv = 0;
                int yy = 0;

                Util::gcdx(A, 26, &aInv, &yy);
                int b = ((c1 - (A * x1)) % 26 + 26) % 26;
                Text p = *this;
                p.shiftBy(-b);
                p.multiply(aInv);

                //if more than 20% of trigrams match english trigrams consider solved
                size_t tcount = p.englishTrigramCount();
                double chi = p.chiSq();
//                if(tcount > 0.2 * (p.size() / 3)){
                solutions.insert(MonoSolution(aInv, -b, tcount, chi));
//                }
            }
        }
    }
    return solutions;
}

struct LengthIC{
    size_t length = 0;
    double ic = 0;
    bool operator>(const LengthIC& rhs) const {
        double thisDev = fabs(ic - 0.0667);
        double thatDev = fabs(rhs.ic - 0.0667);
        return thisDev < thatDev;
    }
};

VigenereSolutionSet Text::solveVigenere() const {

    VigenereSolutionSet solutions;

    set<LengthIC, std::greater<LengthIC>> ICSet;
    for(size_t i = 1; i < 30; ++i){
        vector<Text> cols = this->groupTo(i);
        double sumIC = 0.0;
        //take average of ic
        for(auto c = cols.begin(); c != cols.end(); ++c){
            sumIC += c->ic();
        }
        double averageIC = sumIC / i;
        LengthIC l;
        if(averageIC > 0.06){
            l.ic = averageIC;
            l.length = i;
            ICSet.insert(l);
        }
    }

    for(auto i = ICSet.begin(); i != ICSet.end(); ++i){
        size_t keyLength = i->length;
        std::string key;
        key.insert(0, keyLength, 'a');

        vector<Text> cols = this->groupTo(keyLength);
        size_t k = 0;
        for(auto i = cols.begin(); i != cols.end(); ++i, ++k){
            char s = i->bestChiSqShift();
            key.at(k) = key.at(k) + s;
        }
        Text p = *this;
        p.vigenereAdd(key);
        solutions.insert(VigenereSolution(key, p.englishTrigramCount()));
    }


    return solutions;
}

void Text::solvePoly2() const{
    VigenereSolutionSet solutions;

    set<LengthIC, std::greater<LengthIC>> ICSet;
    for(size_t i = 2; i < 30; ++i){
        vector<Text> cols = this->groupTo(i);
        double sumIC = 0.0;
        //take average of ic
        for(auto c = cols.begin(); c != cols.end(); ++c){
            sumIC += c->ic();
        }
        double averageIC = sumIC / i;
        LengthIC l;
        l.ic = averageIC;
        l.length = i;
        ICSet.insert(l);
    }

    auto bestIC = ICSet.begin();
    size_t keyLength = bestIC->length;
    if(ICSet.size() > 1){
        size_t l1 = ICSet.begin()->length;
        size_t l2 = (++ICSet.begin())->length;
        size_t smaller = l1 < l2 ? l1 : l2;
        size_t larger = l1 > l2 ? l1 : l2;

        for(int i = smaller-1; i != 1; --i){
            if(smaller % i == 0 && larger % i == 0){
                keyLength = i;
                break;
            }
        }
    }
    std::string key;
    key.insert(0, keyLength, 'a');

    vector<Text> cols = this->groupTo(keyLength);
    size_t k = 0;
    for(auto i = cols.begin(); i != cols.end(); ++i, ++k){
        char s = i->bestChiSqShift();
        key.at(k) = key.at(k) + s;
    }
    Text p = *this;
    p.vigenereAdd(key);
    solutions.insert(VigenereSolution(key, p.englishTrigramCount()));

}

char Text::bestChiSqShift(){
    Text p = *this;
    double minChiSq = p.chiSq();
    int shift = 0;
    for(int i = 1; i < 26; ++i){
        p = *this;
        p.shiftBy(i);
        double c = p.chiSq();
        if(c < minChiSq){
            minChiSq = c;
            shift = i;
        }
    }
    return shift;
}

double Text::chiSq(){
    auto counts = countLetters();
    double sum = 0;
    for(auto c = counts.begin(); c != counts.end(); ++c){
        size_t count = c->second;
        char letter = c->first;
        double expected = englishLetterProbabilities.find(letter)->second;
        double denom = content.length() * expected;
        double num = pow((count - denom), 2);
        sum += (num / denom);
    }
    return sum;
}

set<size_t> Text::possibleKeyLengths(set<size_t> &positions) const {
    set<size_t> guesses;

    if(positions.size() < 2){
        return guesses;
    }

    auto first = positions.begin();
    for(auto i = ++positions.begin(); i != positions.end(); i++){
        guesses.insert(Util::gcd(*i, *first));
    }
    return guesses;
}

set<size_t> Text::findTrigramRepetitions() const {
    set<size_t> offsets;
    for(size_t i = 0; i < content.size() - 3; i++){
        string searchString = content.substr(i, 3);

        vector<size_t> positions;
        size_t pos = 0;
        size_t matches = 0;
        while(pos != string::npos){
            pos = content.find(searchString, pos);
            if(pos != string::npos){
//                if(matches > 0){
                positions.push_back(pos);
//                }
                ++pos;
                ++matches;
            }
        }
        if(positions.size() < 2) continue;
        for(auto j = positions.begin(); j != (positions.end() - 1); ++j){
            for(auto k = j + 1; k != positions.end(); ++k){
                offsets.insert(*k - *j);
            }
        }
    }
    return offsets;
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

MonoSolutionSetByTrigrams Text::solveShift() const {
    MonoSolutionSetByTrigrams solutions;
    for(size_t i = 0; i < 26; ++i){
        Text p = *this;
        p.shiftBy(i);
        size_t count = p.englishTrigramCount();
        double chi = p.chiSq();
        solutions.insert(MonoSolution(0, i, count, chi));
    }
    return solutions;
}

double Text::mic(const Text &other) const {
    auto letterCountsThis = this->countLetters();
    auto letterCountsOther = other.countLetters();

    double m = 0;
    for(int i = 0; i < 26; ++i){
        size_t a = letterCountsThis[('a' + i)];
        size_t b = letterCountsOther[('a' + i)];

        m += (a / (double)letterCountsThis.size()) * (b / (double)letterCountsOther.size());
    }

    return m;
}
