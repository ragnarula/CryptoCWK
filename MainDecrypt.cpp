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
                {UNKNOWN, 0, "",  "",     option::Arg::None, "USAGE: decrypt -i input_file -o output_file\n\n"
                                                                     "Options: "},
                {HELP,    0, "",  "help", option::Arg::None, "  --help                  \tPrint usage and exit."},
                {INPUT,   0, "i", "in",   Util::Required,     "  -i, --in input_file     \t[REQUIRED] Filename of cipher text."},
                {OUTPUT,  0, "o", "out",  Util::Required,     "  -o, --out output_file   \t[REQUIRED] Filename where decrypted plain text should be stored."},
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

    //read input
    std::ifstream input(options[INPUT].arg);

    if (input.fail()) {
        std::cerr << "Failed to open input file: " << options[INPUT].arg << std::endl;
        return 1;
    }

    std::stringstream inBuffer;
    inBuffer << input.rdbuf();
    std::string str = inBuffer.str();
    Text cipherText(str);

    //detect mono-alphabetic
    if(fabs(cipherText.ic() - 1.73) < 0.1){
        std::cout << "Cipher text index of coincidence: " << cipherText.ic() << std::endl;
        std::cout << "Suspecting mono-alphabetic cipher." << std::endl;

        Text plainText = cipherText;
        size_t maxShift = 0;
        size_t maxCount = plainText.englishTrigramCount();

        for(size_t i = 1; i <= 26; i++) {
            plainText.shiftForwards();
            size_t count = plainText.englishTrigramCount();
            if (count > maxCount) {
                maxShift = i;
                maxCount = count;
            }
//            std::cout << "Shift: " << i << " Trigrams: " << count << std::endl;
        }

        if(maxCount > 0.2 * (plainText.size() / 3)){
            std::cout << "Decryption Success!\nShift cipher key: " << maxShift << std::endl;
            return 0;
        } else {
            std::cout << "Shift cipher failed, attempting Affine." << std::endl;
        }

        vector<char> letters = {'e','t','a','o','i','n','s','h','r','d','l','c','u','m','w','f','g','y','p','b','v','k','j','x','q','z'};
        Text plainText2 = cipherText;
        multimap<size_t, char> freqs = plainText2.getLetterFrequencies();

        int c1 = freqs.rbegin()->second - 'a';
        int c2 = (++freqs.rbegin())->second - 'a';
        int cDiff = c1 - c2;

        for(auto i = letters.begin(); i != letters.end(); i++){
            for(auto j = letters.begin(); j != letters.end(); j++){

                if(i == j){
                    continue;
                }

                int x1 = *i - 'a';
                int x2 = *j - 'a';
                int xDiff = x1 - x2;
                int xDiffInv = 0;
                int y = 0;

                int gcd = Util::gcdx(xDiff, 26, &xDiffInv, &y);

                int A = (cDiff * xDiffInv) % 26;

                int check = Util::gcd(A, 26);
                if(check == 1){
                    cout << "POTENTIAL A FOUND: " << A << endl;

                    int aInv = 0;
                    int yy = 0;

                    Util::gcdx(A, 26, &aInv, &yy);
                    int b = ((c1 - (A * x1)) % 26 + 26) % 26;
                    Text p = cipherText;
                    p.shiftBy(-b);
                    p.multiply(aInv);
                    cout << "B: " << b << " TRIGRAM COUNT: " << p.englishTrigramCount() << endl;
                    i = --letters.end();
                    j = --letters.end();
                }
            }
        }

        return 0;
    }
}
