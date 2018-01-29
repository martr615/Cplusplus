/*************************
* Class Expression       *
* TNG033: Lab 3          *
**************************/

#ifndef EXP_H
#define EXP_H

#include <iostream>

using namespace std;

const double EPSILON = 1.0e-5;


class Expression{
public:
    friend ostream& operator<<(ostream& os, const Expression& E); // Display the expression.

    bool isRoot(double d) const;    // Check if it's a root.


    virtual double operator()(double x) const = 0;    // Behövs i header för att kunna nå funktionen.

    virtual Expression* clone() const = 0; // ABSTRAKT när = 0;
    virtual ~Expression(){};    // Eventuell destruktor här?

protected:
    virtual void display(ostream &os) const = 0;  // Virtual behövs för att den gör latebinding (kollar den
};


#endif
