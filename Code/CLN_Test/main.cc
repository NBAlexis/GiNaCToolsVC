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

static const WORD MAX_CONSOLE_LINES = 1024;

inline void RedirectIOToConsole() {

    //Create a console for this application
    AllocConsole();

    // Get STDOUT handle
    HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
    FILE *COutputHandle = _fdopen(SystemOutput, "w");

    // Get STDERR handle
    HANDLE ConsoleError = GetStdHandle(STD_ERROR_HANDLE);
    int SystemError = _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
    FILE *CErrorHandle = _fdopen(SystemError, "w");

    // Get STDIN handle
    HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
    int SystemInput = _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
    FILE *CInputHandle = _fdopen(SystemInput, "r");

    //make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
    std::ios_base::sync_with_stdio(true);

    // Redirect the CRT standard input, output, and error handles to the console
    freopen_s(&CInputHandle, "CONIN$", "r", stdin);
    freopen_s(&COutputHandle, "CONOUT$", "w", stdout);
    freopen_s(&CErrorHandle, "CONOUT$", "w", stderr);

    //Clear the error state for each of the C++ standard stream objects. We need to do this, as
    //attempts to access the standard streams before they refer to a valid target will cause the
    //iostream objects to enter an error state. In versions of Visual Studio after 2005, this seems
    //to always occur during startup regardless of whether anything has been read from or written to
    //the console or not.
    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();

}

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{
    //Cout2VisualStudioDebugOutput c2do;
    RedirectIOToConsole();

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

    cout << "==============================================================" << endl;
    cout << "========================= Exam Start =========================" << endl;
    cout << "==============================================================" << endl;

    int examer = 0, examdone = 0;
    exammain(examer, examdone);
    cout << "Exam finish with error: " << examer << " passed: " << examdone << endl;
    int iHasError = 0;

#if DEBUG
    cout << "Start test for 100 times" << endl;
    iHasError = testmain(100);
#else
    cout << "Start test for 10000 times" << endl;
    iHasError = testmain(10000);
#endif

    cout << "Has Error:" << iHasError << endl;
    cout << "Time: " << (gettime() - start) << "s"  << endl;

    system("pause");
    return 0;
}
