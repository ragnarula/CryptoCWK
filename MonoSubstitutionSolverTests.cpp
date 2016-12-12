//
// Created by Raghav Narula on 10/12/2016.
//

#include "catch.hpp"
#include "Text.h"
#include "MonoSubstitutionSolver.h"
using namespace std;

TEST_CASE("substitute test"){
    Text a("abcdefghijklmnopqrstuvwxyz");
    a.substitute("zyxwvutsrqponmlkjihgfedcba");
    REQUIRE(a == Text("zyxwvutsrqponmlkjihgfedcba"));

}


TEST_CASE("Hill climb for shift"){
    cout << "Running Hill Climb test (might take a while)" << endl;
    Text c("alanmathisonturingobefrstjrjunejunewasanenglishcomputerscientistmathematicianlogiciancryptanalystandtheoreticalbiologisthewashighlyinfluentialinthedevelopmentoftheoreticalcomputerscienceprovidingaformalisationoftheconceptsofalgorithmandcomputationwiththeturingmachinewhichcanbeconsideredamodelofageneralpurposecomputerturingiswidelyconsideredtobethefatheroftheoreticalcomputerscienceandartificialintelligenceduringthesecondworldwarturingworkedforthegovernmentcodeandcypherschoolgccsatbletchleyparkbritainscodebreakingcentreforatimeheledhutthesectionresponsibleforgermannaval");
    double originalFitness = c.nGramFitness();
    c.shiftBy(5);
    MonoSubstitutionSolver g(c);
    string k;
    g.hillClimb(k);
    c.substitute(k);
    REQUIRE(c.nGramFitness() - originalFitness < 0.01);
}

TEST_CASE("Hill Climb for affine"){
    cout << "Running Hill Climb test (might take a while)" << endl;
    Text c("alanmathisonturingobefrstjrjunejunewasanenglishcomputerscientistmathematicianlogiciancryptanalystandtheoreticalbiologisthewashighlyinfluentialinthedevelopmentoftheoreticalcomputerscienceprovidingaformalisationoftheconceptsofalgorithmandcomputationwiththeturingmachinewhichcanbeconsideredamodelofageneralpurposecomputerturingiswidelyconsideredtobethefatheroftheoreticalcomputerscienceandartificialintelligenceduringthesecondworldwarturingworkedforthegovernmentcodeandcypherschoolgccsatbletchleyparkbritainscodebreakingcentreforatimeheledhutthesectionresponsibleforgermannaval");
    double originalFitness = c.nGramFitness();
    c.shiftBy(5);
    c.multiply(17);
    MonoSubstitutionSolver g(c);
    string k;
    g.hillClimb(k);
    c.substitute(k);
    REQUIRE(c.nGramFitness() - originalFitness < 0.001);
}

TEST_CASE("Hill Climb for substitution"){
    cout << "Running Hill Climb test (might take a while)" << endl;
    Text c("alanmathisonturingobefrstjrjunejunewasanenglishcomputerscientistmathematicianlogiciancryptanalystandtheoreticalbiologisthewashighlyinfluentialinthedevelopmentoftheoreticalcomputerscienceprovidingaformalisationoftheconceptsofalgorithmandcomputationwiththeturingmachinewhichcanbeconsideredamodelofageneralpurposecomputerturingiswidelyconsideredtobethefatheroftheoreticalcomputerscienceandartificialintelligenceduringthesecondworldwarturingworkedforthegovernmentcodeandcypherschoolgccsatbletchleyparkbritainscodebreakingcentreforatimeheledhutthesectionresponsibleforgermannaval");
    double originalFitness = c.nGramFitness();
    c.substitute("zyxwvutsrqponmlkjihgfedcba");
    MonoSubstitutionSolver g(c);
    string k;
    g.hillClimb(k);
    c.substitute(k);
    REQUIRE(c.nGramFitness() - originalFitness < 0.001);
}