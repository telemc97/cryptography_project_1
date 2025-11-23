#include <cmath>
#include <iostream>

#include "Polynomial.h"
#include "Utils.h"
#include "Logger.h"
#include <ostream>
#include <ctime>
#include <math.h>
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

    constexpr uint32 max_key_length = 20;
    const uint32 key_length_friedman = Crypto::findKeyLengthFriedman(text, max_key_length);
    Logger::instance().log("Key Length according to Friedman test is %i", key_length_friedman);
    const String key = Crypto::getKeyWithFrequencyAnalysis(text, key_length_friedman);
    Logger::instance().log("Key is: %s", key.c_str());
    const String decrypted_text = Crypto::vigenereDecipher(text, key);
    Logger::instance().log("Decrypted text is: \n %s", decrypted_text.c_str());
}

void exercise3() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    uint16 original_message = static_cast<uint16>(std::rand() % 65536);

    uint16 encrypted_message = Crypto::encrypt16bit(original_message);
    uint16 decrypted_message = Crypto::decrypt16bit(encrypted_message);

    if (original_message == decrypted_message) {
        Logger::instance().log("[SUCCESS] The decoding formula is correct!");
    } else {
        Logger::instance().log("[FAILURE] The decoded message does not match the original.");
    }
}

void exercise5() {
    String charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.!?()-";

    const String message = "HELLO-WORLD";
    Logger::instance().log("Original message is: %s", message.c_str());
    Logger::instance().log("Original message's representation in bits is: %s", Utils::toBitString(message).c_str());
    const String key = Crypto::generateOTPKey(message.size(), charset);
    Logger::instance().log("Key is: %s", key.c_str());
    Logger::instance().log("Key representation in bits is: %s", Utils::toBitString(key).c_str());
    const String encrypted_message = Crypto::encrypt(message, key);
    Logger::instance().log("Encrypted message is: %s", encrypted_message.c_str());
    Logger::instance().log("Encrypted message's representation in bits is: %s", Utils::toBitString(encrypted_message).c_str());
    const String decrypted_message = Crypto::decrypt(encrypted_message, key);
    Logger::instance().log("Decrypted message is: %s", decrypted_message.c_str());
    Logger::instance().log("Decrypted message's representation in bits is: %s", Utils::toBitString(decrypted_message).c_str());
    if (message == decrypted_message) {
        Logger::instance().log("[SUCCESS] Decryption is correct");
    } else {
        Logger::instance().log("[FAILURE] The Decryption failed.");
    }
}

void exercise6() {
    uint8 count = 0;
    constexpr uint8 degree = 5;

    Logger::instance().log("Primitive polynomials:");
    // 111111 = 63
    uint8 max_coefficient = 63;
    // 100000 = 32
    uint8 min_coefficient = 32;
    for (uint8 i = min_coefficient; i < max_coefficient + 1; i++) {
        Vector(int32) coefficients = Utils::intToBits(i);
        Polynomial gf2_polynomial = Polynomial(degree, coefficients);
        if (gf2_polynomial.gf2IsPrimitive()) {
            Logger::instance().log(gf2_polynomial.toString());
            count++;
        }
    }

    Logger::instance().log("Found %i Primitive polynomials", count);
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

    Logger::instance().print_separator();
    Logger::instance().log("Exercise 3:");
    Logger::instance().print_separator();
    exercise3();
    Logger::instance().print_separator();
    Logger::instance().print_empty_line();

    Logger::instance().print_separator();
    Logger::instance().log("Exercise 5:");
    Logger::instance().print_separator();
    exercise5();
    Logger::instance().print_separator();
    Logger::instance().print_empty_line();

    Logger::instance().print_separator();
    Logger::instance().log("Exercise 6:");
    Logger::instance().print_separator();
    exercise6();
    Logger::instance().print_separator();
    Logger::instance().print_empty_line();
    return 0;
}