//
// Created by Raghav Narula on 15/12/2016.
//


#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "optionparser.h"
#include "Text.h"
#include "Util.h"
#include "MonoSubstitutionSolver.h"

using namespace std;

enum optionIndex {
    UNKNOWN, HELP, LOG, RESULT, INPUT
};

void printStats(const Text &text, const string &header);

const option::Descriptor usage[] =
        {
                {UNKNOWN, 0, "",  "",       option::Arg::None, "USAGE: decrypt -i input_file -o output_prefix\n\n"
                                                                       "Options: "},
                {HELP,    0, "",  "help",   option::Arg::None, "  --help \tOPTIONAL\n\tPrint usage and exit."},
                {LOG,     0, "l", "log",    Util::Required,    "  -l, --log file \tOPTIONAL\n\tFilename to store log text."},
                {INPUT,   0, "i", "in",    Util::Required,     "  -i, --in input_file \t[REQUIRED] - always\n\t Filename of plain text."},
                {RESULT,  0, "r", "result", Util::Required,    "  -r, --result output_file \tREQUIRED - always\n\tOutput file name for test results in CSV format <text length>,<difference%>,<generations>"},
                {0,       0, 0,   0,        0,                 0}
        };

void runTest(Text& t, ostream& res, ostream& log, size_t sampleSize){
    static string letters("abcdefghijklmnopqrstuvwxyz");
    for(int i = 0; i < 20; ++i){
        log << "Test " << i << " for sample size " << sampleSize << endl;
        cout << "Test " << i << " for sample size " << sampleSize << endl;
        Text sample("");
        if(t.sample(sample, sampleSize)){
            string key = letters;
            random_shuffle(key.begin(), key.end());
            Text cipherText = sample;
            cipherText.substitute(key);
            size_t gen = 0;
            MonoSubstitutionSolver m(cipherText);
            string foundKey;
            stringstream preLog;
            if(m.hillClimb(foundKey,gen,preLog)){
                log << preLog.str();
                cipherText.substitute(foundKey);
                const string& orig = sample.getString();
                const string& recovered = cipherText.getString();
                size_t diff = 0;
                for(size_t i = 0; i < recovered.size(); ++i){
                    if(orig[i] != recovered[i]){
                        ++diff;
                    }
                }
                double diffPercent = (double) diff / (double) sample.size();
                ios::fmtflags f( cout.flags() );
                res  << sampleSize << "," << std::setprecision (15) << diffPercent << "," << gen << endl;
                cout.flags( f );
            }
        }
    }
}

int main(int argc, char *argv[]){
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

    if(options[RESULT].arg == NULL){
        option::printUsage(std::cerr, usage);
        return 1;
    }

    std::ofstream result(options[RESULT].arg);
    stringstream logStream;

    std::ifstream input(options[INPUT].arg);
    if (input.fail()) {
        std::cerr << "Failed to open input file: " << options[INPUT].arg << std::endl;
        return 1;
    }

    std::stringstream inBuffer;
    inBuffer << input.rdbuf();
    std::string str = inBuffer.str();
    Text plainText(str);

    runTest(plainText, result, logStream, 50);
    runTest(plainText, result, logStream, 100);
    runTest(plainText, result, logStream, 250);
    runTest(plainText, result, logStream, 500);
    runTest(plainText, result, logStream, 1000);
    runTest(plainText, result, logStream, 2000);

    if(options[LOG].arg != NULL){
        std::ofstream logout(options[LOG].arg);
        logout << logStream.str();

        if (logout.fail()) {
            std::cerr << "Failed to write log output to: " << options[LOG].arg << std::endl;
        }
    }

}

