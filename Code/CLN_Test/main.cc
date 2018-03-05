#include "mainheader.h"

#define DUMP(expr)  \
	fprint(cout, #expr" = "); fprint(cout, expr); fprint(cout, "\n");

class debugStreambuf : public std::streambuf
{
public:
    virtual int_type overflow(int_type c = EOF)
    {
        if (c != EOF)
        {
            const char buf[] = { c, '\0' };
            OutputDebugStringA(buf);
        }
        return c;
    }
};

class Cout2VisualStudioDebugOutput
{

    debugStreambuf dbgstream;
    std::streambuf *default_stream;
    std::streambuf *default_streamerr;

public:
    Cout2VisualStudioDebugOutput()
    {
        default_stream = std::cout.rdbuf(&dbgstream);
        default_streamerr = std::cerr.rdbuf(&dbgstream);
    }

    ~Cout2VisualStudioDebugOutput()
    {
        std::cout.rdbuf(default_stream);
        std::cerr.rdbuf(default_stream);
    }
};


int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{
    Cout2VisualStudioDebugOutput c2do;

    float start = gettime();
    std::cerr << "df0: " << cl_DF_0 << " df1: " << cl_DF_1 << " df-1: " << cl_DF_minus1 << endl;

	cl_F archimedes = pi((float_format_t)10000);
	fprint(cout, archimedes);
	fprint(cout, "\n");

	cl_FF a;
	cl_FF x1 = "-0.2173f0";
	cl_FF x2 = "5.5084f9";
	cl_FF y = "-1.19698f9";
	fprint(cout, "x1 = "); print_float_binary(cout,x1); fprint(cout, " = "); fprint(cout,x1); fprint(cout, "\n");
	fprint(cout, "x2 = "); print_float_binary(cout,x2); fprint(cout, " = "); fprint(cout,x2); fprint(cout, "\n");
	fprint(cout, "y = "); print_float_binary(cout,y); fprint(cout, " = "); fprint(cout,y); fprint(cout, "\n");
	cl_FF x = x1*x2;
	fprint(cout, "x1*x2 = "); print_float_binary(cout,x); fprint(cout, " = "); fprint(cout,x); fprint(cout, "\n");

	cl_I xx1 = 10;
	cl_I yy1 = ++xx1;
    xx1 *= cl_I(2);
    xx1++;
	fprint(cout, "xx1 = "); fprint(cout, xx1); fprint(cout, "\n");
	fprint(cout, "yy1 = "); fprint(cout, yy1); fprint(cout, "\n");

	cl_I aa = "77371252437321868671713407";
	cl_I w;
	bool squarep = isqrt(aa,&w);
	DUMP(squarep ? "true" : "false");
	DUMP(w);
	DUMP(expt_pos(w,2) <= aa ? "true" : "false");
	DUMP(aa < expt_pos(w+1,2) ? "true" : "false");

	cl_I m = "79228162513111556826425457664";
	cl_I aaa = "19787815858762768436681494528";
	cl_modint_ring R = find_modint_ring(m);
	cl_I b = R->retract(R->canonhom(aaa));
	cl_I c = mod(aaa,abs(m));
	DUMP(b);
	DUMP(c);
	DUMP(b==c ? "true" : "false");

    int examer = 0, examdone = 0;
    exammain(examer, examdone);
    cout << "Exam finish with error: " << examer << " passed: " << examdone << endl;

    cout << "Start test for 10 times" << endl;

#if DEBUG
    testmain(100);
#else
    testmain(10000);
#endif

    cout << "Time: " << (gettime() - start) << "s" << endl;
    return 0;
}
