//
// Created by Raghav Narula on 10/12/2016.
//

#include <random>
#include <queue>
#include "MonoSubstitutionSolver.h"
#include "stats.h"
#include "Util.h"

using namespace std;

struct {
    bool operator()(const pair<char, size_t> &a, const pair<char, size_t> &b){
        return a.second > b.second;
    }
} descendingByCount;


struct {
    bool operator()(const tuple<int, int, size_t>& a, const tuple<int, int, size_t> &b){
        return get<2>(a) > get<2>(b);
    }
} descendingByTrigramCount;


bool MonoSubstitutionSolver::hillClimb(string &bestSolution) const {
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

        double newScore = p.nGramFitness();

        if(newScore < minScore){
            cout << "New Best Score: " << newScore << " With Key: " << key << endl;
            bestKey = key;
            minScore = newScore;
            for(int j = 0; j < 10000; ++j){
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

    bestSolution = bestKey;
    return true;
}


string MonoSubstitutionSolver::frequencySubstitute() const {
    auto counts = cipherText.countLetters();
    sort(counts.begin(), counts.end(), descendingByCount);

    string key("abcdefghijklmnopqrstuvwxyz");
    set<char> charset = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    map<char, char> keymap;


    int i = 0;
    for(auto c = counts.begin(); c != counts.end(); ++c, ++i){
        char x = frequentLetters[i];
        char y = c->first;
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


bool MonoSubstitutionSolver::affine(int &multiplier, int &shift) const {
    auto counts = cipherText.countLetters();
    sort(counts.begin(), counts.end(), descendingByCount);

    int c1 = counts.begin()->first - 'a';
    int c2 = (++counts.begin())->first - 'a';
    int cDiff = c1 - c2;

    vector<tuple<int, int, size_t>> solutions;
    for(auto i = frequentLetters.begin(); i != frequentLetters.end(); i++){
        for(auto j = frequentLetters.begin(); j != frequentLetters.end(); j++){

            if(i == j){
                continue;
            }

            //Solve two linear congruences
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
                Text p = cipherText;
                p.shiftBy(-b);
                p.multiply(aInv);

                //if more than 20% of trigrams match english trigrams consider solved
                size_t tcount = p.englishTrigramCount();
                solutions.push_back(make_tuple(aInv, -b, tcount));
            }
        }
    }

    if(solutions.empty()){
        return false;
    }

    sort(solutions.begin(), solutions.end(), descendingByTrigramCount);
    multiplier = get<0>(*solutions.begin());
    shift = get<1>(*solutions.begin());
    return true;
}


bool MonoSubstitutionSolver::shift(int &bestSolution) const {

    vector<pair<int, size_t>> solutions;

    for(size_t i = 0; i < 26; ++i){
        Text p = cipherText;
        p.shiftBy(i);
        size_t count = p.englishTrigramCount();
        solutions.push_back(pair<int, size_t>(i, count));
    }

    if(solutions.empty()){
        return false;
    }

    sort(solutions.begin(), solutions.end(), [](const pair<int, size_t> &a, const pair<int, size_t> &b){
        return a.second > b.second;
    });

    bestSolution = solutions.begin()->first;
    return true;
}
