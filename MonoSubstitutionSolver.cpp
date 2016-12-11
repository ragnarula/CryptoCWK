//
// Created by Raghav Narula on 10/12/2016.
//

#include <random>
#include <queue>
#include "MonoSubstitutionSolver.h"

using namespace std;

const vector<char> frequentLetters = {'e','t','a','o','i','n','s','h','r','d','l','c','u','m','w','f','g','y','p','b','v','k','j','x','q','z'};

string MonoSubstitutionSolver::HillClimb() {
    static const string symbols("abcdefghijklmnopqrstuvwxyz");

    std::uniform_int_distribution<> unif(0,25);
    std::default_random_engine re(time(0));

    string bestKey = symbols;
    double minScore = std::numeric_limits<double>::max();

    set<string> processedKeys;
    string initialKey = frequencySubstitute();

    queue<string> keyQueue;
    keyQueue.push(initialKey);
    for(int start = 0; start < 26; ++start){
        for(int end = start + 1; end < 26; ++end){
            string newKey = initialKey;
            swap(newKey[start], newKey[end]);
            keyQueue.push(newKey);
        }
    }

    int generation = 0;
    while(!keyQueue.empty()){
        string &key = keyQueue.front();

        Text p = cipherText;
        p.substitute(key);

        double newScore = p.gramFitness();

        if(newScore < minScore){
            cout << "New Best Score: " << newScore << " With Key: " << key << endl;
            bestKey = key;
            minScore = newScore;
            for(int j = 0; j < 1000; ++j){
                int a = unif(re);
                int b = unif(re);

                string newKey = key;
                swap(newKey[a], newKey[b]);

                if(processedKeys.find(newKey) == processedKeys.end()){
                    keyQueue.push(newKey);
                } else {
                    --j;
                    continue;
                }
            }
        }
        processedKeys.insert(key);

        cout << generation << '\r';
        keyQueue.pop();
        ++generation;
    }

    return bestKey;
}

string MonoSubstitutionSolver::frequencySubstitute(){
    auto counts = cipherText.getLetterFrequencies();
    string key("abcdefghijklmnopqrstuvwxyz");
    set<char> charset = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    map<char, char> keymap;

    vector<char> topLetters;
    for(auto i = counts.begin(); i != counts.end(); ++i){
        topLetters.push_back(i->letter);
    }

    int i = 0;
    for(auto c = topLetters.begin(); c != topLetters.end(); ++c, ++i){
        char x = frequentLetters[i];
        char y = *c;
        keymap[y] = x;
        charset.erase(x);
    }

    vector<char> charlist(charset.begin(), charset.end());
    mt19937 rng(static_cast<uint32_t>(time(0)));
    shuffle(charlist.begin(), charlist.end(), rng);
    for(auto k = key.begin(); k != key.end(); ++k){
        auto kk = keymap.find(*k);
        if(kk != keymap.end()){
            *k = kk->second;
        } else {
            *k = *charlist.begin();
            if(!charlist.empty()) charlist.erase(charlist.begin());
        }
    }
    return key;
}