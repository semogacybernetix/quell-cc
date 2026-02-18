#include <iostream>
#include <vector>
#include <Eigen/Eigenvalues>

// Benötigt Eigen-Bibliothek: http://eigen.tuxfamily.org
// Kompilieren mit: g++ -I /path/to/eigen main.cpp -o solver

void solveQuartic(double a, double b, double c, double d, double e) {
    // Normalisierung: ax^4 + bx^3 + cx^2 + dx + e = 0 -> x^4 + (b/a)x^3 + ... = 0
    if (a == 0) {
        std::cerr << "Keine quartische Gleichung (a=0)" << std::endl;
        return;
    }

    // Begleitmatrix (Companion Matrix) aufstellen
    Eigen::Matrix<double, 4, 4> companion_matrix;
    companion_matrix << 0, 0, 0, -e/a,
                        1, 0, 0, -d/a,
                        0, 1, 0, -c/a,
                        0, 0, 1, -b/a;

    // Eigenwerte berechnen
    Eigen::EigenSolver<Eigen::Matrix<double, 4, 4>> solver(companion_matrix);
    auto roots = solver.eigenvalues();

    std::cout << "Loesungen (komplex):" << std::endl;
    for(int i=0; i<4; ++i) {
        std::cout << roots(i).real() << " + " << roots(i).imag() << "i" << std::endl;
    }
}

int main() {
    // Beispiel: x^4 - 6x^3 + 11x^2 - 6x = 0
    solveQuartic(1, -6, 11, -6, 0);
    return 0;
}
