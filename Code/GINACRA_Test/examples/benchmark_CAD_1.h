/*
 * GiNaCRA - GiNaC Real Algebra package
 * Copyright (C) 2010-2012  Ulrich Loup, Joachim Redies, Sebastian Junges
 *
 * This file is part of GiNaCRA.
 *
 * GiNaCRA is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GiNaCRA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GiNaCRA.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


/**
 * @file benchmark_CAD_1.cpp
 *
 * Example file for testing the GiNaC Real Algebra package CAD feature with
 * <ul>
 * <li> the computer algebra system Reduce (http://www.reduce-algebra.com/), and</li>
 * <li> the tool QEPCAD (http://www.usna.edu/Users/cs/qepcad/QEPCAD.html).</li>
 * </ul>
 *
 * @see Examples taken from:

 * @author Ulrich Loup
 * @author
 * @since 2012-04-11
 * @version 2012-04-11
 */

//#include <ctime>
//#include <iostream>
//#include <pthread.h>
//#include <signal.h>

using namespace std;

#include "ginacra_test.h"

using namespace GiNaC;
using namespace GiNaCRA;

const string VERSION = "2012-04-11";
const string SUPPORT = "Ulrich Loup <loup@cs.rwth-aachen.de>";
/// command for Singular
const string cmdQepcad = "qepcad";
/// command for Reduce
const string cmdReduce = "redcsl";
/// timeout for all competitors
const string TIMEOUT     = "10";
const int    TIMEOUT_INT = 10;

// tools

/// compilation of tools to test
void testTools();
/// run current benchmark with ginacra
void testGinacra();
/// run current benchmark with qepcad
void testQepcad();
/// run current benchmark with reduce
void testReduce();

// benchmarks

/// benchmark function type
typedef void (*BenchFunc)();
/// switch global variables to this benchmark @see [1] Runge-Kutta example 1
void benchmarkHairerRK1();
/// switch global variables to this benchmark @see [1] Runge-Kutta example 2
void benchmarkHairerRK2();
/// switch global variables to this benchmark @see [1] Runge-Kutta example 5
void benchmarkButcherRK1();
/// switch global variables to this benchmark @see [1] Laurent series example 1
void benchmarkKatsuraLS1();
/// switch global variables to this benchmark @see [1] Laurent series example 2
void benchmarkKatsuraLS2();
/// switch global variables to this benchmark @see [1] Laurent series example 3
void benchmarkKatsuraLS3();
/// switch global variables to this benchmark @see [1] Laurent series example 4
void benchmarkKatsuraLS4();
/// switch global variables to this benchmark @see [1] Laurent series example 5
void benchmarkKatsuraLS5();

// auxiliary

/// print header for current benchmark and given tool name @param name tool name
void printTestHeader( const string& name );
/// print footer for current benchmark and given tool name @param name tool name
void printTestFooter( const string& name, double t );

// global variables

/// the list of variables for the current benchmark
list<symbol> variables;
/// the list of polynomials for the current benchmark
lst polynomials;
/// latex table of results to be filled during the benchmarks. For each benchmark we have a row using the columns "benchmark name" | "number of vars" | "number of polys" | max degree" | "ginacra time" | "singular time" | "reduce time"
string latexTable[8][7];
/// global benchmark count
unsigned benchmarkCount = 0;
/// global index of current tool, ranging from 0 to the overall number of tools to be tested
unsigned toolIndex = 0;

/**
 * Main program.
 */
int benchmark_CAD_1main()
{
    MultivariatePolynomialSettings::InitializeGiNaCRAMultivariateMR();
    //    VariableListPool::ensureNrVariables( 19 );

    cout << endl;
    cout << " Example file for testing the GiNaC Real Algebra package CAD feature." << endl;
    cout << " Version " << VERSION << endl;
    cout << " Support: " << SUPPORT << endl << endl;
    cout << " Required executables: " << cmdSingular << ", " << cmdReduce << endl << endl;
    cout << " Reference for test sets:" << endl << "[1] ." << endl;
    cout << "Benchmarking settings (hardcoded)" << endl;
    cout << "---------------------------------------------------------- Go, go, go! ----------------------------------------------------------"
         << endl;

    // gathering compilation of benchmarks
    list<BenchFunc> benchmarks = list<BenchFunc>();
    benchmarks.push_back( &benchmarkHairerRK1 );
    benchmarks.push_back( &benchmarkHairerRK2 );
    //    benchmarks.push_back( &benchmarkButcherRK1 );
    benchmarks.push_back( &benchmarkKatsuraLS1 );
    benchmarks.push_back( &benchmarkKatsuraLS2 );
    benchmarks.push_back( &benchmarkKatsuraLS3 );
    benchmarks.push_back( &benchmarkKatsuraLS4 );
    benchmarks.push_back( &benchmarkKatsuraLS5 );

    // run benchmarks
    for( list<BenchFunc>::const_iterator f = benchmarks.begin(); f != benchmarks.end(); ++f )
    {
        cout << "Switching to example set " << benchmarkCount << "." << endl;
        (*f)();
        testTools();
        ++benchmarkCount;
    }
    cout << "---------------------------------------------------------- We're done. ----------------------------------------------------------"
         << endl;
    // print latex result table
    cout << "Print LaTeX table representation of the results:" << endl << endl;
    cout << "\\begin{tabular}{lllll}" << endl;
    for( unsigned b = 0; b != benchmarkCount; ++b )
    {    // benchmarks
        cout << latexTable[b][0];
        for( unsigned c = 1; c != 7; ++c )
            cout << " & $" << latexTable[b][c] << "$";
        cout << "\\\\" << endl;
    }
    cout << "\\end{tabular}" << endl;
    return 0;
}

///////////
// Tools //
///////////

void testTools()
{
    ostringstream intStream;
    intStream << variables.size();
    latexTable[benchmarkCount][1] = intStream.str();    // sets benchmark number of vars
    intStream.flush();
    intStream << polynomials.nops();
    latexTable[benchmarkCount][2] = intStream.str();    // sets benchmark number of vars
    toolIndex                     = 0;
    testGinacra();
    ++toolIndex;
    testQepcad();
    ++toolIndex;
    testReduce();
}

void testGinacra()
{
    printTestHeader( "GiNaCRA" );
    // prepare input
    UnivariatePolynomialSet input = UnivariatePolynomialSet();
    for( lst::const_iterator i = polynomials.begin(); i != polynomials.end(); ++i )
        input.insert( UnivariatePolynomial( *i, ));
    // solve & output
    time_t t = clock();
    //        int             pid;
    //        if( (pid = fork()) < 0 )
    //            cout << "Error\n";
    //        else if( pid == 0 )
    //        {    // child
    Groebner g = Groebner( input.begin(), input.end() );
    g.solve();
    g.reduce();
    g.print();
    //        }
    //        else
    //        {    // parent=mother || father
    //            if( sleep( TIMEOUT_INT ) != 0 )
    //                return;
    //            kill( pid, SIGKILL );
    //
    //        }
    t = clock() - t;
    cout << endl << endl;
    ostringstream doubleStream;
    doubleStream << t;
    latexTable[benchmarkCount][4] = doubleStream.str();    // sets benchmark time
    printTestFooter( "GiNaCRA", t );
}

void testSingular()
{
    printTestHeader( "Singular" );
    // prepare input
    list<symbol>::const_iterator v = variables.begin();
    string call = "intvec opt = option(get);option(prot);ring r = real,(" + v->get_name();
    ++v;
    for( ; v != variables.end(); ++v )
        call += "," + v->get_name();
    lst::const_iterator p = polynomials.begin();
    ostringstream       sStream;
    sStream << *p;
    string s = sStream.str();
    size_t pos;
    while( (pos = s.find( "^" )) != string::npos )
        s.replace( pos, 1, "**" );    // 1 = length( ^ )
    call += ")," + monomialOrderingSingular + "; ideal i=" + s;
    for( ; p != polynomials.end(); ++p )
    {
        ostringstream s;
        s << *p;
        call += "," + s.str();
    }
    call += "; groebner(i); quit;";
    call = "sleep " + TIMEOUT + " && killall " + cmdSingular + " & " + cmdSingular + " -q -c \"" + call + "\"";
    // solve & output
    cout << call << endl;
    double t = clock();
    system( call.c_str() );
    t = clock() - t;
    cout << endl;
    ostringstream doubleStream;
    doubleStream << t;
    latexTable[benchmarkCount][5] = doubleStream.str();    // sets benchmark time
    printTestFooter( "Singular", t );
}

void testReduce()
{
    printTestHeader( "Reduce" );
    // prepare input
    list<symbol>::const_iterator v = variables.begin();
    string call = "load_package \\\"groebner\\\";on groebfullreduction;torder({" + v->get_name();
    ++v;
    for( ; v != variables.end(); ++v )
        call += "," + v->get_name();
    lst::const_iterator p = polynomials.begin();
    ostringstream       sStream;
    sStream << *p;
    string s = sStream.str();
    size_t pos;
    while( (pos = s.find( "^" )) != string::npos )
        s.replace( pos, 1, "**" );    // 1 = length( ^ )
    call += "}," + monomialOrderingReduce + ");ideal:={" + s;
    for( ; p != polynomials.end(); ++p )
    {
        ostringstream s;
        s << *p;
        call += "," + s.str();
    }
    call += "}$ groebner(ideal); exit;";
    call = "sleep " + TIMEOUT + " && killall " + cmdReduce + " & echo \"" + call + "\" | " + cmdReduce + " -q -w";
    // solve & output
    cout << call << endl;
    double t = clock();
    system( call.c_str() );
    t = clock() - t;
    cout << endl;
    ostringstream doubleStream;
    doubleStream << t;
    latexTable[benchmarkCount][6] = doubleStream.str();    // sets benchmark time
    printTestFooter( "Reduce", t );
}

void printTestHeader( const string& name )
{
    cout << "**** " << name << " ****" << endl;
    cout << name << " Example set of polynomials: " << endl;
    for( lst::const_iterator p = polynomials.begin(); p != polynomials.end(); ++p )
        cout << "  " << *p << endl;
    cout << endl << "Starting computation..." << endl;
}

void printTestFooter( const string& name, double t )
{
    cout << name << " finished the computation." << endl;
    cout << "**** The test took " << t / (CLOCKS_PER_SEC / 1000.0) << " msec ****" << endl << endl;
}

////////////////
// Benchmarks //
////////////////

void benchmarkHairerRK1()
{
    latexTable[benchmarkCount][0] = "HairerRK1";    // sets benchmark name
    latexTable[benchmarkCount][3] = "3";    // sets benchmark max input degree
    unsigned i = 0;
    symbol C2  = VariableListPool::getVariableSymbol( i++ );
    symbol C3  = VariableListPool::getVariableSymbol( i++ );
    symbol B3  = VariableListPool::getVariableSymbol( i++ );
    symbol B2  = VariableListPool::getVariableSymbol( i++ );
    symbol B1  = VariableListPool::getVariableSymbol( i++ );
    symbol A21 = VariableListPool::getVariableSymbol( i++ );
    symbol A32 = VariableListPool::getVariableSymbol( i++ );
    symbol A31 = VariableListPool::getVariableSymbol( i++ );
    variables  = list<symbol>();
    variables.push_back( C2 );
    variables.push_back( C3 );
    variables.push_back( B3 );
    variables.push_back( B2 );
    variables.push_back( B1 );
    variables.push_back( A21 );
    variables.push_back( A32 );
    variables.push_back( A31 );
    polynomials = lst();
    polynomials.append( C2 - A21 );
    polynomials.append( C3 - A31 - A32 );
    polynomials.append( B1 + B2 + B3 - 1 );
    polynomials.append( B2 * C2 + B3 * C3 - numeric( 1, 2 ));
    polynomials.append( B2 * pow( C2, 2 ) + B3 * pow( C3, 2 ) - numeric( 1, 3 ));
    polynomials.append( B3 * A32 * C2 - numeric( 1, 6 ));
}

void benchmarkHairerRK2()
{
    latexTable[benchmarkCount][0] = "HairerRK2";    // sets benchmark name
    latexTable[benchmarkCount][0] = "4";    // sets benchmark max degree
    unsigned i = 0;
    symbol C2  = VariableListPool::getVariableSymbol( i++ );
    symbol C3  = VariableListPool::getVariableSymbol( i++ );
    symbol C4  = VariableListPool::getVariableSymbol( i++ );
    symbol B4  = VariableListPool::getVariableSymbol( i++ );
    symbol B3  = VariableListPool::getVariableSymbol( i++ );
    symbol B2  = VariableListPool::getVariableSymbol( i++ );
    symbol B1  = VariableListPool::getVariableSymbol( i++ );
    symbol A21 = VariableListPool::getVariableSymbol( i++ );
    symbol A32 = VariableListPool::getVariableSymbol( i++ );
    symbol A31 = VariableListPool::getVariableSymbol( i++ );
    symbol A41 = VariableListPool::getVariableSymbol( i++ );
    symbol A42 = VariableListPool::getVariableSymbol( i++ );
    symbol A43 = VariableListPool::getVariableSymbol( i++ );
    variables  = list<symbol>();
    variables.push_back( C2 );
    variables.push_back( C3 );
    variables.push_back( C4 );
    variables.push_back( B4 );
    variables.push_back( B3 );
    variables.push_back( B2 );
    variables.push_back( B1 );
    variables.push_back( A21 );
    variables.push_back( A32 );
    variables.push_back( A31 );
    variables.push_back( A41 );
    variables.push_back( A42 );
    variables.push_back( A43 );
    polynomials = lst();
    polynomials.append( B1 + B2 + B3 + B4 - 1 );
    polynomials.append( B2 * C2 + B3 * C3 + B4 * C4 - numeric( 1, 2 ));
    polynomials.append( B2 * pow( C2, 2 ) + B3 * pow( C3, 2 ) + B4 * pow( C4, 2 ) - numeric( 1, 3 ));
    polynomials.append( B3 * A32 * C2 + B4 * A42 * C2 + B4 * A43 * C3 - numeric( 1, 6 ));
    polynomials.append( B2 * pow( C2, 3 ) + pow( B3 * C3, 3 ) + B4 * pow( C4, 3 ) - numeric( 1, 4 ));
    polynomials.append( B3 - C3 * A32 * C2 + B4 * C4 * A42 * C2 + B4 * C4 * A43 * C3 - numeric( 1, 8 ));
    polynomials.append( B3 * A32 * pow( C2, 2 ) + B4 * A42 * pow( C2, 2 ) + B4 * A43 * pow( C3, 2 ) - numeric( 1, 12 ));
    polynomials.append( B4 * A43 * A32 * C2 - numeric( 1, 24 ));
    polynomials.append( C2 - A21 );
    polynomials.append( C3 - A31 - A32 );
    polynomials.append( C4 - A41 - A42 - A43 );
}

void benchmarkButcherRK1()
{
    latexTable[benchmarkCount][0] = "ButcherRK1";    // sets benchmark name
    latexTable[benchmarkCount][3] = "4";    // sets benchmark max input degree
    unsigned i = 0;
    symbol C2  = VariableListPool::getVariableSymbol( i++ );
    symbol C3  = VariableListPool::getVariableSymbol( i++ );
    symbol B   = VariableListPool::getVariableSymbol( i++ );
    symbol A   = VariableListPool::getVariableSymbol( i++ );
    symbol B3  = VariableListPool::getVariableSymbol( i++ );
    symbol B2  = VariableListPool::getVariableSymbol( i++ );
    symbol A32 = VariableListPool::getVariableSymbol( i++ );
    symbol B1  = VariableListPool::getVariableSymbol( i++ );
    variables  = list<symbol>();
    variables.push_back( C2 );
    variables.push_back( C3 );
    variables.push_back( B );
    variables.push_back( A );
    variables.push_back( B3 );
    variables.push_back( B2 );
    variables.push_back( A32 );
    variables.push_back( B1 );
    polynomials = lst();
    polynomials.append( B1 + B2 + B3 - (A + B) );
    polynomials.append( B2 * C2 + B3 * C3 - (numeric( 1, 2 ) + numeric( 1, 2 ) * B + pow( B, 2 ) - A * B) );
    polynomials.append( B2 * pow( C2, 2 ) + B3 * pow( C3, 2 )
                        - (A * (numeric( 1, 3 ) + pow( B, 2 )) - numeric( 4, 3 ) * B - pow( B, 2 ) - pow( B, 3 )));
    polynomials.append( B3 * A32 * C2
                        - (A * (numeric( 1, 6 ) + numeric( 1, 2 ) * B + pow( B, 2 )) - numeric( 2, 3 ) * B - pow( B, 2 ) - pow( B, 3 )));
    polynomials.append( B2 * pow( C2, 3 ) + B3 * pow( C3, 3 )
                        - (numeric( 1, 4 ) + numeric( 1, 4 ) * B + numeric( 5, 2 ) * pow( B, 2 ) + numeric( 3, 2 ) * pow( B, 3 ) + pow( B, 4 )
                           - A * (B + pow( B, 3 ))));
    polynomials.append( B3 * C3 * A32 * C2
                        - (numeric( 1, 8 ) + numeric( 3, 8 ) * B + numeric( 7, 4 ) * pow( B, 2 ) + numeric( 3, 2 ) * pow( B, 3 ) + pow( B, 4 )
                           - A * (numeric( 1, 2 ) * B + numeric( 1, 2 ) * pow( B, 2 ) + pow( B, 3 ))));
    polynomials.append( B3 * A32 * pow( C2, 2 )
                        - (numeric( 1, 12 ) + numeric( 1, 12 ) * B + numeric( 7, 6 ) * pow( B, 2 ) + numeric( 3, 2 ) * pow( B, 3 ) + pow( B, 4 )
                           - A * (numeric( 2, 3 ) * B + pow( B, 2 ) + pow( B, 3 ))));
    polynomials.append( (numeric( 1, 24 ) + numeric( 7, 24 ) * B + numeric( 13, 12 ) * pow( B, 2 ) + numeric( 3, 2 ) * pow( B, 3 ) + pow( B, 4 )
                         - A * (numeric( 1, 3 ) * B + pow( B, 2 ) + pow( B, 3 ))));
}

void benchmarkKatsuraLS1()
{
    latexTable[benchmarkCount][0] = "KatsuraLS1";    // sets benchmark name
    latexTable[benchmarkCount][3] = "2";    // sets benchmark max input degree
    unsigned i = 0;
    symbol U0 = VariableListPool::getVariableSymbol( i++ );
    symbol U1 = VariableListPool::getVariableSymbol( i++ );
    variables = list<symbol>();
    variables.push_back( U0 );
    variables.push_back( U1 );
    polynomials = lst();
    polynomials.append( pow( U0, 2 ) - U0 + 2 * pow( U1, 2 ));
    polynomials.append( U0 + 2 * U1 - 1 );
}

void benchmarkKatsuraLS2()
{
    latexTable[benchmarkCount][0] = "KatsuraLS2";    // sets benchmark name
    latexTable[benchmarkCount][3] = "2";    // sets benchmark max input degree
    unsigned i = 0;
    symbol U0 = VariableListPool::getVariableSymbol( i++ );
    symbol U1 = VariableListPool::getVariableSymbol( i++ );
    symbol U2 = VariableListPool::getVariableSymbol( i++ );
    variables = list<symbol>();
    variables.push_back( U0 );
    variables.push_back( U1 );
    variables.push_back( U2 );
    polynomials = lst();
    polynomials.append( pow( U0, 2 ) - U0 + 2 * pow( U1, 2 ) + 2 * pow( U2, 2 ));
    polynomials.append( 2 * U0 * U1 + 2 * U1 * U2 - U1 );
    polynomials.append( U0 + 2 * U1 + 2 * U2 - 1 );
}

void benchmarkKatsuraLS3()
{
    latexTable[benchmarkCount][0] = "KatsuraLS3";    // sets benchmark name
    latexTable[benchmarkCount][3] = "2";    // sets benchmark max input degree
    unsigned i = 0;
    symbol U0 = VariableListPool::getVariableSymbol( i++ );
    symbol U1 = VariableListPool::getVariableSymbol( i++ );
    symbol U2 = VariableListPool::getVariableSymbol( i++ );
    symbol U3 = VariableListPool::getVariableSymbol( i++ );
    variables = list<symbol>();
    variables.push_back( U0 );
    variables.push_back( U1 );
    variables.push_back( U2 );
    variables.push_back( U3 );
    polynomials = lst();
    polynomials.append( pow( U0, 2 ) - U0 + 2 * pow( U1, 2 ) + 2 * pow( U2, 2 ) + 2 * pow( U3, 2 ));
    polynomials.append( 2 * U0 * U1 + 2 * U1 * U2 + 2 * U2 * U3 - U1 );
    polynomials.append( 2 * U0 * U2 + pow( U1, 2 ) + 2 * U1 * U3 - U2 );
    polynomials.append( U0 + 2 * U1 + 2 * U2 + 2 * U3 - 1 );
}

void benchmarkKatsuraLS4()
{
    latexTable[benchmarkCount][0] = "KatsuraLS4";    // sets benchmark name
    latexTable[benchmarkCount][3] = "2";    // sets benchmark max input degree
    unsigned i = 0;
    symbol U0 = VariableListPool::getVariableSymbol( i++ );
    symbol U1 = VariableListPool::getVariableSymbol( i++ );
    symbol U2 = VariableListPool::getVariableSymbol( i++ );
    symbol U3 = VariableListPool::getVariableSymbol( i++ );
    symbol U4 = VariableListPool::getVariableSymbol( i++ );
    variables = list<symbol>();
    variables.push_back( U0 );
    variables.push_back( U1 );
    variables.push_back( U2 );
    variables.push_back( U3 );
    variables.push_back( U4 );
    polynomials = lst();
    polynomials.append( pow( U0, 2 ) - U0 + 2 * pow( U1, 2 ) + 2 * pow( U2, 2 ) + 2 * pow( U3, 2 ) + 2 * pow( U4, 2 ));
    polynomials.append( 2 * U0 * U1 + 2 * U1 * U2 + 2 * U2 * U3 + 2 * U3 * U4 - U1 );
    polynomials.append( 2 * U0 * U2 + pow( U1, 2 ) + 2 * U1 * U3 + 2 * U2 * U4 - U2 );
    polynomials.append( 2 * U0 * U3 + 2 * U1 * U2 + 2 * U1 * U4 - U3 );
    polynomials.append( U0 + 2 * U1 + 2 * U2 + 2 * U3 + 2 * U4 - 1 );
}

void benchmarkKatsuraLS5()
{
    latexTable[benchmarkCount][0] = "KatsuraLS5";    // sets benchmark name
    latexTable[benchmarkCount][3] = "2";    // sets benchmark max input degree
    unsigned i = 0;
    symbol U0 = VariableListPool::getVariableSymbol( i++ );
    symbol U1 = VariableListPool::getVariableSymbol( i++ );
    symbol U2 = VariableListPool::getVariableSymbol( i++ );
    symbol U3 = VariableListPool::getVariableSymbol( i++ );
    symbol U4 = VariableListPool::getVariableSymbol( i++ );
    symbol U5 = VariableListPool::getVariableSymbol( i++ );
    variables = list<symbol>();
    variables.push_back( U0 );
    variables.push_back( U1 );
    variables.push_back( U2 );
    variables.push_back( U3 );
    variables.push_back( U4 );
    variables.push_back( U5 );
    polynomials = lst();
    polynomials.append( pow( U0, 2 ) - U0 + 2 * pow( U1, 2 ) + 2 * pow( U2, 2 ) + 2 * pow( U3, 2 ) + 2 * pow( U4, 2 ) + 2 * pow( U5, 2 ));
    polynomials.append( 2 * U0 * U1 + 2 * U1 * U2 + 2 * U2 * U3 + 2 * U3 * U4 + 2 * U4 * U5 - U1 );
    polynomials.append( 2 * U0 * U2 + pow( U1, 2 ) + 2 * U1 * U3 + 2 * U2 * U4 + 2 * U3 * U5 - U2 );
    polynomials.append( 2 * U0 * U3 + 2 * U1 * U2 + 2 * U1 * U4 + 2 * U2 * U5 - U3 );
    polynomials.append( 2 * U0 * U4 + 2 * U1 * U3 + 2 * U1 * U5 + pow( U2, 2 ) - U4 );
    polynomials.append( U0 + 2 * U1 + 2 * U2 + 2 * U3 + 2 * U4 + 2 * U5 - 1 );
}

///////////////////////
// Auxiliary methods //
///////////////////////











