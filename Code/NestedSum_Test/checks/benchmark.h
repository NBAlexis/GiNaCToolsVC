// 
// written by Stefan Weinzierl
//

//#include <iostream>
//#include <stdexcept>
//#include <ctime>
//
//#include "ginac/ginac.h"
//#include "nestedsums/nestedsums.h"


int bmmain()
{

  using namespace GiNaC;
  using namespace nestedsums;

  try{

    time_t time_start;
    time_t time_end;

    std::cout << std::endl;

    int k;

    symbol n("n");

    for (k=1;k<11;k++){

      ex Z1 = create_harmonic_sum_with_ones(n,k);

      // measuring time starts here
      time(&time_start);

      ex erg = Z1*Z1;

      // measuring time end here
      time(&time_end);

      std::cout << std::endl;
      std::cout << " " << k << " : " << Z1 << " Time in seconds : " << difftime(time_end,time_start) << std::endl;
      std::cout << std::endl;

    }

  } catch (std::exception &e)
    {
      std::cout << "Exception : " << e.what() << std::endl;
    }

  return 0;
}

