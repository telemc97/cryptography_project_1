#include <iostream>

#include "Polynomial.h"
#include "Utils.h"
#include "Logger.h"
#include <ostream>

#include "Crypto.h"

void exercise1() {
    wide_char initial_message[24] = {L'ο',L'κ',L'η',L'θ',L'μ',L'φ',L'δ',L'ζ',L'θ',L'γ',L'ο',L'θ',
                                     L'χ',L'υ',L'κ',L'χ',L'σ',L'φ',L'θ',L'μ',L'φ',L'μ',L'χ',L'γ'};
    // x^2+3x+1
    Polynomial g_x(2, {1,3,1});

    // x^5+3x^4+3x^3+7x^2+5x+4
    Polynomial f_x(5, {1,3,3,7,5,4});

    const Polynomial q_x = f_x / g_x;
    const Polynomial r_x = f_x % g_x;

    Logger::instance().log("f(x) = %s", f_x.toString().c_str());
    Logger::instance().log("g(x) = %s", g_x.toString().c_str());
    Logger::instance().log("f(x) / g(x) = %s with a remainder of %s", q_x.toString().c_str(), r_x.toString().c_str());

    wide_char final_message_letters[24];
    int8 final_message_numbers[24];

    const int8 key_offset = r_x.getCoefficients()[r_x.getDegree()];

    for (int i = 0; i < 24; i++) {
        final_message_numbers[i] = Utils::convertGreekCharToInt(initial_message[i]) - key_offset;
        final_message_letters[i] = Utils::convertIntToGreekChar(final_message_numbers[i]);
    }

    Logger::instance().log("Decoded Message is: ");
    for (const auto wchar : final_message_letters) {
        std::wcout << wchar;
    }
    std::cout << std::endl;
}

void exercise2() {
    String text = "SCEELGZSSLCRFPWUTNTSBXAHRCCCMSAGVCAHYOQHQRKAHRTFRSAEFGDEGWOEGWBFVFGUSVEWOEGOALP"
                  "DRNGGZPSVFOXAUTBNBVVLACESFWUTRQPLSUEATZVKOMNGVREHTVPWNFAUEVBTLOAGGVRZBMNAPESPNV"
                  "FGBELTUVBTDPKRNDVWJEBSIESUIHZHUWOUZNBOJHIAVTVLPSORZBOAHRPFVLPCNYZNHHNQLCHKOOBGC"
                  "AWUEHGFBFPNGBWGSKDVGWBFHLZBFROVUYQPRHYOQHQRVIYVZDNUAIGYSNVZTBNBRPARRZSYQLXCYCFA"
                  "CEBSHUWPSFHSVFJRRNGRLOEFVNRGMTURIESUIHZHHJPNTFOLKAHVFWFKVMRGVVFNLVXSVVLAFVBGZLH"
                  "HZOATYAVAHUWYENESFGTECRCCDLISLCHKOOBGCAWPDRNWALVTURPESPNLBIJASLTRHNZHLSNBVVLABH"
                  "HGZLRRNFRGAHREDRGWLRJVBSYEORMBFKTUVGCGPNGNHJZPCUGVRQWRBQIPWAWBVRRSZFBESNUOIQROF"
                  "WUTVAHUGZENESGZLPRBDYWIELBBQLOEXASRGMTURQHJCEVQCALDAAGHBKVUAQSTGAIFGWPSSHRESVVV"
                  "NGGVVFRTUNHVSTBRLCAVAHRXBRWVFGUWFUBRIROAVPDBAHXFVWNAMBFLWUBWFAKOXACJKVMRCSBHSEG"
                  "UOGOLRRVHUAUKSBFRPHMCYSGZHTNAMBFLWVYZNYYERGVNLPSNNQAWDTBAKBMSDORKRDSOAGVRLVPBSH"
                  "UAZCHEJROOEALCHLOIAXHUSAAGGVRSNEBSHJWUTLSWIWOEUNRCJVDHPSQWUOHTVFUPEAPSCZFSVPGNF"
                  "KMNGVREHTVPGGGTAXRHRFVRGJSALFMRATNEVUFUSCJVDHPSQTPNBZWNDAHRBFREKISSSEWUTVNZNFKI"
                  "AGSTJHLPNZPMSUFYOJKVFTEOIAAAGVCADHWFBTZGAIBARRUVMCBGVLPOABTJZPTRYWTZAAAQGBGUNBJ"
                  "KUSAIFVHGZHTFUCBLZOARICLVTUVGCSYTBSHUWJUEISJZHTNESGZLBNFWPJLQHVFRELNGFWGZPNXJSP"
                  "GBLQFSGVVWAGVEWLTUVBTKAHNGOEWMAVEZLFLCRFGNJFFBEGPALNGVTVUYEFROEUOOESCESUYFBFGGM"
                  "IAISALPNTBFZSAHRZOGAJSBEDUQZIPFCESUYGUWAYHLBAUGZHTYVBRAKOAGHUAUKNCSEKVNPNBTWAAY"
                  "BBTOPTUBIGSUYBASBXAHRFSGZYERGVRXPRFGCAWPSBOJVGBSGEOVFPNTNBQWEPREWRFJELBIQGUTRKD"
                  "RUAAYNKLWYHBJSIWYBEVUULOEZNMOWAOTVJRQVUNASJLOEBEMBXWHLFWPKAHRFSQSFSBEANLOEZNHVU"
                  "ZOERBTAUEREWAYAHRFSPGUDGUWAYPSNPSELHIANABMUTBSWALLLYVURFJEBEHNDLNGVBBLOEEJCEVZY"
                  "BHVNNLTBUOIWHNVDHUSAIFSOVJSYUVUULVDBTCBVYEFROEUOWBEYVVVNGGVVFRTUNHGZLRRVGNFFGBB"
                  "RRFNIARSEGYSPVSALPSGGVNLJAATSGSSOATCASUIDBTJZPCUVGGZLAIRFNYLFBEVHEHNORWAYZIABHU"
                  "WYWBERFZLHNFHBZHVRNBVIOITUSELOAAGVNLLVREMBFLIAGVVKYOBZWFUVNFVRRJHBYLOOGCEGUOGLO"
                  "IFJSZANHGFOLAZAZNHGWYOSRBIAYOAZSALPNGRZYANEAPSVKHMNGHRJVFURFRVPTLGVBKLTJBWQGUTG"
                  "UWACHRRFISXPCVRBGAAHVAYGZLRRVGNLOIEQQBFZTVGIRFAHRESNLOIEQQBEWOARBGOOIPUWFLOEBAS"
                  "GZHTZNYRKHNRVBFLLIABFNFPSNNQAWDTBATBJDAAGCSSIEGGSEOVRQJSJASLPNZYAAMBGWISAIBAWAG"
                  "AHREKBJKSLBIUSCEGBVNNLSBZSXAUDBSOQJPVRFCZWRIAQCSSKEFVFRLVFVARBMATUROAKDEENRRKPR"
                  "RGCSAUDBHHJZHTZNYRKAHVAUFLPCXVTLGBDBAHUSCEGUOGQVUZNMUSCENYZGZLTENWAAUGNARVFAEYY"
                  "WTWUCRVBGZLWBEZQQVUQBBGZHVRDIRKAIBAGNFKYBHKBFAJHFHSAUDNAGJWYSGUWFAZAUNFQLOIATHB"
                  "HBTLBIEXPNTRFBFPTVFOZSATRECSLLMCRFNELNGCFBTHBYLHUSAIFNANLAEEBTCJVBNOZLWHRYLHESP"
                  "NVAURSYLLPVVDKHBBRRPWEEVSAULSJUSGZLRLBIJASLZBHVNHTRVBGZLDVESPLPOABTFUPEAGWSAJRR"
                  "FSNJJHVGVVFRTUNHNLHSHCSEXPCVNZYWCEYVHVKILRARRVBSRBTFWCEENZGZPNTFHUAZIFACGSUYNGH"
                  "REWTNGOQWLPNAOYQZIFNHNDSBHGALXLEYVBTAZTUNHNYVOQFQVWUTVFHUSZATESNLKENYCSOOAGJSPS"
                  "UCNYZPMYIBFWGQPWBAHTGHNLQSRHLRVAHBAATUNBGZHTURKNFASGBYAGDTUROAKDEEFVRKQUFGQHJPO"
                  "HFVBOAHVAUFLPCXNBQZLWNAHFLVKABKGZLAAFKRJZTBDIRKAIBAGNFKISUSFWLSGUWACZHRJOALZTBE"
                  "OVKLQHRGGAVNFNBQZLWNAHFLVKABKGZLAAFKRJZTBGVBKLTURBGZLRRFHUWPDRNCSVPSFNHVKMAPGWB"
                  "FIYGUWFAKOAGARSUACRGFATIFGWPVPSFNHVKMAPGWBFVFGUSJGYLQJSQGUTYVYRLOEJNMGZPNTFOEWP"
                  "MRNBNUVNFGFHUAIIRRVKZAGVGSSJTVBBGZLIQROPGBLQOSRPWRRFGRVPNGUSJGYDFGVVKPSBXPHLPTU"
                  "VBXLOIATGPGBLQOSQGUEORHGWYIGUWACAHRESVKHNRNHRJDALGCQGAHVFWGZPNXGVVFNSPBIYVIEVZD"
                  "EGCEQNZVLALRVBBLOEEJCEVZTURFRAZCBAHVFBAYYMNKSITUHVJYIGNHVGUWURBGZPNTFRBFALBBYDM"
                  "PTREWTZAAAQWGZPNXGVNLKIFFOGAZFNPHVGUIACFRKLNGQOLKPSNXSLVYIIVBTXVRPRWAYVOQFQVWUT"
                  "VFHF";

    Crypto crypto = Crypto(text);
    const uint32 min_word_length = 14;
    const uint32 key_length_kasiski = crypto.findKeyLengthKasiski(min_word_length);
    Logger::instance().log("Key Length according to Kasiski method is %i", key_length_kasiski);
    const uint32 max_key_length = 20;
    const uint32 key_length_friedman = crypto.findKeyLengthFriedman(max_key_length);
    Logger::instance().log("Key Length according to Friedman test is %i", key_length_friedman);
    const String key = crypto.getKeyWithFrequencyAnalysis(key_length_friedman);
    Logger::instance().log("Key is: %s", key.c_str());
    const String decrypted_text = crypto.decryptMessageWithKey(key);
    Logger::instance().log("Decrypted text is: \n %s", decrypted_text.c_str());

}

int main() {
    std::setlocale(LC_ALL, "en_US.UTF-8");

    Logger::instance().print_separator();
    Logger::instance().log("Exercise 1:");
    Logger::instance().print_separator();
    exercise1();
    Logger::instance().print_separator();
    Logger::instance().print_empty_line();

    Logger::instance().print_separator();
    Logger::instance().log("Exercise 2:");
    Logger::instance().print_separator();
    exercise2();
    Logger::instance().print_separator();
    Logger::instance().print_empty_line();

    return 0;
}