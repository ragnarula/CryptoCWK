//
// Created by Raghav Narula on 11/12/2016.
//

#ifndef CRYPTOCOURSEWORK_STATS_H
#define CRYPTOCOURSEWORK_STATS_H

#include <string>
#include <map>
#include <vector>

const std::vector<char> frequentLetters = {'e','t','a','o','i','n','s','h','r','d','l','c','u','m','w','f','g','y','p','b','v','k','j','x','q','z'};

const std::map<std::string, double> unigramProbs = {
        {"e", 0.12702},
        {"t", 0.09056},
        {"a", 0.08167},
        {"o", 0.07507},
        {"i", 0.06996},
        {"n", 0.06749},
        {"s", 0.06327},
        {"h", 0.06094},
        {"r", 0.05987},
        {"d", 0.04253},
        {"l", 0.04025},
        {"c", 0.02782},
        {"u", 0.02758},
        {"m", 0.02406},
        {"w", 0.02360},
        {"f", 0.02228},
        {"g", 0.02015},
        {"y", 0.01974},
        {"p", 0.01929},
        {"b", 0.01492},
        {"v", 0.00978},
        {"k", 0.00772},
        {"j", 0.00153},
        {"x", 0.00150},
        {"q", 0.00095},
        {"z", 0.00074}
};

const std::map<std::string, double> bigramProbs = {
        {"th",0.0271},
        {"en",0.0113},
        {"ng",0.0089},
        {"he",0.0233},
        {"at",0.0112},
        {"al",0.0088},
        {"in",0.0203},
        {"ed",0.0108},
        {"it",0.0088},
        {"er",0.0178},
        {"nd",0.0107},
        {"as",0.0087},
        {"an",0.0161},
        {"to",0.0107},
        {"is",0.0086},
        {"re",0.0141},
        {"or",0.0106},
        {"ha",0.0083},
        {"es",0.0132},
        {"ea",0.0100},
        {"et",0.0076},
        {"on",0.0132},
        {"ti",0.0099},
        {"se",0.0073},
        {"st",0.0125},
        {"ar",0.0098},
        {"ou",0.0072},
        {"nt",0.0117},
        {"te",0.0098},
        {"of",0.0071}
};

const std::map<std::string, double> trigramProbs = {
        {"the",0.0181},
        {"ere",0.0031},
        {"hes",0.0024},
        {"and",0.0073},
        {"tio",0.0031},
        {"ver",0.0024},
        {"ing",0.0072},
        {"ter",0.0030},
        {"his",0.0024},
        {"ent",0.0042},
        {"est",0.0028},
        {"oft",0.0022},
        {"ion",0.0042},
        {"ers",0.0028},
        {"ith",0.0021},
        {"her",0.0036},
        {"ati",0.0026},
        {"fth",0.0021},
        {"for",0.0034},
        {"hat",0.0026},
        {"sth",0.0021},
        {"tha",0.0033},
        {"ate",0.0025},
        {"oth",0.0021},
        {"nth",0.0033},
        {"all",0.0025},
        {"res",0.0021},
        {"int",0.0032},
        {"eth",0.0024},
        {"ont",0.0020}
};

const std::map<std::string, double> quadgramProbs = {
        {"ofthe",  0.0018},
        {"andth",  0.0007},
        {"ction",  0.0005},
        {"ation",  0.0017},
        {"ndthe",  0.0007},
        {"which",  0.0005},
        {"inthe",  0.0016},
        {"onthe",  0.0007},
        {"these",  0.0005},
        {"there",  0.0009},
        {"edthe",  0.0006},
        {"after",  0.0005},
        {"ingth",  0.0009},
        {"their",  0.0006},
        {"eofth",  0.0005},
        {"tothe",  0.0008},
        {"tiona",  0.0006},
        {"about",  0.0004},
        {"ngthe",  0.0008},
        {"orthe",  0.0006},
        {"erthe",  0.0004},
        {"other",  0.0007},
        {"forth",  0.0006},
        {"ional",  0.0004},
        {"atthe",  0.0007},
        {"ingto",  0.0006},
        {"first",  0.0004},
        {"tions",  0.0007},
        {"theco",  0.0005},
        {"would",  0.0004}
};

#endif //CRYPTOCOURSEWORK_STATS_H
