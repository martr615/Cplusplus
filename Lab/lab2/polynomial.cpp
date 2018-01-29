/*********************************************************
* Class Polynomial member functions implementation       *
* TNG033: Lab 3                                          *
**********************************************************/

#include <iostream>
#include <iomanip>
#include <math.h>
#include "polynomial.h"

//#include <cmath>

// _________________________ CONSTRUCTORS ___________________________
// Default constructor.
Polynomial::Polynomial(){
    degree = 0;
    coef = nullptr;
}

// Constructor with d = degree and c[] =  coefficients.
Polynomial::Polynomial(int d, double c[]){
    degree = d;
    coef = new double[degree+1]; // Allokera minne för koefficienterna.

    for(int i = 0; i <= degree; i++){
        coef[i] = c[i];
    }
}

// Constructor with a double. Degree = 0;
Polynomial::Polynomial(double d){
    degree = 0;
    coef = new double[degree+1];  // Array with one position.s
    coef[0] = d;
}

// Copy constructor
Polynomial::Polynomial(const Polynomial &P){
    degree = P.degree;
    coef = new double[degree+1];
    for(int i = 0; i <= degree; i++){
        coef[i] = P.coef[i];  // Copy the coefficients.
    }
}

// Destructor.
Polynomial::~Polynomial(){
    //cout << "before delete coef" << endl;   // Debug minnesluckor
    delete [] coef;
    //cout << "efter delete coef" << endl;    // Debug minnesluckor
}

// _________________________ OPERATORS ___________________________

// Operator "=".
// Assignment operator.
const Polynomial& Polynomial::operator=(const Polynomial P){
    // Om de är olika så kopiera bara.
    if (this != &P){
        //Replaces it with P
        delete [] coef;  // För memory leaks, måste delete:a innan assignar nya värden på coef.
        coef = new double[P.degree+1];
        degree = P.degree;

        for (int i = 0; i < P.degree+1; i++){
            coef[i] = P.coef[i];
        }
    }
    return *this;
}

// Operator "()".
// Evaluate the given double, for example f(x) where x is a double.
double Polynomial::operator()(double x) const{
    double sum = 0;
    for(int i = 0; i <= degree; i++){
        sum += coef[i] * pow(x,i);  // Räknar polynomet. pow(base,exponent)
    }
    return sum;
}

// Operator "[]".
// Returns the given position x in the polynomial.
double& Polynomial::operator[](const int x) const {
    coef[x] = 0;    // För vi ska skriva över denna position, men den har redan ett värde, så nollställ.
    return coef[x];
}


// Operator "+",
// Addition between polynomials. Returns a new polynomial with the answer.
Polynomial operator+(const Polynomial& P1, const Polynomial& P2){
    int newDegree = 0;

    // Determine which of the polynomials that has the largest degree.
    if(P1.degree < P2.degree){
        newDegree = P2.degree;
    }
    else{
        newDegree = P1.degree;  // If P1 has a higher degree.
    }

    //double *newCoef = new double[newDegree+1];
    double newCoef[newDegree+1];   // Allokera minne för den nya array:en.

    // Add the two polynomials together at the same index i.
    for(int i = 0; i <= newDegree; i++){
        newCoef[i] = 0; // Clear the array from worthless values. We received junk values without it.

        if (i <= P1.degree){
            newCoef[i] += P1.coef[i];
        }

        if (i <= P2.degree){
            newCoef[i] += P2.coef[i];
        }
    }
    return Polynomial(newDegree, newCoef);  // Calls the constructor to create polynomial which is the answer.
}


// ___________________________ FUNCTIONS _____________________________

// Display a polynomial.
void Polynomial::display(ostream& os) const{
    cout << setprecision(2) << fixed << coef[0];
    for(int i = 1; i <= degree; i++){
        if (coef[i] != 0 ){

               os << fixed << setprecision(2) << " + " << coef[i] << " * X^"<< i;
        }
    }
}

Polynomial *Polynomial::clone() const {
    Polynomial* newPoly = new Polynomial(this->degree,this->coef);

    return newPoly;
}


