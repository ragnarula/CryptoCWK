//
// Created by Rag on 15/11/2016.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "optionparser.h"
#include "Text.h"
#include "Util.h"


enum optionIndex {
    UNKNOWN, HELP, KEY, INPUT, OUTPUT
};

const option::Descriptor usage[] =
        {
                {UNKNOWN,     0, "",  "",      option::Arg::None, "USAGE: shift -k key -i input_file -o output_file\n\n"
                                                                          "Options: "},
                {HELP,        0, "",  "help",  option::Arg::None, "  --help \tPrint usage and exit."},
                {KEY, 0, "k", "count", Util::Required,     "  -k, --key key \t[REQUIRED] The number of letters to shift each plain text character by. "},
                {INPUT,       0, "i", "in",    Util::Required,     "  -i, --in input_file \t[REQUIRED] Filename of plain text."},
                {OUTPUT,      0, "o", "out",   Util::Required,     "  -o, --out output_file \t[REQUIRED] Filename where cipher text should be stored."},
                {0,           0, 0,   0,       0,                 0}
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

    if (options[KEY] == NULL || options[INPUT] == NULL || options[OUTPUT] == NULL) {
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
    Text plainText(str);

    //shift
    int shift = std::atoi(options[KEY].arg);
    Text cipherText = plainText;
    cipherText.shiftBy(shift);

    //write output
    std::ofstream output(options[OUTPUT].arg);
    output << cipherText;

    if (output.fail()) {
        std::cerr << "Failed to write output to: " << options[OUTPUT].arg << std::endl;
    }

    output.close();
}