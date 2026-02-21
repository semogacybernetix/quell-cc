/***************************************************************************
 *   Copyright (C) 2016 by Саша Миленковић                                 *
 *   sasa.milenkovic.xyz@gmail.com                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *   ( http://www.gnu.org/licenses/gpl-3.0.en.html )                       *
 *									   *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <cmath>
#include <iostream>
#include "quartic.h"

//---------------------------------------------------------------------------
// solve cubic equation x^3 + a*x^2 + b*x + c
// x - array of size 3
// In case 3 real roots: => x[0], x[1], x[2], return 3
//         2 real roots: x[0], x[1],          return 2
//         1 real root : x[0], x[1] ± i*x[2], return 1
unsigned int solveP3(real *x,real a,real b,real c) {
	real a2 = a*a;
    	real q  = (a2 - 3*b)/9;
	real r  = (a*(2*a2-9*b) + 27*c)/54;
    	real r2 = r*r;
	real q3 = q*q*q;
	real A,B;
    	if(r2<q3)
    	{
    		real t=r/sqrtr(q3);
    		if( t<-1) t=-1;
    		if( t> 1) t= 1;
    		t=acosr(t);
    		a/=3; q=-2*sqrtr(q);
    		x[0]=q*cosr(t/3)-a;
    		x[1]=q*cosr((t+M_2PI)/3)-a;
    		x[2]=q*cosr((t-M_2PI)/3)-a;
    		return 3;
    	}
    	else
    	{
    		A =-powr(absr(r)+sqrtr(r2-q3),real (1)/3);
    		if( r<0 ) A=-A;
    		B = (0==A ? 0 : q/A);

		a/=3;
		x[0] =(A+B)-a;
		x[1] =-real (0.5)*(A+B)-a;
		x[2] = real (0.5)*sqrtr(real (3))*(A-B);
		if(fabs(x[2])<eps) { x[2]=x[1]; return 2; }

		return 1;
        }
}

//---------------------------------------------------------------------------
// Solve quartic equation x^4 + a*x^3 + b*x^2 + c*x + d
// (attention - this function returns dynamically allocated array. It has to be released afterwards)
DComplex* solve_quartic(real a, real b, real c, real d)
{
	real a3 = -b;
	real b3 =  a*c -real (4)*d;
	real c3 = -a*a*d - c*c + real (4)*b*d;

std::cout << "ak: " << a3 << std::endl;
std::cout << "bk: " << b3 << std::endl;
std::cout << "ck: " << c3 << std::endl;
std::cout << std::endl;

	// cubic resolvent
	// y^3 − b*y^2 + (ac−4d)*y − a^2*d−c^2+4*b*d = 0

	real x3[3];
	unsigned int iZeroes = solveP3(x3, a3, b3, c3);

	real q1, q2, p1, p2, D, sqD, y;

std::cout << "y1: " << x3[0] << std::endl;
std::cout << "y2: " << x3[1] << std::endl;
std::cout << "y3: " << x3[2] << std::endl;
std::cout << std::endl;

	y = x3[0];
	// THE ESSENCE - choosing Y with maximal absolute value !
	if(iZeroes != 1)
	{
		if(fabs(x3[1]) > fabs(y)) y = x3[1];
		if(fabs(x3[2]) > fabs(y)) y = x3[2];
	}

	// h1+h2 = y && h1*h2 = d  <=>  h^2 -y*h + d = 0    (h === q)

	D = y*y - 4*d;

std::cout << "D: " << D << std::endl;
std::cout << std::endl;

	if(fabs(D) < eps) //in other words - D==0
	{
		q1 = q2 = y * real (0.5);
		// g1+g2 = a && g1+g2 = b-y   <=>   g^2 - a*g + b-y = 0    (p === g)
		D = a*a - 4*(b-y);
		if(fabs(D) < eps) //in other words - D==0
			p1 = p2 = a * real (0.5);

		else
		{
			sqD = sqrtr(D);
			p1 = (a + sqD) * real (0.5);
			p2 = (a - sqD) * real (0.5);
		}
	}
	else
	{
		sqD = sqrtr(D);
		q1 = (y + sqD) * real (0.5);
		q2 = (y - sqD) * real (0.5);
		// g1+g2 = a && g1*h2 + g2*h1 = c       ( && g === p )  Krammer
		p1 = (a*q1-c)/(q1-q2);
		p2 = (c-a*q2)/(q1-q2);
	}

std::cout << "a1: " << p1 << std::endl;
std::cout << "b1: " << q1 << std::endl;
std::cout << "a2: " << p2 << std::endl;
std::cout << "b2: " << q2 << std::endl;
std::cout << std::endl;

    DComplex* retval = new DComplex[4];

	// solving quadratic eq. - x^2 + p1*x + q1 = 0
	D = p1*p1 - 4*q1;
	if(D < 0.0)
	{
		retval[0].real( -p1 * real (0.5) );
		retval[0].imag( sqrtr(-D) * real (0.5) );
		retval[1] = std::conj(retval[0]);
	}
	else
	{
		sqD = sqrtr(D);
		retval[0].real( (-p1 + sqD) * real (0.5) );
		retval[1].real( (-p1 - sqD) * real (0.5) );
	}

	// solving quadratic eq. - x^2 + p2*x + q2 = 0
	D = p2*p2 - 4*q2;
	if(D < 0.0)
	{
		retval[2].real( -p2 * real (0.5) );
		retval[2].imag( sqrtr(-D) * real (0.5) );
		retval[3] = std::conj(retval[2]);
	}
	else
	{
		sqD = sqrtr(D);
		retval[2].real( (-p2 + sqD) * real (0.5) );
		retval[3].real( (-p2 - sqD) * real (real (0.5)) );
	}

    return retval;
}

