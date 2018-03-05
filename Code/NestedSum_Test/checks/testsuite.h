// 
// written by Stefan Weinzierl
//

//#include <iostream>
//#include <stdexcept>
//#include <ctime>
//
//#include "ginac/ginac.h"
//#include "nestedsums/nestedsums.h"


int tsmain()
{

  using namespace GiNaC;
  using namespace nestedsums;

  std::cout << std::endl;
  std::cout << "nestedsums " << nestedsums::version_major 
                      << "." << nestedsums::version_minor
                      << "." << nestedsums::version_micro
	    << " testsuite, each test should return zero" << std::endl;
  std::cout << std::endl;

  try{

    // definition of variables

    time_t time_start;
    time_t time_end;

    int k;
    int order;
    int NMAX;

    symbol eps("eps","\\varepsilon");

    symbol a("a"), b("b"), c("c");

    symbol x("x"), y("y"), z("z");
    symbol x0("x0","x_0"), x1("x1","x_1"), x2("x2","x_2"), x3("x3","x_3");
    symbol y0("y0","y_0"), y1("y1","y_1"), y2("y2","y_2"), y3("y3","y_3");
    symbol m1("m1","m_1"), m2("m2","m_2"), m3("m3","m_3");
    symbol i("i"), j("j"), n("n");

    letter l1(x,m1);
    letter l2(y,m2);
    letter l3(z,m3);

    letter l_x0_0(x0,0);
    letter l_x0_1(x0,1);
    letter l_x0_2(x0,2);
    letter l_x0_3(x0,3);
    letter l_x0bar_0(1-x0,0);
    letter l_x0bar_1(1-x0,1);

    unit_letter u0(numeric(1));
    unit_letter u1(m1);
    unit_letter u2(m2);
    unit_letter u3(m3);

    Zsum Z0(n);
    Zsum Z1(n,lst{l1});
    Zsum Z2(n,lst{l1,l2});
    Zsum Z3(n,lst{l1,l2,l3});

    Ssum S0(n);
    Ssum S1(n,lst{l1});
    Ssum S2(n,lst{l1,l2});
    Ssum S3(n,lst{l1,l2,l3});

    Euler_Zagier_sum EZ0(n);
    Euler_Zagier_sum EZ1(n,lst{u1});
    Euler_Zagier_sum EZ2(n,lst{u1,u2});
    Euler_Zagier_sum EZ3(n,lst{u1,u2,u3});

    harmonic_sum HS0(n);
    harmonic_sum HS1(n,lst{u1});
    harmonic_sum HS2(n,lst{u1,u2});
    harmonic_sum HS3(n,lst{u1,u2,u3});

    multiple_polylog GL1(lst{l1});
    multiple_polylog GL2(lst{l1,l2});
    multiple_polylog GL3(lst{l1,l2,l3});

    multiple_zeta_value MZV1(lst{u1});
    multiple_zeta_value MZV2(lst{u1,u2});
    multiple_zeta_value MZV3(lst{u1,u2,u3});

    harmonic_polylog HL1(lst{l1});
    harmonic_polylog HL2(lst{l1,u2});
    harmonic_polylog HL3(lst{l1,u2,u3});

    nielsen_polylog NL1(lst{l1});
    nielsen_polylog NL2(lst{l1,u0});
    nielsen_polylog NL3(lst{l1,u0,u0});

    classical_polylog CL1(lst{l1});

    ex expr_start, expr_end;

    ex t1, t2, t3;

    ex ma,mb,mc,mb1,mb2,mc1,mc2,ma1,ma2;

    // -------------------------------------------
    
    std::cout << std::endl;
    std::cout << "checking comparison of basic letters" << std::endl;
    std::cout << std::endl;

    time(&time_start);
    expr_start = basic_letter(x,m1,3,n);
    expr_end = basic_letter(x,m1,3,n)
                 - expr_start;
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    std::cout << std::endl;
    std::cout << "checking comparison of lists of basic letters" << std::endl;
    std::cout << std::endl;

    time(&time_start);
    expr_start = lst{basic_letter(x,m1,3,n)};
    expr_end = lst{basic_letter(x,m1,3,n)}
                 - expr_start;
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    std::cout << std::endl;
    std::cout << "checking expand_tgamma" << std::endl;
    std::cout << std::endl;

    for (k=1;k<10;k++)
      {
	time(&time_start);
	ex expr_start = nestedsums_helper_expand_tgamma_fct(0,2,0,2,eps,k);
	time(&time_end);
	ex res = expr_start - 1;
	std::cout << "Test    " << k << " : " << res << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;
      }

    // -------------------------------------------
    std::cout << std::endl;
    std::cout << "checking ( 1 + eps Z_1(n) + eps^2 Z_11(n) + ... ) ( 1 - eps S_1(n) + eps^2 S_11(n) - ... ) = 1" << std::endl;
    std::cout << std::endl;

    ex Z0_temp = Zsum(n-1);

    for (k=1;k<6;k++)
      {
	time(&time_start);
	ex Z1_temp = create_ratio_of_tgamma(0,1,0,1,n,eps,k,expand_status::expansion_required);
	time(&time_end);
	ex res = Z1_temp - Z0_temp;
	std::cout << "Test    " << k << " : " << res << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;
      }

    // -------------------------------------------
    // conversion Ssum -> Zsum -> Ssum should yield back the original result 
    std::cout << std::endl;
    std::cout << "checking conversion between Ssums and Zsums" << std::endl;
    std::cout << std::endl;

    expr_start = S1+S2+S3;
    time(&time_start);
    expr_end = expr_start - Zsum_to_Ssum(Ssum_to_Zsum(expr_start));
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    expr_start = x+MZV3+y*z;
    time(&time_start);
    expr_end = expr_start - Ssum_to_Zsum(Zsum_to_Ssum(expr_start));
    time(&time_end);
    std::cout << "Test    " << 2 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    //  multiply S2*S3 and convert the result to Zsums
    //  and compare this to the case where S2 and S3 are
    //  first converted to Zsums and the multiplied.
    //
    // In the first case the multiplication for Ssums is used, 
    // in the second case the one for Zsums.

    std::cout << std::endl;
    std::cout << "checking multiplication/conversion" << std::endl;
    std::cout << std::endl;

    time(&time_start);
    expr_start = Ssum_to_Zsum(S2*S3);
    expr_end = nestedsums_helper_expand(expr_start - Ssum_to_Zsum(S2)*Ssum_to_Zsum(S3));
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    //  multiply Z2*Z3 and substitute n=10 in the end
    //  and compare this to the case where Z2 and Z3 are
    //  substituted first and ordinary multiplication is used.

    // takes a few seconds    
    std::cout << std::endl;
    std::cout << "checking multiplication/substitution" << std::endl;
    std::cout << std::endl;

    time(&time_start);
    expr_start = Z2*Z3;
    expr_start = expr_start.subs(n==10);
    t2 = Z2;
    t3 = Z3;
    expr_end = nestedsums_helper_expand(expr_start - t2.subs(n==10) * t3.subs(n==10) );
    // GiNaC does not simplify symbolic powers, therefore substitute some values
    expr_end = expr_end.subs(m1==3);
    expr_end = expr_end.subs(m2==4);
    expr_end = expr_end.subs(m3==5);
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    //
    // The formulae checked here are
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i x^i     =       1  - (1-x)^n
    //  - sum_{i=1}^n binom(n,i) (-1)^i x^i/i   =   S_1(n) - S(n;1;1-x)
    //  - sum_{i=1}^n binom(n,i) (-1)^i x^i/i^2 =  S_11(n) - S(n;1,1;1,1-x)
    //  - sum_{i=1}^n binom(n,i) (-1)^i x^i/i^3 = S_111(n) - S(n;1,1,1;1,1,1-x)

    std::cout << std::endl;
    std::cout << "checking Csums" << std::endl;
    std::cout << std::endl;

    time(&time_start);
    expr_start = Csum(n,lst{l_x0_0});
    expr_end = create_Ssum(n,lst()) * ( unit_letter((ex) 0,n) - letter(1-x0,0,n) ) 
                 - unit_letter((ex) 0,n) * convert_Csum_to_Ssum(expr_start);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = Csum(n,lst{l_x0_1});
    expr_end = create_Ssum(n,lst{_unit_one_letter}) - create_Ssum(n,lst{l_x0bar_1}) 
                 - convert_Csum_to_Ssum(expr_start);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 2 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = Csum(n,lst{l_x0_2});
    expr_end = create_Ssum(n,lst{_unit_one_letter,_unit_one_letter}) 
             - create_Ssum(n,lst{_unit_one_letter,l_x0bar_1}) 
                 - convert_Csum_to_Ssum(expr_start);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 3 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = Csum(n,lst{l_x0_3});
    expr_end = create_Ssum(n,lst{_unit_one_letter,_unit_one_letter,_unit_one_letter}) 
             - create_Ssum(n,lst{_unit_one_letter,_unit_one_letter,l_x0bar_1}) 
                 - convert_Csum_to_Ssum(expr_start);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 4 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    //
    // The formulae checked here are
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i sum_{i1=i+1}^{infty} (x^i1)/i1     =  S(infty;1;x) - 1/n + ((1-x)^n)/n

    std::cout << std::endl;
    std::cout << "checking Csums part 2" << std::endl;
    std::cout << std::endl;

    time(&time_start);
    expr_start = Csum(n,lst{_unit_zero_letter,l_x0_1});
    expr_end = Ssum(Infinity,lst{l_x0_1}) - letter((ex) 1,1,n) + letter(1-x0,1,n)
                 - convert_Csum_to_Ssum(expr_start);
    expr_end = expr_end*Ssum(n) ;
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    //
    // The formulae checked here are
    //
    // S(n;-1;x) = x/(1-x) + x^2/(1-x)^2 - x/(1-x) x^n - x^2/(1-x)^2 x^n - x/(1-x) n x^n
    //
    // S(n;-1,m2;x,y) = x/(1-x)^2 S(n;m2;xy) + 1/(1-x) S(n;m2-1;xy)
    //                   -(x/(1-x) + x^2/(1-x)^2) x^n S(n;m2;y) - x/(1-x) n x^n S(n;m2;y)
    //
    // S(Infinity;-1;x) = x/(1-x) + x^2/(1-x)^2 
    //
    // S(Infinity;-1,m2;x,y) = x/(1-x)^2 S(Infinity;m2;xy) + 1/(1-x) S(Infinity;m2-1;xy)
    //
    // S(n;-1;1) = 1/2 n^2 + 1/2 n
    //
    // S(n;0;x) = x/(1-x) - x/(1-x) x^n 
    //

    std::cout << std::endl;
    std::cout << "checking negative degrees" << std::endl;
    std::cout << std::endl;

    time(&time_start);
    expr_start = Ssum(n,lst{letter(x,-1)}).remove_negative_degrees();
    expr_end = create_Ssum(n,lst()) * ( x/(1-x) + pow(x,2)/pow(1-x,2) 
               - x/(1-x)*letter(x,0,n) - pow(x,2)/pow(1-x,2)*letter(x,0,n)
               -x/(1-x)*letter(x,-1,n) );
    expr_end = expr_end - expr_start;
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = Ssum(n,lst{letter(x,-1),letter(y,m2)}).remove_negative_degrees();
    expr_end = x/pow(1-x,2)*Ssum(n,lst{letter(x*y,m2)})
      +1/(1-x)*Ssum(n,lst{letter(x*y,m2-1)})
      -(x/(1-x)+pow(x,2)/pow(1-x,2))*letter(x,0,n)*Ssum(n,lst{letter(y,m2)})
      -x/(1-x)*letter(x,-1,n)*Ssum(n,lst{letter(y,m2)});
    expr_end = expr_end - expr_start;
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 2 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = Ssum(Infinity,lst{letter(x,-1)}).remove_negative_degrees();
    expr_end = ( x/(1-x) + pow(x,2)/pow(1-x,2) )*create_Ssum(Infinity,lst()) ;
    expr_end = expr_end - expr_start;
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 3 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = Ssum(Infinity,lst{letter(x,-1),letter(y,m2)}).remove_negative_degrees();
    expr_end = x/pow(1-x,2)*Ssum(Infinity,lst{letter(x*y,m2)})
      +1/(1-x)*Ssum(Infinity,lst{letter(x*y,m2-1)});
    expr_end = expr_end - expr_start;
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 4 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = Ssum(n,lst{letter((ex) 1,-1)}).remove_negative_degrees();
    expr_end = numeric(1,2) * unit_letter((ex) -2,n) * create_Ssum(n,lst())
      + numeric(1,2) * unit_letter((ex) -1,n) * create_Ssum(n,lst());
    expr_end = expr_end - expr_start;
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 5 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = Ssum(n,lst{letter(x,0)}).remove_negative_degrees();
    expr_end = S0 * (x/(1-x) - x/(1-x)*letter(x,0,n));
    expr_end = expr_end - expr_start;
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 6 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    //
    // The formulae checked here are
    //
    //  sum_{i=1}^infty x^i / i =  - ln(1-x)
    //
    //  sum_{i=1}^infty x^i / i Gamma(i+eps)/Gamma(i) = Gamma(1+eps) * ( -ln(1-x) + eps Li_11(1,x) + eps^2 Li_111(1,1,x) + ... )
    //
    //  Gamma(1-c*eps)/Gamma(a*eps)/Gamma(b*eps) * sum_{i=1}^infty x^i Gamma(i+a*eps)/Gamma(i+1-c*eps) Gamma(i+b*eps)/Gamma(i+1)
    //    =  a b eps^2 Li2(x) + a b c eps^3 Li3(x) + a b (a+b+c) eps^3 S_{1,2}(x)
    //
    //
    // letter must have the right index

    std::cout << std::endl;
    std::cout << "checking transcendental_sum_type_A" << std::endl;
    std::cout << std::endl;

    order = 3 ;

    time(&time_start);
    expr_start = create_transcendental_sum_type_A_and_set_gammas(Infinity,i,
       letter(x0,1,i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Zsum(i-1),
       eps,order,expand_status::expansion_required);
    expr_end = classical_polylog(lst{l_x0_1}) 
               - expr_start;
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_A_and_set_gammas(Infinity,i,
       letter(x0,1,i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,0)}),
       Zsum(i-1),
       eps,order,expand_status::expansion_required);
    expr_end =   classical_polylog(lst{l_x0_1}) 
               + eps * harmonic_polylog(lst{l_x0_1,_unit_one_letter})
               + pow(eps,2) * harmonic_polylog(lst{l_x0_1,_unit_one_letter,_unit_one_letter});
    expr_end = nestedsums_helper_expand( expr_end - expr_start);
    time(&time_end);
    std::cout << "Test    " << 2 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    order = 2;
    expr_start = create_transcendental_sum_type_A_and_set_gammas(Infinity,i,
       letter(x0,0,i), 
       list_of_tgamma(lst{ratio_of_tgamma(0,a,1,-c),ratio_of_tgamma(0,b,1,0) }), 
       Zsum(i-1),
       eps,order,expand_status::expansion_required);
    expr_start = a*eps*b*eps * expr_start;
    expr_start = nestedsums_helper_expand( expr_start);
    expr_end =   a*b*pow(eps,2) * classical_polylog(lst{l_x0_2})
      + a*b*c*pow(eps,3)  * classical_polylog(lst{l_x0_3})
      + a*b*(a+b+c)*pow(eps,3) * nielsen_polylog(lst{l_x0_2,_unit_one_letter})
               ;
    expr_end = nestedsums_helper_expand( expr_end - expr_start);

    time(&time_end);
    std::cout << "Test    " << 3 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    //
    // The formulae checked here are
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i x^i     =       1  - (1-x)^n
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i x^i/i   =       S_1(n)  - S(n;1;1-x)
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i x^i/i^2 =       S_11(n)  - S(n;1,1;1,1-x)
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i x^i/i^3 =       S_111(n)  - S(n;1,1,1;1,1,1-x)
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i S(i;1;x) =       1/n  - (1-x)^n/n
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i S(i;2;x) =       1/n S(n;1;1)  - 1/n S(n;1;1-x)
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i S(i;3;x) =       1/n S(n;1,1;1,1)  - 1/n S(n;1,1;1,1-x)
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i S(i;1,1;1,x) =       1/n^2 - (1-x)^n/n^2
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i S(i;1,1,1;1,1,x) =       1/n^3 - (1-x)^n/n^3
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i 1/i S(i;1;x) =       S(n;2;1) - S(n;2;1-x)
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i 1/i S(i;1,1;1,x) =       S(n;3;1) - S(n;3;1-x)
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i 1/i^3 =       S_111(n)  
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i S(i;3;1) =       1/n S(n;1,1;1,1)
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i S(i;1,1,1;1,1,1) =       1/n^3 
    //
    //  - sum_{i=1}^n binom(n,i) (-1)^i 1/i S(i;1,1;1,1) =       S(n;3;1) 

    std::cout << std::endl;
    std::cout << "checking transcendental_sum_type_C" << std::endl;
    std::cout << std::endl;

    order = 1 ;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       letter(x0,0,i),
       _empty_list_of_tgamma,
       Ssum(i),
       eps,order,expand_status::expansion_required);
    expr_end = create_Ssum(n,lst()) * ( unit_letter((ex) 0,n) - letter(1-x0,0,n));
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start * unit_letter((ex) 0,n);
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       letter(x0,1,i),
       _empty_list_of_tgamma,
       Ssum(i),
       eps,order,expand_status::expansion_required);
    expr_end = create_Ssum(n,lst{_unit_one_letter}) - create_Ssum(n,lst{l_x0bar_1});
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 2 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       letter(x0,2,i),
       _empty_list_of_tgamma,
       Ssum(i),
       eps,order,expand_status::expansion_required);
    expr_end = create_Ssum(n,lst{_unit_one_letter,_unit_one_letter}) 
                 - create_Ssum(n,lst{_unit_one_letter,l_x0bar_1});
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 3 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       letter(x0,3,i),
       _empty_list_of_tgamma,
       Ssum(i),
       eps,order,expand_status::expansion_required);
    expr_end = create_Ssum(n,lst{_unit_one_letter,_unit_one_letter,_unit_one_letter}) 
                 - create_Ssum(n,lst{_unit_one_letter,_unit_one_letter,l_x0bar_1});
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 4 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;


    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       unit_letter((ex) 0,i),
       _empty_list_of_tgamma,
       Ssum(i,lst{letter(x0,1)}),
       eps,order,expand_status::expansion_required);
    expr_end = create_Ssum(n,lst()) * (unit_letter((ex) 1,n) - letter(1-x0,1,n)) ;
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 5 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       unit_letter((ex) 0,i),
       _empty_list_of_tgamma,
       Ssum(i,lst{letter(x0,2)}),
       eps,order,expand_status::expansion_required);
    expr_end = unit_letter((ex) 1, n)
       * ( Ssum(n,lst{_unit_one_letter}) - Ssum(n,lst{l_x0bar_1}) );
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 6 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       unit_letter((ex) 0,i),
       _empty_list_of_tgamma,
       Ssum(i,lst{letter(x0,3)}),
       eps,order,expand_status::expansion_required);
    expr_end = unit_letter((ex) 1,n) 
       * ( Ssum(n,lst{_unit_one_letter,_unit_one_letter}) - Ssum(n,lst{_unit_one_letter,l_x0bar_1}) );
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 7 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       unit_letter((ex) 0,i),
       _empty_list_of_tgamma,
       Ssum(i,lst{_unit_one_letter,letter(x0,1)}),
       eps,order,expand_status::expansion_required);
    expr_end = create_Ssum(n,lst()) * (unit_letter((ex) 2,n) - letter(1-x0,2,n));
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 8 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       unit_letter((ex) 0,i),
       _empty_list_of_tgamma,
       Ssum(i,lst{_unit_one_letter,_unit_one_letter,letter(x0,1)}),
       eps,order,expand_status::expansion_required);
    expr_end = create_Ssum(n,lst()) * (unit_letter((ex) 3,n) - letter(1-x0,3,n));
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test    " << 9 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       unit_letter((ex) 1,i),
       _empty_list_of_tgamma,
       Ssum(i,lst{letter(x0,1)}),
       eps,order,expand_status::expansion_required);
    expr_end = Ssum(n,lst{unit_letter((ex) 2)}) - Ssum(n,lst{letter(1-x0,2)});
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test   " << 10 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       unit_letter((ex) 1,i),
       _empty_list_of_tgamma,
       Ssum(i,lst{_unit_one_letter,letter(x0,1)}),
       eps,order,expand_status::expansion_required);
    expr_end = Ssum(n,lst{unit_letter((ex) 3)}) - Ssum(n,lst{letter(1-x0,3)});
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test   " << 11 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       unit_letter((ex) 3,i),
       _empty_list_of_tgamma,
       Ssum(i),
       eps,order,expand_status::expansion_required);
    expr_end = create_Ssum(n,lst{_unit_one_letter,_unit_one_letter,_unit_one_letter});
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test   " << 12 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       unit_letter((ex) 0,i),
       _empty_list_of_tgamma,
       Ssum(i,lst{unit_letter((ex) 3)}),
       eps,order,expand_status::expansion_required);
    expr_end = unit_letter((ex) 1,n) 
       * ( Ssum(n,lst{_unit_one_letter,_unit_one_letter}) );
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test   " << 13 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       unit_letter((ex) 0,i),
       _empty_list_of_tgamma,
       Ssum(i,lst{_unit_one_letter,_unit_one_letter,_unit_one_letter}),
       eps,order,expand_status::expansion_required);
    expr_end = create_Ssum(n,lst()) * unit_letter((ex) 3,n) ;
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test   " << 14 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = transcendental_sum_type_C(n,i,
       unit_letter((ex) 1,i),
       _empty_list_of_tgamma,
       Ssum(i,lst{_unit_one_letter,_unit_one_letter}),
       eps,order,expand_status::expansion_required);
    expr_end = Ssum(n,lst{unit_letter((ex) 3)}) ;
    expr_end = Ssum_to_Zsum(expr_end);
    expr_end = expr_end - expr_start;
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    time(&time_end);
    std::cout << "Test   " << 15 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;


    // -------------------------------------------
    //
    // The formulae checked here are
    //
    //   C circ C S(n;2;x) 
    //
    //   C circ C S(n;5;x) 
    //
    //   C circ C S(n;1,1;x,1) 
    //
    //   C circ C S(n;1,1;x,y) 
    //
    //   C circ C (x^n)/n S(n;1;y) 
    //
    //   C circ C (z^n)/n S(n;1,1;x,y) 
    //
    //   C circ C (z^n)/n S(n;1,1;1,1) 
    //
    //   C circ C 1/n^3 S(n;2,2;x,1) 
    //
    //   C circ C (z^n)/n^3 S(n;2,2;x,y) 

    std::cout << std::endl;
    std::cout << "checking C circ C = id" << std::endl;
    std::cout << std::endl;

    order = 1 ;

    time(&time_start);
    expr_start = create_Ssum(n,lst{letter(x,2)});
    expr_end = transcendental_sum_type_C(i,n,
       letter((ex) 1,0,n),
       _empty_list_of_tgamma,
       expr_start,
       eps,order,expand_status::expansion_required);
    expr_end = Zsum_to_Ssum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    expr_end = transcendental_sum_type_C(n,i,
       letter((ex) 1,0,i),
       _empty_list_of_tgamma,
       expr_end,
       eps,order,expand_status::expansion_required);
    expr_end = Ssum_to_Zsum(expr_end - expr_start);
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end,expand_request::member_variables);
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_Ssum(n,lst{letter(x,5)});
    expr_end = transcendental_sum_type_C(i,n,
       letter((ex) 1,0,n),
       _empty_list_of_tgamma,
       expr_start,
       eps,order,expand_status::expansion_required);
    expr_end = Zsum_to_Ssum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    expr_end = transcendental_sum_type_C(n,i,
       letter((ex) 1,0,i),
       _empty_list_of_tgamma,
       expr_end,
       eps,order,expand_status::expansion_required);
    expr_end = Ssum_to_Zsum(expr_end - expr_start);
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end,expand_request::member_variables);
    time(&time_end);
    std::cout << "Test    " << 2 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_Ssum(n,lst{letter(x,1),letter((ex) 1,1)});
    expr_end = transcendental_sum_type_C(i,n,
       letter((ex) 1,0,n),
       _empty_list_of_tgamma,
       expr_start,
       eps,order,expand_status::expansion_required);
    expr_end = Zsum_to_Ssum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    expr_end = transcendental_sum_type_C(n,i,
       letter((ex) 1,0,i),
       _empty_list_of_tgamma,
       expr_end,
       eps,order,expand_status::expansion_required);
    expr_end = Ssum_to_Zsum(expr_end - expr_start);
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end,expand_request::member_variables);
    time(&time_end);
    std::cout << "Test    " << 3 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_Ssum(n,lst{letter(x,1),letter(y,1)});
    expr_end = transcendental_sum_type_C(i,n,
       letter((ex) 1,0,n),
       _empty_list_of_tgamma,
       expr_start,
       eps,order,expand_status::expansion_required);
    expr_end = Zsum_to_Ssum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    expr_end = transcendental_sum_type_C(n,i,
       letter((ex) 1,0,i),
       _empty_list_of_tgamma,
       expr_end,
       eps,order,expand_status::expansion_required);
    expr_end = Ssum_to_Zsum(expr_end - expr_start);
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end,expand_request::member_variables);
    time(&time_end);
    std::cout << "Test    " << 4 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_letter(x,1,n) * create_Ssum(n,lst{letter(y,1)});
    expr_end = transcendental_sum_type_C(i,n,
       letter((ex) 1,0,n),
       _empty_list_of_tgamma,
       expr_start,
       eps,order,expand_status::expansion_required);
    expr_end = Zsum_to_Ssum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    expr_end = transcendental_sum_type_C(n,i,
       letter((ex) 1,0,i),
       _empty_list_of_tgamma,
       expr_end,
       eps,order,expand_status::expansion_required);
    expr_end = Ssum_to_Zsum(expr_end - expr_start);
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end,expand_request::member_variables);
    time(&time_end);
    std::cout << "Test    " << 5 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_letter(z,1,n) * create_Ssum(n,lst{letter(x,1),letter(y,1)});
    expr_end = transcendental_sum_type_C(i,n,
       letter((ex) 1,0,n),
       _empty_list_of_tgamma,
       expr_start,
       eps,order,expand_status::expansion_required);
    expr_end = Zsum_to_Ssum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    expr_end = transcendental_sum_type_C(n,i,
       letter((ex) 1,0,i),
       _empty_list_of_tgamma,
       expr_end,
       eps,order,expand_status::expansion_required);
    expr_end = Ssum_to_Zsum(expr_end - expr_start);
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end,expand_request::member_variables);
    time(&time_end);
    std::cout << "Test    " << 6 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_letter(z,1,n) * create_Ssum(n,lst{letter((ex) 1,1),letter((ex) 1,1)});
    expr_end = transcendental_sum_type_C(i,n,
       letter((ex) 1,0,n),
       _empty_list_of_tgamma,
       expr_start,
       eps,order,expand_status::expansion_required);
    expr_end = Zsum_to_Ssum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    expr_end = transcendental_sum_type_C(n,i,
       letter((ex) 1,0,i),
       _empty_list_of_tgamma,
       expr_end,
       eps,order,expand_status::expansion_required);
    expr_end = Ssum_to_Zsum(expr_end - expr_start);
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end,expand_request::member_variables);
    time(&time_end);
    std::cout << "Test    " << 7 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // takes a few seconds
    time(&time_start);
    expr_start = create_letter(1,3,n) * create_Ssum(n,lst{letter(x,2),letter((ex) 1,2)});
    expr_end = transcendental_sum_type_C(i,n,
       letter((ex) 1,0,n),
       _empty_list_of_tgamma,
       expr_start,
       eps,order,expand_status::expansion_required);
    expr_end = Zsum_to_Ssum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end);
    expr_end = transcendental_sum_type_C(n,i,
       letter((ex) 1,0,i),
       _empty_list_of_tgamma,
       expr_end,
       eps,order,expand_status::expansion_required);
    expr_end = Ssum_to_Zsum(expr_end - expr_start);
    expr_end = remove_trivial_Zsum(expr_end);
    expr_end = nestedsums_helper_expand(expr_end,expand_request::member_variables);
    time(&time_end);
    std::cout << "Test    " << 8 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    //
    // The formulae checked here are
    //
    // sum_{i=1}^n (x0^i)/i Gamma(i+eps)/Gamma(i+eps) Z(i-1)
    //
    // sum_{i=1}^n (x0^i)/i Gamma(i-1+eps)/Gamma(i+eps) Z(i-1)
    //
    // sum_{i=1}^n (x0^i)/i Gamma(i-1+eps)/Gamma(i+eps) Z(i-1;2;y)
    //
    // sum_{i=1}^n (x0^i)/i Gamma(i-1+eps)/Gamma(i+eps) Z(i-1+3;2;y)
    //
    // sum_{i=1}^n (x0^i)/i Gamma(i-1+eps)/Gamma(i+eps) Z(i-1-1;2;y)
    //
    // sum_{i=1}^n (x0^i)/(i+3) Gamma(i-1+eps)/Gamma(i+eps) Z(i-1-1;2;y)
    //
    // sum_{i=1}^n (x0^i)/(i+3) Gamma(i-1+eps)/Gamma(i+eps) Z(i-1-1;2;y) z^(i+1)/((i+1)+1)^2
    //
    // sum_{i=1}^n (x0^i)/(i-3) Gamma(i+eps)/Gamma(i+eps) Z_{111}(i-1)

    std::cout << std::endl;
    std::cout << "checking eval explicit type_A" << std::endl;
    std::cout << std::endl;

    order = 3 ;
    NMAX = 10;

    time(&time_start);
    expr_start = create_transcendental_sum_type_A_and_set_gammas(n,i,
       letter(x0,1,i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Zsum(i-1),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_A>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_A_and_set_gammas(n,i,
       letter(x0,1,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Zsum(i-1),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_A>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 2 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_A_and_set_gammas(n,i,
       letter(x,1,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Zsum(i-1,lst{letter(y,2)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_A>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 3 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_A_and_set_gammas(n,i,
       letter(x,1,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Zsum(i-1+3,lst{letter(y,2)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_A>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 4 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;


    time(&time_start);
    expr_start = create_transcendental_sum_type_A_and_set_gammas(n,i,
       letter(x,1,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Zsum(i-1-1,lst{letter(y,2)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_A>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 5 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;


    time(&time_start);
    expr_start = create_transcendental_sum_type_A_and_set_gammas(n,i,
       basic_letter(x,1,3,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Zsum(i-1-1,lst{letter(y,2)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_A>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 6 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // takes a few seconds    
    time(&time_start);
    expr_start = create_transcendental_sum_type_A_and_set_gammas(n,i,
       basic_letter(x,1,3,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Zsum(i-1-1,lst{letter(y,2)})
        *create_list_of_tgamma_and_set_gammas(lst{ratio_of_tgamma(1,2,2,3)},i-1,eps,order)
        *basic_letter(z,2,1,i+1),
       eps,order,expand_status::start);
    expr_end = create_transcendental_sum_type_A_and_set_gammas(n,i,
       basic_letter(x,1,3,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Zsum(i-1-1,lst{letter(y,2)})
        *create_list_of_tgamma_and_set_gammas(lst{ratio_of_tgamma(1,2,2,3)},i-1,eps,order)
        *basic_letter(z,2,1,i+1),
       eps,order,expand_status::expansion_required);
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 7 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_A_and_set_gammas(n,i,
       basic_letter(x,1,-3,i),
       list_of_tgamma(lst{ratio_of_tgamma(-0,1,0,1)}),
       Zsum(i-1,lst{letter((ex) 1,1),letter((ex) 1,1),letter((ex) 1,1)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_A>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 8 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    //
    // The formulae checked here are
    //
    // sum_{i=1}^{n-1} (x^i)/i Gamma(i+eps)/Gamma(i+eps) Z(i-1)
    //                 (y^(n-i))/(n-i) Gamma(n-i+eps)/Gamma(n-i+eps) Z(n-i-1)
    //
    // sum_{i=1}^{n-1} (x^i)/i Gamma(i+eps)/Gamma(i+eps) Z(i-1;1;x1)
    //                 (y^(n-i))/(n-i) Gamma(n-i+eps)/Gamma(n-i+eps) Z(n-i-1;1;y1)
    //
    // sum_{i=1}^{n-1} (x^i)/(i+1) Gamma(i+eps)/Gamma(i+eps) Z(i-1)
    //                 (y^(n-i))/(n-i) Gamma(n-i+eps)/Gamma(n-i+eps) Z(n-i-1)
    //
    // sum_{i=1}^{n-1} (x^i)/i Gamma(i+eps)/Gamma(i+eps) Z(i-1)
    //                 (y^(n-i))/(n-i+1) Gamma(n-i+eps)/Gamma(n-i+eps) Z(n-i-1)
    //
    // sum_{i=1}^{n-1} (x^i)/i Gamma(i+eps)/Gamma(i+eps) Z(i-1+2;1;x1)
    //                 (y^(n-i))/(n-i) Gamma(n-i+eps)/Gamma(n-i+eps) Z(n-i-1+3;1;y1)
    //
    // sum_{i=1}^{n-1} (x^i)/(i+1) Gamma(i+eps)/Gamma(i+eps) Z(i-1;0;1)
    //                 Gamma(n-i+eps)/Gamma(n-i+eps) Z(n-i-1;0;1)
    //
    // sum_{i=1}^{n-1} (x^i)/(i+1) Gamma(i+eps)/Gamma(i+eps) Z(i-1+2;1;x1)
    //                 (y^(n-i))/(n-i+2) Gamma(n-i+eps)/Gamma(n-i+eps) Z(n-i-1+3;1;y1)
    //
    // sum_{i=1}^{n-1} (x^i)/(i+1) Gamma(i+eps)/Gamma(i+eps) Z(i-1-1;1;x1)
    //                 (y^(n-i))/(n-i+2) Gamma(n-i+eps)/Gamma(n-i+eps) Z(n-i-1-2;1;y1)
    //
    // sum_{i=1}^{n-1} (x^i)/(i-1) Gamma(i+eps)/Gamma(i+eps) Z(i-1-1;1;x1)
    //                 (y^(n-i))/(n-i-2) Gamma(n-i+eps)/Gamma(n-i+eps) Z(n-i-1-2;1;y1)
    //
    // sum_{i=1}^{n-1} (x^i)/(i-1) Gamma(i-1+eps)/Gamma(i+eps) Z(i-1-1;1;x1)
    //                 (y^(n-i))/(n-i-2) Gamma(n-i-1+eps)/Gamma(n-i+eps) Z(n-i-1-2;1;y1)
    //
    // sum_{i=1}^{n-1} (x^i)/(i-1) Gamma(i-1+eps)/Gamma(i+eps) Z(i-1-1;1;x1)
    //                 (y^(n-i))/(n-i-2) Gamma(n-i+1+eps)/Gamma(n-i-1+eps) Z(n-i-1-2;1;y1)

    std::cout << std::endl;
    std::cout << "checking eval explicit type_B" << std::endl;
    std::cout << std::endl;

    order = 3 ;
    NMAX = 10;

    time(&time_start);
    expr_start = create_transcendental_sum_type_B_and_set_gammas(n,i,
       letter(x,1,i),
       letter(y,1,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Zsum(i-1),
       Zsum(n-i-1),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_B>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_B_and_set_gammas(n,i,
       letter(x,1,i),
       letter(y,1,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Zsum(i-1,lst{letter(x1,1)}),
       Zsum(n-i-1,lst{letter(y1,1)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_B>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 2 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_B_and_set_gammas(n,i,
       basic_letter(x,1,1,i),
       letter(y,1,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Zsum(i-1),
       Zsum(n-i-1),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_B>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 3 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_B_and_set_gammas(n,i,
       basic_letter(x,1,0,i),
       basic_letter(y,1,1,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Zsum(i-1),
       Zsum(n-i-1),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_B>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 4 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_B_and_set_gammas(n,i,
       letter(x,1,i),
       letter(y,1,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Zsum(i-1+2,lst{letter(x1,1)}),
       Zsum(n-i-1+3,lst{letter(y1,1)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_B>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 5 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;


    time(&time_start);
    expr_start = create_transcendental_sum_type_B_and_set_gammas(n,i,
       basic_letter(x,1,1,i),
       basic_letter((ex) 1,0,0,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Zsum(i-1,lst{letter((ex) 1,0)}),
       Zsum(n-i-1,lst{letter((ex) 1,0)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_B>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand(); 
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 6 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_B_and_set_gammas(n,i,
       basic_letter(x,1,1,i),
       basic_letter(y,1,2,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Zsum(i-1+2,lst{letter(x1,1)}),
       Zsum(n-i-1+3,lst{letter(y1,1)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_B>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 7 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_B_and_set_gammas(n,i,
       basic_letter(x,1,1,i),
       basic_letter(y,1,2,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Zsum(i-1-1,lst{letter(x1,1)}),
       Zsum(n-i-1-2,lst{letter(y1,1)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_B>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 8 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;


    time(&time_start);
    expr_start = create_transcendental_sum_type_B_and_set_gammas(n,i,
       basic_letter(x,1,-1,i),
       basic_letter(y,1,-2,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Zsum(i-1-1,lst{letter(x1,1)}),
       Zsum(n-i-1-2,lst{letter(y1,1)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_B>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test    " << 9 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // takes a few seconds    
    time(&time_start);
    expr_start = create_transcendental_sum_type_B_and_set_gammas(n,i,
       basic_letter(x,1,-1,i),
       basic_letter(y,1,-2,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Zsum(i-1-1,lst{letter(x1,1)}),
       Zsum(n-i-1-2,lst{letter(y1,1)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_B>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test   " << 10 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_B_and_set_gammas(n,i,
       basic_letter(x,1,-1,i),
       basic_letter(y,1,-2,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(1,1,-1,1)}),
       Zsum(i-1-1,lst{letter(x1,1)}),
       Zsum(n-i-1-2,lst{letter(y1,1)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_B>(expr_start).set_expansion();
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    time(&time_end);
    std::cout << "Test   " << 11 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    //
    // The formulae checked here are
    //
    // - sum_{i=1}^n binom(n,i) (-1)^i (x0^i)/i Gamma(i+eps)/Gamma(i+eps) S(i)
    //
    // - sum_{i=1}^n binom(n,i) (-1)^i (x0^i)/i Gamma(i-1+eps)/Gamma(i+eps) S(i)
    //
    // - sum_{i=1}^n binom(n,i) (-1)^i (x0^i)/i Gamma(i-1+eps)/Gamma(i+eps) S(i;2;y)
    //
    // - sum_{i=1}^n binom(n,i) (-1)^i (x0^i)/i Gamma(i-1+eps)/Gamma(i+eps) S(i+3;2;y)
    //
    // - sum_{i=1}^n binom(n,i) (-1)^i (x0^i)/i Gamma(i-1+eps)/Gamma(i+eps) S(i-1;2;y)
    //
    // - sum_{i=1}^n binom(n,i) (-1)^i (x0^i)/(i+3) Gamma(i-1+eps)/Gamma(i+eps) S(i-1;2;y)
    //
    // - sum_{i=1}^n binom(n,i) (-1)^i (x0^i)/(i+3) Gamma(i-1+eps)/Gamma(i+eps) S(i-1;2;y) z^(i+1)/((i+1)+1)^2

    std::cout << std::endl;
    std::cout << "checking eval explicit type_C" << std::endl;
    std::cout << std::endl;

    order = 3 ;
    NMAX = 10;

    time(&time_start);
    expr_start = create_transcendental_sum_type_C_and_set_gammas(n,i,
       letter(x0,1,i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Ssum(i),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_C>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_C_and_set_gammas(n,i,
       letter(x0,1,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Ssum(i),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_C>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 2 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_C_and_set_gammas(n,i,
       letter(x,1,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Ssum(i,lst{letter(y,2)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_C>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 3 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;


    time(&time_start);
    expr_start = create_transcendental_sum_type_C_and_set_gammas(n,i,
       letter(x,1,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Ssum(i+3,lst{letter(y,2)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_C>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 4 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;


    time(&time_start);
    expr_start = create_transcendental_sum_type_C_and_set_gammas(n,i,
       letter(x,1,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Ssum(i-1,lst{letter(y,2)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_C>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 5 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;


    time(&time_start);
    expr_start = create_transcendental_sum_type_C_and_set_gammas(n,i,
       basic_letter(x,1,3,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Ssum(i-1,lst{letter(y,2)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_C>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 6 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;
    
    
    // takes a few seconds    
    order = 2 ;
    NMAX = 10;

    time(&time_start);
    expr_start = create_transcendental_sum_type_C_and_set_gammas(n,i,
       basic_letter(x,1,3,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Ssum(i-1,lst{letter(y,2)})
        *create_list_of_tgamma_and_set_gammas(lst{ratio_of_tgamma(1,2,2,3)},i-1,eps,order)
        *basic_letter(z,2,1,i+1),
       eps,order,expand_status::start);
    expr_end = create_transcendental_sum_type_C_and_set_gammas(n,i,
       basic_letter(x,1,3,i),
       list_of_tgamma(lst{ratio_of_tgamma(-1,1,0,1)}),
       Ssum(i-1,lst{letter(y,2)})
        *create_list_of_tgamma_and_set_gammas(lst{ratio_of_tgamma(1,2,2,3)},i-1,eps,order)
        *basic_letter(z,2,1,i+1),
       eps,order,expand_status::expansion_required);
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs( x == numeric(1,13) );
    expr_end = expr_end.subs( x == numeric(1,13) );
    expr_start = expr_start.subs( y == numeric(11,17) );
    expr_end = expr_end.subs( y == numeric(11,17) );
    expr_start = expr_start.subs( z == numeric(1,3) );
    expr_end = expr_end.subs( z == numeric(1,3) );
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 7 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    //
    // The formulae checked here are
    //
    // - sum_{i=1}^{n-1}  binom(n,i) (-1)^i (x^i)/i Gamma(i+eps)/Gamma(i+eps) S(i)
    //                 (y^(n-i))/(n-i) Gamma(n-i+eps)/Gamma(n-i+eps) S(n-i)
    //
    // - sum_{i=1}^{n-1}  binom(n,i) (-1)^i x^i Gamma(i+eps)/Gamma(i+eps) S(i;0;x1)
    //                 y^(n-i) Gamma(n-i+eps)/Gamma(n-i+eps) S(n-i;0;y1)
    //
    // - sum_{i=1}^{n-1}  binom(n,i) (-1)^i (x^i)/i Gamma(i+eps)/Gamma(i+eps) S(i;1;x1)
    //                 (y^(n-i))/(n-i) Gamma(n-i+eps)/Gamma(n-i+eps) S(n-i;1;y1)
    //
    // - sum_{i=1}^{n-1}  binom(n,i) (-1)^i (x^i)/(i+1) Gamma(i+eps)/Gamma(i+eps) S(i)
    //                 (y^(n-i))/(n-i) Gamma(n-i+eps)/Gamma(n-i+eps) S(n-i)
    //
    // - sum_{i=1}^{n-1}  binom(n,i) (-1)^i (x^i)/i Gamma(i+eps)/Gamma(i+eps) S(i)
    //                 (y^(n-i))/(n-i+1) Gamma(n-i+eps)/Gamma(n-i+eps) S(n-i)
    //
    // - sum_{i=1}^{n-1}  binom(n,i) (-1)^i (x^i)/i Gamma(i+eps)/Gamma(i+eps) S(i+2;1;x1)
    //                 (y^(n-i))/(n-i) Gamma(n-i+eps)/Gamma(n-i+eps) S(n-i+3;1;y1)
    //
    // - sum_{i=1}^{n-1}  binom(n,i) (-1)^i (x^i)/(i+1) Gamma(i+eps)/Gamma(i+eps) S(i;0;1)
    //                 Gamma(n-i+eps)/Gamma(n-i+eps) S(n-i;0;1)
    //
    // - sum_{i=1}^{n-1}  binom(n,i) (-1)^i (x^i)/(i+1) Gamma(i+eps)/Gamma(i+eps) S(i+2;1;x1)
    //                 (y^(n-i))/(n-i+2) Gamma(n-i+eps)/Gamma(n-i+eps) S(n-i+3;1;y1)
    //
    // - sum_{i=1}^{n-1}  binom(n,i) (-1)^i (x^i)/(i+1) Gamma(i+eps)/Gamma(i+eps) S(i-1;1;x1)
    //                 (y^(n-i))/(n-i+2) Gamma(n-i+eps)/Gamma(n-i+eps) S(n-i-2;1;y1)
    //

    std::cout << std::endl;
    std::cout << "checking eval explicit type_D" << std::endl;
    std::cout << std::endl;

    order = 3 ;
    NMAX = 10;

    time(&time_start);
    expr_start = create_transcendental_sum_type_D_and_set_gammas(n,i,
       letter(x,1,i),
       letter(y,1,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Ssum(i),
       Ssum(n-i),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_D>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_D_and_set_gammas(n,i,
       letter(x,0,i),
       letter(y,0,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Ssum(i,lst{letter(x1,0)}),
       Ssum(n-i,lst{letter(y1,0)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_D>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs( x == numeric(1,13) );
    expr_end = expr_end.subs( x == numeric(1,13) );
    expr_start = expr_start.subs( y == numeric(11,17) );
    expr_end = expr_end.subs( y == numeric(11,17) );
    expr_start = expr_start.subs( x1 == numeric(1,3) );
    expr_end = expr_end.subs( x1 == numeric(1,3) );
    expr_start = expr_start.subs( y1 == numeric(5,7) );
    expr_end = expr_end.subs( y1 == numeric(5,7) );
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 2 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // takes a few seconds    
    time(&time_start);
    expr_start = create_transcendental_sum_type_D_and_set_gammas(n,i,
       letter(x,1,i),
       letter(y,1,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Ssum(i,lst{letter(x1,1)}),
       Ssum(n-i,lst{letter(y1,1)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_D>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs( x == numeric(1,13) );
    expr_end = expr_end.subs( x == numeric(1,13) );
    expr_start = expr_start.subs( y == numeric(11,17) );
    expr_end = expr_end.subs( y == numeric(11,17) );
    expr_start = expr_start.subs( x1 == numeric(1,3) );
    expr_end = expr_end.subs( x1 == numeric(1,3) );
    expr_start = expr_start.subs( y1 == numeric(5,7) );
    expr_end = expr_end.subs( y1 == numeric(5,7) );
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 3 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_D_and_set_gammas(n,i,
       basic_letter(x,1,1,i),
       letter(y,1,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Ssum(i),
       Ssum(n-i),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_D>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs( x == numeric(1,13) );
    expr_end = expr_end.subs( x == numeric(1,13) );
    expr_start = expr_start.subs( y == numeric(11,17) );
    expr_end = expr_end.subs( y == numeric(11,17) );
    expr_start = expr_start.subs( x1 == numeric(1,3) );
    expr_end = expr_end.subs( x1 == numeric(1,3) );
    expr_start = expr_start.subs( y1 == numeric(5,7) );
    expr_end = expr_end.subs( y1 == numeric(5,7) );
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 4 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_D_and_set_gammas(n,i,
       basic_letter(x,1,0,i),
       basic_letter(y,1,1,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Ssum(i),
       Ssum(n-i),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_D>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs( x == numeric(1,13) );
    expr_end = expr_end.subs( x == numeric(1,13) );
    expr_start = expr_start.subs( y == numeric(11,17) );
    expr_end = expr_end.subs( y == numeric(11,17) );
    expr_start = expr_start.subs( x1 == numeric(1,3) );
    expr_end = expr_end.subs( x1 == numeric(1,3) );
    expr_start = expr_start.subs( y1 == numeric(5,7) );
    expr_end = expr_end.subs( y1 == numeric(5,7) );
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 5 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // takes a few seconds    
    time(&time_start);
    expr_start = create_transcendental_sum_type_D_and_set_gammas(n,i,
       letter(x,1,i),
       letter(y,1,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Ssum(i+2,lst{letter(x1,1)}),
       Ssum(n-i+3,lst{letter(y1,1)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_D>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs( x == numeric(1,13) );
    expr_end = expr_end.subs( x == numeric(1,13) );
    expr_start = expr_start.subs( y == numeric(11,17) );
    expr_end = expr_end.subs( y == numeric(11,17) );
    expr_start = expr_start.subs( x1 == numeric(1,3) );
    expr_end = expr_end.subs( x1 == numeric(1,3) );
    expr_start = expr_start.subs( y1 == numeric(5,7) );
    expr_end = expr_end.subs( y1 == numeric(5,7) );
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 6 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;


    time(&time_start);
    expr_start = create_transcendental_sum_type_D_and_set_gammas(n,i,
       basic_letter(x,1,1,i),
       basic_letter((ex) 1,0,0,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Ssum(i,lst{letter((ex) 1,0)}),
       Ssum(n-i,lst{letter((ex) 1,0)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_D>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs( x == numeric(1,13) );
    expr_end = expr_end.subs( x == numeric(1,13) );
    expr_start = expr_start.subs( y == numeric(11,17) );
    expr_end = expr_end.subs( y == numeric(11,17) );
    expr_start = expr_start.subs( x1 == numeric(1,3) );
    expr_end = expr_end.subs( x1 == numeric(1,3) );
    expr_start = expr_start.subs( y1 == numeric(5,7) );
    expr_end = expr_end.subs( y1 == numeric(5,7) );
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 7 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    expr_start = create_transcendental_sum_type_D_and_set_gammas(n,i,
       basic_letter(x,1,1,i),
       basic_letter(y,1,2,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Ssum(i+2,lst{letter(x1,1)}),
       Ssum(n-i+3,lst{letter(y1,1)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_D>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs( x == numeric(1,13) );
    expr_end = expr_end.subs( x == numeric(1,13) );
    expr_start = expr_start.subs( y == numeric(11,17) );
    expr_end = expr_end.subs( y == numeric(11,17) );
    expr_start = expr_start.subs( x1 == numeric(1,3) );
    expr_end = expr_end.subs( x1 == numeric(1,3) );
    expr_start = expr_start.subs( y1 == numeric(5,7) );
    expr_end = expr_end.subs( y1 == numeric(5,7) );
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 8 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // takes a few seconds    
    time(&time_start);
    expr_start = create_transcendental_sum_type_D_and_set_gammas(n,i,
       basic_letter(x,1,1,i),
       basic_letter(y,1,2,n-i),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       list_of_tgamma(lst{ratio_of_tgamma(0,1,0,1)}),
       Ssum(i-1,lst{letter(x1,1)}),
       Ssum(n-i-2,lst{letter(y1,1)}),
       eps,order,expand_status::start);
    expr_end = ex_to<transcendental_sum_type_D>(expr_start).set_expansion();
    expr_end = remove_trivial_Zsum(expr_end);
    expr_start = expr_start.subs( x == numeric(1,13) );
    expr_end = expr_end.subs( x == numeric(1,13) );
    expr_start = expr_start.subs( y == numeric(11,17) );
    expr_end = expr_end.subs( y == numeric(11,17) );
    expr_start = expr_start.subs( x1 == numeric(1,3) );
    expr_end = expr_end.subs( x1 == numeric(1,3) );
    expr_start = expr_start.subs( y1 == numeric(5,7) );
    expr_end = expr_end.subs( y1 == numeric(5,7) );
    expr_start = expr_start.subs(n==NMAX);
    expr_start = expr_start.expand();
    expr_end = expr_end.subs(n==NMAX);
    expr_end = expr_end.expand();
    expr_end = expr_end - expr_start;
    expr_end = expr_end.normal();
    time(&time_end);
    std::cout << "Test    " << 9 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    // -------------------------------------------
    //
    // The formulae checked here are
    //
    // (c-1) 2F1(a,b-1,c-1,x) - (c-1) 2F1(a,b,c-1,x) + ax 2F1(a+1,b,c,x) = 0
    //
    // (c1-1) 3F2(a,b1-1,b2,c1-1,c2,x) - (c1-1) 3F2(a,b1,b2,c1-1,c2,x) + x a b2/c2 3F2(a+1,b1,b2+1,c1,c2+1,x) = 0
    // 
    // (c-1) F1(a-1,b1,b2,c-1,x1,x2) - (c-1) F1(a,b1,b2,c-1,x1,x2) + x1 b1 F1(a,b1+1,b2,c,x1,x2) 
    //                              + x2 b2 F1(a,b1,b2+1,c,x1,x2) = 0
    //
    // (c-1) S1(a1-1,a2,b1,c-1,c1,x1,x2) - (c-1) S1(a1,a2,b1,c-1,c1,x1,x2) + x1 a2 b1/c1 S1(a1,a2+1,b1+1,c,c1+1,x1,x2)
    //                              + x2 a2 S1(a1,a2+1,b1,c,c1,x1,x2) =  0
    //
    // (c1-1) S1(a1,a2,b1-1,c,c1-1,x1,x2) - (c1-1) S1(a1,a2,b1,c,c1-1,x1,x2) + x1 a1 a2/c S1(a1+1,a2+1,b1,c+1,c1,x1,x2) = 0
    //
    // (c1-1) F2(a,b1-1,b2,c1-1,c2,x1,x2) - (c1-1) F2(a,b1,b2,c1-1,c2,x1,x2) + x1 a F2(a+1,b1,b2,c1,c2,x1,x2) = 0
    //
    // (c2-1) F2(a,b1,b2-1,c1,c2-1,x1,x2) - (c2-1) F2(a,b1,b2,c1,c2-1,x1,x2) + x2 a F2(a+1,b1,b2,c1,c2,x1,x2) = 0

    std::cout << std::endl;
    std::cout << "checking transcendental_fct" << std::endl;
    std::cout << std::endl;

    order = 5 ;

    time(&time_start);
    ma = 1 - eps;
    mb = 1 + eps;
    mc = 2 + 3*eps;
    expr_end = 
               create_transcendental_fct_type_A(x,lst{ma,mb-1},lst{mc-1},lst{mc},lst{ma,mb-1},
						eps,order,expand_status::expansion_required)
             - create_transcendental_fct_type_A(x,lst{ma,mb},lst{mc-1},lst{mc},lst{ma,mb},
						eps,order,expand_status::expansion_required)
         + x * create_transcendental_fct_type_A(x,lst{ma+1,mb},lst{mc},lst{mc},lst{ma,mb},
						eps,order,expand_status::expansion_required)
      ;
    expr_end = convert_Zsums_to_standard_form(expr_end);
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    time(&time_start);
    ma = 1 - eps;
    mb1 = 1 + eps;
    mc1 = 2 + 3*eps;
    mb2 = 1 + 4*eps;
    mc2 = 2 + 5*eps;
    expr_end = 
      create_transcendental_fct_type_A(x,lst{ma,mb1-1,mb2},lst{mc1-1,mc2},lst{mc1,mc2},lst{ma,mb1-1,mb2},
				       eps,order,expand_status::expansion_required)
      - create_transcendental_fct_type_A(x,lst{ma,mb1,mb2},lst{mc1-1,mc2},lst{mc1,mc2},lst{ma,mb1,mb2},
						eps,order,expand_status::expansion_required)
      + x * create_transcendental_fct_type_A(x,lst{ma+1,mb1,mb2+1},lst{mc1,mc2+1},lst{mc1,mc2},lst{ma,mb1,mb2},
						eps,order,expand_status::expansion_required)
      ;
    expr_end = convert_Zsums_to_standard_form(expr_end);
    time(&time_end);
    std::cout << "Test    " << 2 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    order = 4;

    time(&time_start);
    ma = 1 - eps;
    mc = 2 + 3*eps;
    mb1 = 1 + eps;
    mb2 = 1 + 4*eps;
    expr_end = 
      create_transcendental_fct_type_B(x1,x2,lst{mb1},lst(),lst{mb2},lst(),lst{ma-1},lst{mc-1},lst{mc},lst{ma-1,mb1,mb2},
				       eps,order,expand_status::expansion_required)
      - create_transcendental_fct_type_B(x1,x2,lst{mb1},lst(),lst{mb2},lst(),lst{ma},lst{mc-1},lst{mc},lst{ma,mb1,mb2},
					 eps,order,expand_status::expansion_required)
      + x1 * create_transcendental_fct_type_B(x1,x2,lst{mb1+1},lst(),lst{mb2},lst(),lst{ma},lst{mc},lst{mc},lst{ma,mb1,mb2},
					      eps,order,expand_status::expansion_required)
      + x2 * create_transcendental_fct_type_B(x1,x2,lst{mb1},lst(),lst{mb2+1},lst(),lst{ma},lst{mc},lst{mc},lst{ma,mb1,mb2},
					      eps,order,expand_status::expansion_required)
      ;
    expr_end = convert_Zsums_to_standard_form(expr_end);
    time(&time_end);
    std::cout << "Test    " << 3 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    order = 4;

    time(&time_start);
    ma1 = 1 - eps;
    mc  = 2 + 3*eps;
    mb1 = 1 + eps;
    mc1 = 2 - 5*eps;
    ma2 = 1 + 4*eps;
    expr_end = 
      create_transcendental_fct_type_C(x1,x2,lst{mb1},lst{mc1},lst{ma1-1,ma2},lst{mc-1},lst{mc,mc1},lst{ma1-1,ma2,mb1},
				       eps,order,expand_status::expansion_required)
      - create_transcendental_fct_type_C(x1,x2,lst{mb1},lst{mc1},lst{ma1,ma2},lst{mc-1},lst{mc,mc1},lst{ma1,ma2,mb1},
				       eps,order,expand_status::expansion_required)
      + x1 * create_transcendental_fct_type_C(x1,x2,lst{mb1+1},lst{mc1+1},lst{ma1,ma2+1},lst{mc},lst{mc,mc1},lst{ma1,ma2,mb1},
				       eps,order,expand_status::expansion_required)
      + x2 * create_transcendental_fct_type_C(x1,x2,lst{mb1},lst{mc1},lst{ma1,ma2+1},lst{mc},lst{mc,mc1},lst{ma1,ma2,mb1},
				       eps,order,expand_status::expansion_required)
      ;
    expr_end = convert_Zsums_to_standard_form(expr_end);
    time(&time_end);
    std::cout << "Test    " << 4 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    order = 4;

    time(&time_start);
    ma1 = 1 - eps;
    mc  = 2 + 3*eps;
    mb1 = 1 + eps;
    mc1 = 2 - 5*eps;
    ma2 = 1 + 4*eps;
    expr_end = 
      create_transcendental_fct_type_C(x1,x2,lst{mb1-1},lst{mc1-1},lst{ma1,ma2},lst{mc},lst{mc,mc1},lst{ma1,ma2,mb1-1},
				       eps,order,expand_status::expansion_required)
      - create_transcendental_fct_type_C(x1,x2,lst{mb1},lst{mc1-1},lst{ma1,ma2},lst{mc},lst{mc,mc1},lst{ma1,ma2,mb1},
				       eps,order,expand_status::expansion_required)
      + x1 *  create_transcendental_fct_type_C(x1,x2,lst{mb1},lst{mc1},lst{ma1+1,ma2+1},lst{mc+1},lst{mc,mc1},lst{ma1,ma2,mb1},
				       eps,order,expand_status::expansion_required)
      ;
    expr_end = convert_Zsums_to_standard_form(expr_end);
    time(&time_end);
    std::cout << "Test    " << 5 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    order = 3;

    time(&time_start);
    mb1 = 1 - eps;
    mc1 = 2 + 3*eps;
    mb2 = 1 + eps;
    mc2 = 2 - 5*eps;
    ma  = 1 + 4*eps;
    expr_end = 
      create_transcendental_fct_type_D(x1,x2,lst{mb1-1},lst{mc1-1},lst{mb2},lst{mc2},lst{ma},lst(),lst{mc1,mc2},lst{ma,mb1-1,mb2},
				       eps,order,expand_status::expansion_required)
      - create_transcendental_fct_type_D(x1,x2,lst{mb1},lst{mc1-1},lst{mb2},lst{mc2},lst{ma},lst(),lst{mc1,mc2},lst{ma,mb1,mb2},
				       eps,order,expand_status::expansion_required)
      + x1 * create_transcendental_fct_type_D(x1,x2,lst{mb1},lst{mc1},lst{mb2},lst{mc2},lst{ma+1},lst(),lst{mc1,mc2},lst{ma,mb1,mb2},
				       eps,order,expand_status::expansion_required)
      ;
    expr_end = convert_Zsums_to_standard_form(expr_end);
    time(&time_end);
    std::cout << "Test    " << 6 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;

    order = 3;

    time(&time_start);
    mb1 = 1 - eps;
    mc1 = 2 + 3*eps;
    mb2 = 1 + eps;
    mc2 = 2 - 5*eps;
    ma  = 1 + 4*eps;
    expr_end = 
      create_transcendental_fct_type_D(x1,x2,lst{mb1},lst{mc1},lst{mb2-1},lst{mc2-1},lst{ma},lst(),lst{mc1,mc2},lst{ma,mb1,mb2-1},
				       eps,order,expand_status::expansion_required)
      - create_transcendental_fct_type_D(x1,x2,lst{mb1},lst{mc1},lst{mb2},lst{mc2-1},lst{ma},lst(),lst{mc1,mc2},lst{ma,mb1,mb2},
				       eps,order,expand_status::expansion_required)
      + x2 * create_transcendental_fct_type_D(x1,x2,lst{mb1},lst{mc1},lst{mb2},lst{mc2},lst{ma+1},lst(),lst{mc1,mc2},lst{ma,mb1,mb2},
				       eps,order,expand_status::expansion_required)
      ;
    expr_end = convert_Zsums_to_standard_form(expr_end);
    time(&time_end);
    std::cout << "Test    " << 7 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;


    // -------------------------------------------
    //

    std::cout << std::endl;
    std::cout << "checking multiplication of list_of_tgamma" << std::endl;
    std::cout << std::endl;

    time(&time_start);
    int locorder = 4;
    int suborder = 2;
    lst la = { create_ratio_of_tgamma(2,-3,1,-2), create_ratio_of_tgamma(1,0,1,0) };
    lst lb = { create_ratio_of_tgamma(1,0,1,-2), create_ratio_of_tgamma(2,-3,1,0) };
    ex subsuma = create_letter(x,0,n-1)*create_Zsum(n-2,lst())
      *create_list_of_tgamma_and_set_gammas(la, n-1, eps, suborder);
    ex subsumb = create_letter(x,0,n-1)*create_Zsum(n-2,lst())
      *create_list_of_tgamma_and_set_gammas(lb, n-1, eps, suborder);

    expr_end = 
      create_transcendental_sum_type_A_and_expand(Infinity,n,
						  create_unit_letter((ex) 0,n),
						  _empty_list_of_tgamma,
						  subsuma,
						  eps,locorder)
      -
      create_transcendental_sum_type_A_and_expand(Infinity,n,
						  create_unit_letter((ex) 0,n),
						  _empty_list_of_tgamma,
						  subsumb,
						  eps,locorder)
      ;
    expr_end = convert_Zsums_to_standard_form(expr_end);
    time(&time_end);
    std::cout << "Test    " << 1 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;


    order = 1 ;

    time(&time_start);
    expr_end = 
      transcendental_fct_type_B(x,y,
				lst{5-3*eps,6-4*eps,1},lst{6-3*eps,2-2*eps},
				lst{-2+3*eps,-1+eps},lst{5-eps},
				lst{6-3*eps,2-2*eps},lst{4-2*eps,1},
				lst{1-2*eps,1-2*eps,-3+2*eps,4-2*eps},
				lst{1+eps,1+eps,1-eps,1-eps,1-eps,1-eps,1+eps,3,1,5-3*eps},
				eps,
				order,
				expand_status::expansion_required)
      -
       transcendental_fct_type_B(x,y,
				 lst{1,5-3*eps,6-4*eps},lst{6-3*eps,2-2*eps},
				 lst{-2+3*eps,-1+eps},lst{5-eps},
				 lst{6-3*eps,2-2*eps},lst{1,4-2*eps},
				 lst{-3+2*eps,4-2*eps,1-2*eps,1-2*eps},
				 lst{5-3*eps,1+eps,3,1,1+eps,1-eps,1-eps,1+eps,1-eps,1-eps},
				 eps,
				 order,
				 expand_status::expansion_required )
      ;
    expr_end = convert_Zsums_to_standard_form(expr_end);
    time(&time_end);
    std::cout << "Test    " << 2 << " : " << expr_end << "               Time in seconds : " << difftime(time_end,time_start) << std::endl;





  } catch (std::exception &e)
    {
      std::cout << "Exception : " << e.what() << std::endl;
    }

  std::cout << std::endl;
  std::cout << "end nestedsums testsuite" << std::endl;
  std::cout << std::endl;

  return 0;
}


