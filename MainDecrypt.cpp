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
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;
enum optionIndex {
    UNKNOWN, HELP, INPUT, OUTPUT
};

const option::Descriptor usage[] =
        {
                {UNKNOWN, 0, "",  "",     option::Arg::None, "USAGE: decrypt -i input_file -o output_prefix\n\n"
                                                                     "Options: "},
                {HELP,    0, "",  "help", option::Arg::None, "  --help                  \tPrint usage and exit."},
                {INPUT,   0, "i", "in",   Util::Required,     "  -i, --in input_file     \t[REQUIRED] Filename of cipher text."},
                {OUTPUT,  0, "o", "out",  Util::Required,     "  -o, --out output_prefix   \t[REQUIRED] Prefix for output file name <prefix><cipher>.txt"},
                {0,       0, 0,   0,      0,                 0}
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

    if (options[INPUT] == NULL || options[OUTPUT] == NULL) {
        option::printUsage(std::cerr, usage);
        return 1;
    }

    string prefix = string(options[OUTPUT].arg);
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

    //detect mono-alphabetic
    std::cout << "Cipher text index of coincidence: " << cipherText.ic() << std::endl;
    const Text plainText = cipherText;

    MonoSolutionSetByTrigrams mono = plainText.solveMono();
    MonoSolutionSetByTrigrams shift = plainText.solveShift();
    VigenereSolutionSet vig = plainText.solveVigenere();

    if(!mono.empty()){
        cout << "Affine Solution found: \t" << mono.begin()->getTrigramCount() << endl;
        Text p = cipherText;
        p.multiply(mono.begin()->getMultiplier());
        p.shiftBy(mono.begin()->getShift());
        string filename = prefix + "_affine.txt";
        std::ofstream output(filename);
        output << p;

        if (output.fail()) {
            std::cerr << "Failed to write output to: " << filename << std::endl;
        }
    }
    if(!shift.empty()){
        cout << "Shift solution found: \t" << shift.begin()->getTrigramCount() << endl;
        Text p = cipherText;
        p.shiftBy(shift.begin()->getShift());
        string filename = prefix + "_shift.txt";
        std::ofstream output(filename);
        output << cipherText;

        if (output.fail()) {
            std::cerr << "Failed to write output to: " << filename << std::endl;
        }
    }
    if(!vig.empty()){
        cout << "Vigenere solution found: \t" << vig.begin()->getTrigramCount() << endl;
        Text p = cipherText;
        p.vigenereAdd(vig.begin()->getKey());
        string filename = prefix + "_vigenere.txt";
        std::ofstream output(filename);
        output << cipherText;

        if (output.fail()) {
            std::cerr << "Failed to write output to: " << filename << std::endl;
        }
    }


    return 0;

}
