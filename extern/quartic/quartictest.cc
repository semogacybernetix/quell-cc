#include <iostream>
#include <iomanip>

#include "quartic.h"

//---------------------------------------------------------------------------
int main()
{
float a, b, c, d, x1, x2, x3, x4;
std::complex<float>* solutions;

		// read coefficients of an algebric equation of 4th order (-1000 for exiting the application)
		std::cout << "--------------------------------------------"  << std::endl << std::endl;
		std::cout << "A = "; std::cin >> a;
		std::cout << "B = "; std::cin >> b;
		std::cout << "C = "; std::cin >> c;
		std::cout << "D = "; std::cin >> d;
		std::cout << std::endl;

// solve the algebric equation of 4th order and print the results
solutions = solve_quartic(a, b, c, d);

x1= solutions[0].real();
x2= solutions[2].real();
x3= solutions[3].real();
x4= solutions[4].real();

delete[] solutions;
}





