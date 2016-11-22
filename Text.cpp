/*
 * Text.cpp
 *
 *  Created on: 10 Nov 2016
 *      Author: rag
 */

#include <cstdlib>
#include <algorithm>
#include "Text.h"
#include "Util.h"

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

Text::Text(const char* data) : content(data) {

}

Text::Text(std::string &s) : content(s){

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
	if(content.size() < 1){
		return 0.0;
	}

    map<char, size_t> freq = countLetters();
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

unsigned long Text::size() const {
    return content.size();
}


std::map<char, size_t> Text::countLetters() const {
    std::map<char, size_t> freq = letterMap;
    for(auto i = content.begin(); i != content.end(); i++){
        //if the letter is not part of the alphabet then continue to the next one
        if(!isalpha(*i)){
            i++;
            continue;
        }

        //lowercase all letters
        char c = tolower(*i);

        ++freq[c];
    }
    return freq;
}

MonoSolutionSet Text::solveMono() const {
    LetterFrequencySet freqs = getLetterFrequencies();

    int c1 = freqs.rbegin()->letter - 'a';
    int c2 = (++freqs.rbegin())->letter - 'a';
    int cDiff = c1 - c2;

    MonoSolutionSet solutions;
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
                if(tcount > 0.2 * (p.size() / 3)){
                    solutions.insert(MonoSolution(aInv, -b, tcount));
                }
            }
        }
    }
    return solutions;
}

VigenereSolutionSet Text::solvePoly() const {

    set<size_t> positions = findTrigramRepetitions();
    set<size_t> keyLengthGuesses = possibleKeyLengths(positions);

    vector<string> maybeKeys;

    for(auto i = keyLengthGuesses.begin(); i != keyLengthGuesses.end(); i++){
        vector<Text> cols = this->groupTo(*i);
        string maybeKey("a");

        for(auto j = ++cols.begin(); j != cols.end(); j++){
            char maxMICShift = 0;
            double maxMIC = 0.0;

            for(char k = 0; k < 26; ++k){
                Text p = *j;
                p.shiftBy(k);
                double mic = cols[0].mic(p);
                if(mic > maxMIC){
                    maxMIC = mic;
                    maxMICShift = k;
                }
            }
            char k2 = (-maxMICShift % 26 + 26) % 26;
            maybeKey.push_back(k2 + 'a');
        }
        maybeKeys.push_back(maybeKey);
    }

    VigenereSolutionSet solutions;
    for(auto i = maybeKeys.begin(); i != maybeKeys.end(); ++i){
        for(char j = 0; j < 26; ++j){
            string maybeKey = *i;
            for(auto s = maybeKey.begin(); s != maybeKey.end(); ++s){
                *s = (((*s - 'a') + j) % 26) + 'a';
                Text p = *this;
                p.vigenereSubtract(maybeKey);
                size_t count = p.englishTrigramCount();
                solutions.insert(VigenereSolution(maybeKey, count));
//                cout << maybeKey << endl;
            }
        }
    }
    return solutions;
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
    set<size_t> positions;
    for(size_t i = 0; i < content.size() - 3; i++){
        string searchString = content.substr(i, 3);

        size_t pos = 0;
        size_t matches = 0;
        while(pos != string::npos){
            pos = content.find(searchString, pos);
            if(pos != string::npos){
                if(matches > 0){
                    positions.insert(pos);
                }
                ++pos;
                ++matches;
            }

        }
    }
    return positions;
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

MonoSolutionSet Text::solveShift() const {
    MonoSolutionSet solutions;
    for(size_t i = 0; i < 26; ++i){
        Text p = *this;
        p.shiftBy(i);
        size_t count = p.englishTrigramCount();
        if(count > 0.2 * (p.size() / 3)){
            solutions.insert(MonoSolution(0, i, count));
        }
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
