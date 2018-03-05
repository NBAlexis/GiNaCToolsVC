//=============================================================================
// FILENAME : ginac_test.cpp
// 
// DESCRIPTION:
//
// REVISION:
//  [3/5/2018 nbale]
//=============================================================================
#include "ginac_test.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{

    //In the debug window the exceptions show crazy!!!!!!!
    //try something else
    //Cout2VisualStudioDebugOutput c2do;
    RedirectIOToConsole();

    int error = 0;

    cout << " error = " << error << endl; error += exam_archive();
    cout << " error = " << error << endl; error += exam_clifford();
    cout << " error = " << error << endl; error += exam_color();
    cout << " error = " << error << endl; error += main_bugme_chinrem_gcd();
    cout << " error = " << error << endl; error += main_check_inifcns();
    cout << " error = " << error << endl; error += main_check_lsolve();
    cout << " error = " << error << endl; error += main_check_matrices();
    cout << " error = " << error << endl; error += main_check_mul_info();
    cout << " error = " << error << endl; error += main_check_numeric();
    cout << " error = " << error << endl; error += main_exam_cra();
    cout << " error = " << error << endl; error += main_exam_differentiation();
    cout << " error = " << error << endl; error += main_exam_factor();
    cout << " error = " << error << endl; error += main_exam_hashmap();
    cout << " error = " << error << endl; error += main_exam_indexed();
    cout << " error = " << error << endl; error += main_exam_inifcns();
    cout << " error = " << error << endl; error += main_exam_inifcns_nstdsums();
    cout << " error = " << error << endl; error += main_exam_lsolve();
    cout << " error = " << error << endl; error += main_exam_matrices();
    cout << " error = " << error << endl; error += main_exam_misc();
    cout << " error = " << error << endl; error += main_exam_mod_gcd();
    cout << " error = " << error << endl; error += main_exam_normalization();
    cout << " error = " << error << endl; error += main_exam_numeric();
    cout << " error = " << error << endl; error += main_exam_paranoia();
    cout << " error = " << error << endl; error += main_exam_polygcd();
    cout << " error = " << error << endl; error += main_exam_powerlaws();
    cout << " error = " << error << endl; error += main_exam_pseries();
    cout << " error = " << error << endl; error += main_exam_real_imag();
    cout << " error = " << error << endl; error += main_exam_structure();
    cout << " error = " << error << endl; error += main_factor_univariate_bug();
    cout << " error = " << error << endl; error += main_heur_gcd_bug();
    cout << " error = " << error << endl; error += main_match_bug();
    cout << " error = " << error << endl; error += main_numeric_archive();
    cout << " error = " << error << endl; error += main_parser_bugs();
    cout << " error = " << error << endl; error += main_pgcd_infinite_loop();
    cout << " error = " << error << endl; error += main_pgcd_relatively_prime_bug();
    cout << " error = " << error << endl; error += main_time_antipode();
    cout << " error = " << error << endl; error += main_time_dennyfliegner();
    cout << " error = " << error << endl; error += main_time_fateman_expand();
    cout << " error = " << error << endl; error += main_time_gammaseries();
    cout << " error = " << error << endl; error += main_time_hashmap();
    cout << " error = " << error << endl; error += main_time_lw_A();
    cout << " error = " << error << endl; error += main_time_lw_B();
    cout << " error = " << error << endl; error += main_time_lw_C();
    cout << " error = " << error << endl; error += main_time_lw_D();
    cout << " error = " << error << endl; error += main_time_lw_E();
    cout << " error = " << error << endl; error += main_time_lw_F();
    cout << " error = " << error << endl; error += main_time_lw_G();
    cout << " error = " << error << endl; error += main_time_lw_H();
    cout << " error = " << error << endl; error += main_time_lw_IJKL();
    cout << " error = " << error << endl; error += main_time_lw_M1();
    cout << " error = " << error << endl; error += main_time_lw_M2();
    cout << " error = " << error << endl; error += main_time_lw_N();
    cout << " error = " << error << endl; error += main_time_lw_O();
    cout << " error = " << error << endl; error += main_time_lw_P();
    cout << " error = " << error << endl; error += main_time_lw_Pprime();
    cout << " error = " << error << endl; error += main_time_lw_Q();
    cout << " error = " << error << endl; error += main_time_lw_Qprime();
    cout << " error = " << error << endl; error += main_time_parser();
    cout << " error = " << error << endl; error += main_time_toeplitz();
    cout << " error = " << error << endl; error += main_time_uvar_gcd();
    cout << " error = " << error << endl; error += main_time_vandermonde();

    cout << " end with error:" << error << endl;
    system("pause");
    return error;
}
