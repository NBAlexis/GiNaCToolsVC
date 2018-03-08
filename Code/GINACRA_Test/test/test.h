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
 * Test program for several functionalities of the GiNaC Real Algebra package.
 * @author Ulrich Loup
 * @since 2010-07-28
 * @version 2011-07-15
 */

#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "ginacra.h"

using namespace GiNaCRA;
using namespace std;

//////////////////
// Test program //
//////////////////

int testmain( int argc, char** argv )
{
    GiNaCRA::MultivariatePolynomialSettings::InitializeGiNaCRAMultivariateMR();
    // Get the top level suite from the registry
    CppUnit::Test*              suite_all        = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    CppUnit::Test*              suite_univariate = CppUnit::TestFactoryRegistry::getRegistry( CPPUNITSettings::TESTSUITE_UNIVARIATE ).makeTest();
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( suite_all );
    runner.addTest( suite_univariate );

    // Change the default outputter to a compiler error format outputter
    runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(), std::cerr ));

    // Run the tests.
    bool wasSucessful = runner.run();

    // Return error code 1 if the one of test failed.
    return !wasSucessful;
}
