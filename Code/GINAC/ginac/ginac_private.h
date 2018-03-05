//=============================================================================
// FILENAME : ginac_private.h
// 
// DESCRIPTION:
//
// REVISION:
//  [3/4/2018 nbale]
//=============================================================================
#pragma once

//total header

#ifndef _GINAC_PRIVATE_H_
#define _GINAC_PRIVATE_H_

//#include <cstddef> // for size_t
//#include <typeinfo> // for typeid
//#include <iterator>
//#include <map>
//#include <set>
//#include <list>
//#include <vector>
//#include <algorithm>
//#include <utility>
//#include <iomanip>
//#include <iostream>
//#include <stdexcept>
//#include <cstddef> // for size_t
//#include <functional>
//#include <iosfwd>
//#include <memory>
//#include <cstdint>
//#include <string>
//#include <stack>
//#include <cstring>

#include "cln_public.h"

#define GINAC_API  __declspec(dllexport)

#include "config.h"
#include "compiler.h"
#include "flags.h"
#include "assertion.h"
#include "class_info.h"
#include "print.h"
#include "registrar.h"
#include "ptr.h"
#include "basic.h"
#include "ex.h"
#include "archive.h"
#include "numeric.h"
#include "utils.h"
#include "constant.h"
#include "container.h"
#include "hash_seed.h"

#endif //#ifndef _GINAC_PRIVATE_H_

//=============================================================================
// END OF FILE
//=============================================================================

