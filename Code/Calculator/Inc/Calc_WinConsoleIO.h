//=============================================================================
// FILENAME : Calc_VCWin.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/3/2018 nbale]
//=============================================================================
#pragma once

#ifndef _CALC_WINCONSOLEIO_H_
#define _CALC_WINCONSOLEIO_H_


#include "Calc_Core.h"
#include <iostream>
#include <windows.h>

__BEGIN_NAMESPACE

//https://gist.github.com/takashyx/937f3a794ad36cd98ec3

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

public:
    Cout2VisualStudioDebugOutput() 
    {
        default_stream = std::cout.rdbuf(&dbgstream);
    }

    ~Cout2VisualStudioDebugOutput() 
    {
        std::cout.rdbuf(default_stream);
    }
};

__END_NAMESPACE

#endif//#ifdef _CALC_WINCONSOLEIO_H_

//=============================================================================
// END OF FILE
//=============================================================================

