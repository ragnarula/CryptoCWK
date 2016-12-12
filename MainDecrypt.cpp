/*
 * Main.cpp
 *
 *  Created on: 10 Nov 2016
 *      Author: rag
 */

#include <iostream>
#include "Text.h"
#include "optionparser.h"
#include "Util.h"
#include "MonoSubstitutionSolver.h"
#include "PolySubstitutionSolver.h"
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;
enum optionIndex {
    UNKNOWN, HELP, INPUT, OUTPUT, FUNCTION
};

void printStats(const Text &text, const string &header);

const option::Descriptor usage[] =
        {
                {UNKNOWN, 0, "",  "",         option::Arg::None, "USAGE: decrypt -i input_file -o output_prefix\n\n"
                                                                         "Options: "},
                {HELP,    0, "",  "help",     option::Arg::None, "  --help \tOPTIONAL\n\tPrint usage and exit."},
                {INPUT,   0, "i", "in",       Util::Required,    "  -i, --in input_file \tREQUIRED - always \n\tFilename of cipher text."},
                {OUTPUT,  0, "o", "out",      Util::Required,    "  -o, --out output_file \tREQUIRED - when '--function' is not 'stats'\r\n\tOutput file name for decrypted text"},
                {FUNCTION,    0, "f", "function", Util::Required,    "  -f, --function stats|shift|affine|vigenere|hill-climb \tOPTIONAL\n\tFunction to run, defaults to stats, '--output' must be set when this is not 'stats'"},
                {0,       0, 0,   0,          0,                 0}
        };

int main(int argc, char *argv[]) {
    argc -= (argc > 0);
    argv += (argc > 0); // skip program name argv[0] if present
    option::Stats stats(usage, argc, argv);
    std::vector<option::Option> options(stats.options_max);
    std::vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

    if (parse.error())
        return 1;

    if (options[HELP]) {
        option::printUsage(std::cout, usage);
        return 0;
    }

    if (options[INPUT] == NULL || options[FUNCTION] == NULL) {
        option::printUsage(std::cerr, usage);
        return 1;
    }

    //read input
    std::ifstream input(options[INPUT].arg);

    if (input.fail()) {
        std::cerr << "Failed to open input file: " << options[INPUT].arg << std::endl;
        return 1;
    }

    std::stringstream inBuffer;
    inBuffer << input.rdbuf();
    std::string str = inBuffer.str();
    const Text cipherText(str);


    //print file stats
    printStats(cipherText, "Cipher Text Stats");
    Text p = cipherText;

    if (strcmp(options[FUNCTION].arg, "shift") == 0 && options[OUTPUT] != NULL) {
        MonoSubstitutionSolver m(cipherText);
        int key = 0;
        if(!m.shift(key)){
            cout << "Failed to find shift solution." << endl;
            return 1;
        }
        cout << "Key Found: " << key << endl;
        p.shiftBy(key);
        printStats(p, "Pain Text Stats");
        return 0;
    } else if(strcmp(options[FUNCTION].arg, "affine") == 0 && options[OUTPUT] != NULL){
        MonoSubstitutionSolver m(cipherText);
        int multiplier = 0;
        int shift = 0;
        if(!m.affine(multiplier, shift)){
            cout << "Failed to find an affine solution." << endl;
            return 1;
        }
        cout << "Key Found, Multiplier: " << multiplier << " Shift: " << shift << endl;
        p.multiply(multiplier);
        p.shiftBy(shift);
        printStats(p, "Plain Text Stats");
    } else if(strcmp(options[FUNCTION].arg, "hill-climb") == 0 && options[OUTPUT] != NULL) {
        MonoSubstitutionSolver m(cipherText);
        string key;
        if(!m.hillClimb(key)){
            cout << "Failed to find solution by hill-climb." << endl;
            return 1;
        }
        cout << "Key Found: " << key << endl;
        p.substitute(key);
        printStats(p, "Plain Text Stats");
    }else if(strcmp(options[FUNCTION].arg, "vigenere") == 0 && options[OUTPUT] != NULL) {
        PolySubstitutionSolver ps(cipherText);
        string key;
        if(!ps.vigenere(key)){
            cout << "Failed to find viginere solution." << endl;
            return 1;
        }
        cout << "Key Found: " << key << endl;
        p.vigenereAdd(key);
        printStats(p, "Plain Text Stats");
    }

    if(strcmp(options[FUNCTION].arg, "stats") != 0 && options[OUTPUT] != NULL){
        //write output
        std::ofstream output(options[OUTPUT].arg);
        cout << "Writing decrypted text to: " << options[OUTPUT].arg << endl;
        output << cipherText << endl;

        if (output.fail()) {
            std::cerr << "Failed to write output to: " << options[OUTPUT].arg << std::endl;
        }
        output.close();
        cout << "Finished writing successfully." << endl;
    }

    return 0;

}

void printStats(const Text &text, const string &header) {
    static const string tab("\t");
    cout << header << ":" << endl;
    cout << tab << "Number of charachters:          " << text.size() << endl;
    cout << tab << "Index of Coincidence:           " << text.ic() << endl;
    cout << tab << "Chi Squared Unigram Fitness:    " << text.chiSqUnigram() << endl;
    cout << tab << "Number of english Trigrams:     " << text.englishTrigramCount() << endl;
}
