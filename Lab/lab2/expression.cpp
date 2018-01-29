/*********************************************************
* Class Expression member functions implementation       *
* TNG033: Lab 3                                          *
**********************************************************/
#include <cmath>

#include "expression.h"

using namespace std;

// Display the expression.
ostream& operator<<(ostream& os, const Expression& E){
    E.display(os); // Kallar displayfunktionen i respektive subklass.
    return os;
}

// Test if it's a root.
bool Expression::isRoot(double x) const{
    return(fabs( (*this)(x)) < EPSILON); // Kallar operator() för respektive subklass.

}

// Ha en destruktor i här i expression?





