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


#ifndef MULTIVARIATECOEFFICIENTMR_H
#define MULTIVARIATECOEFFICIENTMR_H

//#include <ginac/ginac.h>
#include <iostream>

namespace GiNaCRA
{
    /**
     * Class encapsulating expressions as coefficients of the terms.
     *
     * @author Sebastian Junges
     * @since 2011-12-07
     * @version 2011-12-08
     */
    class GINACRA_API MultivariateCoefficientMR
    {
        public:
            MultivariateCoefficientMR();
            MultivariateCoefficientMR( const GiNaC::ex& );
            friend bool operator ==( const MultivariateCoefficientMR& m1, const MultivariateCoefficientMR& m2 );
            friend const MultivariateCoefficientMR operator *( const MultivariateCoefficientMR& m1, const MultivariateCoefficientMR& m2 );
            friend const MultivariateCoefficientMR operator +( const MultivariateCoefficientMR& m1, const MultivariateCoefficientMR& m2 );
            friend const MultivariateCoefficientMR operator -( const MultivariateCoefficientMR& m1 );
            friend const MultivariateCoefficientMR operator -( const MultivariateCoefficientMR& m1, const MultivariateCoefficientMR& m2 );
            friend const MultivariateCoefficientMR operator /( const MultivariateCoefficientMR& m1, const MultivariateCoefficientMR& m2 );
            friend std::ostream& operator <<( std::ostream& os, const MultivariateCoefficientMR& m1 );

            inline GiNaC::ex getExpression() const
            {
                return mCoefficient;
            }

            inline MultivariateCoefficientMR inverse() const
            {
                if( GiNaC::is_exactly_a<GiNaC::numeric>( mCoefficient ))
                {
                    GiNaC::numeric num = GiNaC::ex_to<GiNaC::numeric>( mCoefficient );
                    return MultivariateCoefficientMR( GiNaC::ex( num.inverse() ));
                }
                throw (std::domain_error( "The coefficient is not a numeric (others not supported yet)" ));
            }

        protected:
            GiNaC::ex mCoefficient;
    };

}
#endif   /** MULTIVARIATECOEFFICIENTMR_H */
