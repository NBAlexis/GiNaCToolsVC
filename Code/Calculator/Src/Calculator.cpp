#include "Calculator_Pch.h"

using namespace std;

void
testfoo(mpz_t result, const mpz_t param, unsigned long n)
{
    unsigned long i;
    mpz_mul_ui(result, param, n);
    for (i = 1; i < n; i++)
        mpz_add_ui(result, result, i * 7);
}

const cln::cl_I fibonacci(int n)
{
    // Need a precision of ((1+sqrt(5))/2)^-n.
    cln::float_format_t prec = cln::float_format((int)(0.208987641*n + 5));
    cln::cl_R sqrt5 = sqrt(cl_float(5, prec));
    cln::cl_R phi = (1 + sqrt5) / 2;
    return cln::round1(cln::expt(phi, n) / sqrt5);
}

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{
    Cout2VisualStudioDebugOutput c2v;
    OutputDebugStringA("release?...");

    mpz_t r, n;
    mpz_init(r);
    mpz_init_set_str(n, "123456", 0);
    testfoo(r, n, 20L);
    char* testres = new char[128];
    gmp_snprintf(testres, 128, "%Zd\n", r);
    //TCHAR * tc = new TCHAR[128];
    //for (int i = 0; i < 128; ++i)
    //{
    //    tc[i] = SCAST(TCHAR, testres[i]);
    //}

    cout << "Hello word" << endl;
    cout << testres << endl;
    cout << "==============" << endl;
    //appTrace(_T("Hello Word\n"));
    //appTrace(_T("%s\n"), tc);
    //appTrace(_T("=============cln\n"));

    cout << "Something?" << endl;
    for (int i = 0; i < 301; ++i)
    {
        cln::cl_I fib = fibonacci(i);
        cout << "fibonacci " << i << " = " << fib << endl;
        
    }
    cout << "Something End?" << endl;

    appTrace(_T("=============End\n"));

    //appSafeDelete(testres);
    //appSafeDelete(tc);
    //system("pause");

    GiNaC::symbol x("x"), y("y");
    GiNaC::ex poly;

    //ex testex1(1);
    //ex testpow1 = pow(x, testex1);
    //ex testpow2 = pow(x, 1);
    //ex testex12(1);
    //ex testpow3 = pow(x, 1);
    //poly += factorial(0 + 16)*pow(x, 0)*pow(y, 2 - 0);
    //poly += factorial(1 + 16)*pow(x, 1)*pow(y, 2 - 1);
    //poly += factorial(2 + 16)*pow(x, 2)*pow(y, 2 - 2);
    for (int i = 0; i < 3; ++i)
        poly += GiNaC::factorial(i + 16)*pow(x, i)*pow(y, 2 - i);
    cout << poly << endl;

    cout << "cln factorial 16 =" << cln::factorial(16) << endl;
    cout << "ginac factorial 16 =" << GiNaC::factorial(16) << endl;

    GiNaC::symbol xx("x");
    GiNaC::ex t1 = (pow(xx, 2) + 2 * xx + 1) / (xx + 1);
    GiNaC::ex t2 = (pow(sin(xx), 2) + 2 * sin(xx) + 1) / (sin(xx) + 1);
    std::cout << "t1 is " << t1.normal() << std::endl;
    std::cout << "t2 is " << t2.normal() << std::endl;

    cout << "================================End=========" << endl;

    return 0;
}
