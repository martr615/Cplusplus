/*************************
* Class Polynomial       *
* TNG033: Lab 3          *
**************************/

#ifndef POL_H
#define POL_H

#include <iostream>

using namespace std;

#include "expression.h"


class Polynomial : public Expression{
public:
    // Constructors.
    Polynomial(); // Default constructor.
    Polynomial(int d, double *C);   //
    Polynomial(double d);
    Polynomial(const Polynomial& P); //Copy contructor.
    ~Polynomial(); //Destructor.

    // Operators.
    const Polynomial& operator=(const Polynomial P);    // Assignment operator.
    double operator()(double d) const;  // Calculate/evaluate.
    double& operator[](const int x) const;    // Returns the position x in the polynomial array.
    friend Polynomial operator+(const Polynomial& P1, const Polynomial& P2); // Addition between two Polynomials.

    // Functions.
    void display(ostream& os) const;   // Display function.
    Polynomial* clone() const;

protected:
    // Variables.
    int degree;  // Vilken exponent polynomet går upp till.
    double* coef; // Array av koefficienter.
};


#endif
