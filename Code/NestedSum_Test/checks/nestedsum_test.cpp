//=============================================================================
// FILENAME : nestedsum_test.cpp
// 
// DESCRIPTION:
//
// REVISION:
//  [3/6/2018 nbale]
//=============================================================================
#include "nestedsum_test.h"

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

    error += exmain();
    error += bmmain();
    error += tsmain();

    cout << "Test End with error = " << error << endl;
    system("pause");
    return error;
}
