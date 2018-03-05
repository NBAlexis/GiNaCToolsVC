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

    std::cout << std::endl;
    std::cout << "checking Csums" << std::endl;
    std::cout << std::endl;

    ex expr_start, expr_end;

    symbol x("x"), y("y"), z("z");
    symbol x0("x0", "x_0"), x1("x1", "x_1"), x2("x2", "x_2"), x3("x3", "x_3");
    symbol y0("y0", "y_0"), y1("y1", "y_1"), y2("y2", "y_2"), y3("y3", "y_3");
    symbol m1("m1", "m_1"), m2("m2", "m_2"), m3("m3", "m_3");
    symbol i("i"), j("j"), n("n");
    letter l_x0_0(x0, 0);
    letter l_x0_1(x0, 1);
    letter l_x0_2(x0, 2);
    letter l_x0_3(x0, 3);
    letter l_x0bar_0(1 - x0, 0);
    letter l_x0bar_1(1 - x0, 1);

    expr_start = Csum(n, lst{ l_x0_0 });
    expr_end = create_Ssum(n, lst()) * (unit_letter((ex)0, n) - letter(1 - x0, 0, n))
        - unit_letter((ex)0, n) * convert_Csum_to_Ssum(expr_start);
    expr_end = nestedsums_helper_expand(expr_end);
    std::cout << "Test    " << 1 << " : " << expr_end << std::endl;
    if (expr_end != 0)
    {
        ++error;
    }

    cout << _unit_one_letter << endl;
    cout << l_x0bar_1 << endl;
    cout << x0 << endl;
    cout << unit_letter((ex)1) << endl;
    cout << ((ex)1) << endl;
    cout << basic_letter(1, 1, 0) << endl;

    cout << create_Ssum(n, lst{ _unit_one_letter }) << endl;
    cout << create_Ssum(n, lst{ l_x0bar_1 }) << endl;
    cout << convert_Csum_to_Ssum(expr_start) << endl;

    expr_start = Csum(n, lst{ l_x0_1 });
    expr_end = create_Ssum(n, lst{ _unit_one_letter }) - create_Ssum(n, lst{ l_x0bar_1 })
        - convert_Csum_to_Ssum(expr_start);
    expr_end = nestedsums_helper_expand(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    std::cout << "Test    " << 2 << " : " << expr_end << std::endl;
    if (expr_end != 0)
    {
        ++error;
    }

    expr_start = Csum(n, lst{ l_x0_2 });
    expr_end = create_Ssum(n, lst{ _unit_one_letter,_unit_one_letter })
        - create_Ssum(n, lst{ _unit_one_letter,l_x0bar_1 })
        - convert_Csum_to_Ssum(expr_start);
    expr_end = nestedsums_helper_expand(expr_end);
    std::cout << "Test    " << 3 << " : " << expr_end << std::endl;
    if (expr_end != 0)
    {
        ++error;
    }

    expr_start = Csum(n, lst{ l_x0_3 });
    expr_end = create_Ssum(n, lst{ _unit_one_letter,_unit_one_letter,_unit_one_letter })
        - create_Ssum(n, lst{ _unit_one_letter,_unit_one_letter,l_x0bar_1 })
        - convert_Csum_to_Ssum(expr_start);
    expr_end = nestedsums_helper_expand(expr_end);
    std::cout << "Test    " << 3 << " : " << expr_end << std::endl;
    if (expr_end != 0)
    {
        ++error;
    }

    //error += exmain();
    //error += bmmain();
    //error += tsmain();

    cout << "Test End with error = " << error << endl;
    system("pause");
    return error;
}
