/*----------------------------------------------------------------------------------
Dividing one integer by another results in a rounded-down integer
5/2    results in 2
5.0/2  results in 2.5
Finding roots of quadratic equation:
double rootCoeff = -b/(2*a)
Since b and 2 were both integers, -b/2 was rounded down before being multiplied by a
The fix ? Cast atleast one operand to double
double rootCoeff = -b/(2.0*a)
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <cmath>

// Function to find roots of quadratic equation ax2+bx+c=0
void findQuadrantRoots(int a, int b, int c) {
    if (a == 0) {
        std::cout << "Not a quadratic equation" << std::endl;
    }

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        std::cout << "No real roots" << std::endl;
    }

    double rootCoeff = -b/(2.0 * a);
    double sqrtDiscriminant = std::sqrt(discriminant);
    double root1 = rootCoeff + sqrtDiscriminant / (2 * a);
    double root2 = rootCoeff - sqrtDiscriminant / (2 * a);
    std::cout << "Roots: " << root1 << " and " << root2 << std::endl;
}

int main() {
    double a = 1, b = -3, c = 2;  // x^2 - 3x + 2 = 0;
    findQuadrantRoots(a, b, c);
    return 0;
}
