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
#include "Arg.h"


enum optionIndex {
    UNKNOWN, HELP, SHIFT_COUNT, INPUT, OUTPUT
};

const option::Descriptor usage[] =
        {
                {UNKNOWN,     0, "",  "",      option::Arg::None, "USAGE: shift -c shift_count -i input_file -o output_file\n\n"
                                                                          "Options: "},
                {HELP,        0, "",  "help",  option::Arg::None, "  --help \tPrint usage and exit."},
                {SHIFT_COUNT, 0, "c", "count", Arg::Required,     "  -c, --count shift_count \tThe number of letters to shift each plain text character by.  [REQUIRED]"},
                {INPUT,       0, "i", "in",    Arg::Required,     "  -i, --in input_file \tFilename of plain text.  [REQUIRED]"},
                {OUTPUT,      0, "o", "out",   Arg::Required,     "  -o, --out output_file \tFilename where cipher text should be stored.  [REQUIRED]"},
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

    if (options[SHIFT_COUNT] == NULL || options[INPUT] == NULL || options[OUTPUT] == NULL) {
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
    int shift = std::atoi(options[SHIFT_COUNT].arg);
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