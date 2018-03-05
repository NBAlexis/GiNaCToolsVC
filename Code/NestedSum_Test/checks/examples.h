// 
// written by Stefan Weinzierl
//

//#include <iostream>
//#include <stdexcept>
//
//#include "ginac/ginac.h"
//#include "nestedsums/nestedsums.h"


int exmain()
{

  using namespace GiNaC;
  using namespace nestedsums;

  std::cout << std::endl;
  std::cout << "examples for nestedsums" << std::endl;
  std::cout << std::endl;

  try{
    // definition of variables

    int order;

    symbol eps("eps","\\varepsilon");

    symbol a("a"), b("b"), c("c");

    symbol x("x"), y("y");

    // -------------------------------------------------
    // expansion of a hypergeometric function

    order = 4;

    // expands 2F1(a eps, b eps, 1 - c eps, x) in eps
    ex F21 = transcendental_fct_type_A(x,lst{a*eps,b*eps},lst{1-c*eps},
				       lst{1-c*eps},lst{a*eps,b*eps},
				       eps,order,expand_status::expansion_required);

    // some polishing
    F21 = convert_Zsums_to_standard_form(F21,lst{eps});

    std::cout << std::endl;
    std::cout << "Example: Expansion of a hypergeometric function:" <<std::endl;
    std::cout << std::endl;
    std::cout << "There are several output formats for multiple polylogs available." << std::endl;
    std::cout << "The default option is:" << std::endl;
    std::cout << std::endl;
    std::cout << " 2F1(a*eps, b*eps; 1 - c*eps; x)  =  " << std::endl;
    std::cout << "   " << F21 << " + O(eps^" << order << ")" << std::endl;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Setting the flag" << std::endl;
    std::cout << "  _print_format |= print_format::no_special_cases;" << std::endl;
    std::cout << "will print Nielsen polylogs and harmonic polylogs also in the Li-notation:" << std::endl;

    _print_format |= print_format::no_special_cases;

    std::cout << std::endl;
    std::cout << " 2F1(a*eps, b*eps; 1 - c*eps; x)  =  " << std::endl;
    std::cout << "   " << F21 << " + O(eps^" << order << ")" << std::endl;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Setting the flag" << std::endl;
    std::cout << "  _print_format |= print_format::no_reversed_order;" << std::endl;
    std::cout << "will not reverse the argument lists for multiple polylogs and multiple zeta values:" << std::endl;

    _print_format |= print_format::no_reversed_order;

    std::cout << std::endl;
    std::cout << " 2F1(a*eps, b*eps; 1 - c*eps; x)  =  " << std::endl;
    std::cout << "   " << F21 << " + O(eps^" << order << ")" << std::endl;
    std::cout << std::endl;

    // -------------------------------------------------
    // expansion of an Appell function of the second kind

    order = 2;
    _print_format = print_format::standard;

    // expands F2(1,1,eps;1+eps,1-eps;x,y) in eps
    ex F2 = transcendental_fct_type_D(x,y,lst{1},lst{1+eps},lst{eps},lst{1-eps},
				      lst{1},lst(),lst{1+eps,1-eps},lst{1,1,eps},
				      eps,order,expand_status::expansion_required);

    // some polishing
    F2 = convert_Zsums_to_standard_form(F2,lst{eps});

    std::cout << std::endl;
    std::cout << "Further example: Expansion of the second Appell function:" <<std::endl;
    std::cout << std::endl;
    std::cout << " F2( 1, 1, eps; 1+eps, 1-eps; x, y)  =  " << std::endl;
    std::cout << "   " << F2 << " + O(eps^" << order << ")" << std::endl;
    std::cout << std::endl;

  } catch (std::exception &e)
    {
      std::cout << "Exception : " << e.what() << std::endl;
    }

  std::cout << std::endl;
  std::cout << "end examples" << std::endl;
  std::cout << std::endl;

  return 0;
}




