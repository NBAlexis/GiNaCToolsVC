//=============================================================================
// FILENAME : ginacra_test.cpp
// 
// DESCRIPTION:
//
// REVISION:
//  [3/9/2018 nbale]
//=============================================================================
#include "GINACRA_Test.h"

using namespace std;

CTestFactory GFac;

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

    MultivariatePolynomialSettings::InitializeGiNaCRAMultivariateMR();

    error += testmain();
    error += CppUnit::iErrors;

#if 0
    //cout << "error = " << error << endl;
    //error += benchmark_CAD_1main(); this CANNOT run because it contains a "UnivariatePolynomial( *i, )", what's this??
    cout << "error = " << error << endl;
    error += benchmark_Groebner_1main();
    cout << "error = " << error << endl;
    error += example1main();
    cout << "error = " << error << endl;
    error += example2main();
    cout << "error = " << error << endl;
    error += example3main();
    cout << "error = " << error << endl;
    error += example4main();
    cout << "error = " << error << endl;
    error += example_AlgoSynmain();
    cout << "error = " << error << endl;
    error += example_CADincremental_1main();
    cout << "error = " << error << endl;
    error += example_CADincremental_2main();
    cout << "error = " << error << endl;
    error += example_CADincremental_3main();
    cout << "error = " << error << endl;
    error += example_CAD_1main();
    cout << "error = " << error << endl;
    error += example_CAD_2main();
    cout << "error = " << error << endl;
    error += example_CAD_3main();
    cout << "error = " << error << endl;
    error += example_CAD_4main();
    cout << "error = " << error << endl;
    error += example_CAD_5main();
    cout << "error = " << error << endl;
    error += example_CAD_6main();
    cout << "error = " << error << endl;
    error += example_CAD_7main();
    cout << "error = " << error << endl;
    error += example_CAD_8main();
    cout << "error = " << error << endl;
    error += example_CAD_9main();
    cout << "error = " << error << endl;
    error += example_CAD_Amain();
    cout << "error = " << error << endl;
    error += example_CAD_Bmain();
    cout << "error = " << error << endl;
    error += example_CAD_Cmain();
    cout << "error = " << error << endl;
    error += example_IR_1main();
    cout << "error = " << error << endl;
    error += example_IR_2main();
    cout << "error = " << error << endl;
    error += example_IR_3main();
    cout << "error = " << error << endl;
    error += example_IR_4main();
    //cout << "error = " << error << endl;
    //error += example_NFM2011presentationmain();
    //cout << "error = " << error << endl;
    //error += example_RAN_1main();
    cout << "error = " << error << endl;
    error += example_RAN_2main();
    cout << "error = " << error << endl;
    error += example_RAN_3main();
    //cout << "error = " << error << endl;
    //error += example_SGB_1main();
#endif

//ADDTESTFUNCTIONS

    cout << "Test End with error = " << error << endl;
    system("pause");
    return error;
}