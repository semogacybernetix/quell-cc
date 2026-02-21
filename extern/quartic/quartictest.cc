
#include <iostream>
#include <iomanip>

#include "../../cc/class/quartic.h"

//using namespace std;

//---------------------------------------------------------------------------
int main()
{
	std::cout << std::fixed << std::setprecision(8);
	real a, b, c, d;

		// read coefficients of an algebric equation of 4th order (-1000 for exiting the application)
		std::cout << "--------------------------------------------"  << std::endl << std::endl;
		std::cout << "A = "; std::cin >> a;
		std::cout << "B = "; std::cin >> b;
		std::cout << "C = "; std::cin >> c;
		std::cout << "D = "; std::cin >> d;
		std::cout << std::endl;

        // solve the algebric equation of 4th order and print the results
        std::complex<real>* solutions = solve_quartic(a, b, c, d);

        // print the results
		std::cout << "x1 = " << (solutions[0].real()>=0. ? " " : "") << solutions[0].real(); if(solutions[0].imag()!=0.0) std::cout << "   +   i * " <<  solutions[0].imag(); std::cout << std::endl;
		std::cout << "x2 = " << (solutions[1].real()>=0. ? " " : "") << solutions[1].real(); if(solutions[1].imag()!=0.0) std::cout << "   -   i * " << -solutions[1].imag(); std::cout << std::endl;
		std::cout << "x3 = " << (solutions[2].real()>=0. ? " " : "") << solutions[2].real(); if(solutions[2].imag()!=0.0) std::cout << "   +   i * " <<  solutions[2].imag(); std::cout << std::endl;
		std::cout << "x4 = " << (solutions[3].real()>=0. ? " " : "") << solutions[3].real(); if(solutions[3].imag()!=0.0) std::cout << "   -   i * " << -solutions[3].imag(); std::cout << std::endl;

		// control / test
		std::cout << std::endl;
		std::cout << polinom_4(solutions[0], a, b, c, d) << std::endl;
		std::cout << polinom_4(solutions[1], a, b, c, d) << std::endl;
		std::cout << polinom_4(solutions[2], a, b, c, d) << std::endl;
		std::cout << polinom_4(solutions[3], a, b, c, d) << std::endl;

        delete[] solutions;
cschnittpunkte sp;
quartischmalin (a, b, c, d, sp);

        // print the results
		std::cout << std::endl;
		std::cout << "anz = " << sp.anz << std::endl;
		std::cout << "x1 = " << sp.abstand[0] << std::endl;
		std::cout << "x2 = " << sp.abstand[1] << std::endl;
		std::cout << "x3 = " << sp.abstand[2] << std::endl;
		std::cout << "x4 = " << sp.abstand[3] << std::endl;

		std::cout << std::endl;
}