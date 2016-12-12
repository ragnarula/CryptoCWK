//
// Created by Raghav Narula on 12/12/2016.
//

#include "catch.hpp"
#include "Text.h"
#include "PolySubstitutionSolver.h"


using namespace std;

TEST_CASE("Solve Poly"){
    std::string key("keyw");

    Text t("alanmathisonturingobefrstjrjunejunewasanenglishcomputerscientistmathematicianlogiciancryptanalystandtheoreticalbiologisthewashighlyinfluentialinthedevelopmentoftheoreticalcomputerscienceprovidingaformalisationoftheconceptsofalgorithmandcomputationwiththeturingmachinewhichcanbeconsideredamodelofageneralpurposecomputerturingiswidelyconsideredtobethefatheroftheoreticalcomputerscienceandartificialintelligenceduringthesecondworldwarturingworkedforthegovernmentcodeandcypherschoolgccsatbletchleyparkbritainscodebreakingcentreforatimeheledhutthesectionresponsibleforgermannaval");
    t.vigenereAdd(key);

    PolySubstitutionSolver p(t);

    string foundKey;
    REQUIRE(p.vigenere(foundKey));
    REQUIRE(foundKey == "qwce");
}