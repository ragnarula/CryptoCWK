//
// Created by Raghav Narula on 12/12/2016.
//

#include "PolySubstitutionSolver.h"
#include <cmath>

using namespace std;

struct {
    bool operator()(const pair<string, size_t> &a, const pair<string, size_t> &b){
        return a.second > b.second;
    }
} descendingByCount;


bool PolySubstitutionSolver::vigenere(string &bestKey) const {

    vector<pair<string, size_t>> solutions;

    set<pair<size_t, double>> icSet;
    for(size_t i = 1; i < 30; ++i){
        vector<Text> cols = cipherText.groupTo(i);
        double sumIC = 0.0;
        //take average of ic
        for(auto c = cols.begin(); c != cols.end(); ++c){
            sumIC += c->ic();
        }
        double averageIC = sumIC / i;
        if(averageIC > 0.06){
            icSet.insert(pair<size_t, double>(i, averageIC));
        }
    }

    for(auto i = icSet.begin(); i != icSet.end(); ++i){
        size_t keyLength = i->first;
        std::string key;
        key.insert(0, keyLength, 'a');

        vector<Text> cols = cipherText.groupTo(keyLength);
        size_t k = 0;
        for(auto j = cols.begin(); j != cols.end(); ++j, ++k){
            int s = bestChiSqShift(*j);
            key.at(k) = key.at(k) + (char)s;
        }
        Text p = cipherText;
        p.vigenereAdd(key);
        solutions.push_back(pair<string, size_t>(key, p.englishTrigramCount()));
    }


    if(solutions.empty()){
        return false;
    }
    sort(solutions.begin(), solutions.end(), descendingByCount);
    bestKey = solutions.begin()->first;
    return true;
}


int PolySubstitutionSolver::bestChiSqShift(const Text &t) const{
    Text p = t;
    double minChiSq = p.chiSqUnigram();
    int shift = 0;
    for(int i = 1; i < 26; ++i){
        p = t;
        p.shiftBy(i);
        double c = p.chiSqUnigram();
        if(c < minChiSq){
            minChiSq = c;
            shift = i;
        }
    }
    return shift;
}