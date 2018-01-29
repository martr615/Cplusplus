/*************************
* Class Log              *
* TNG033: Lab 3          *
**************************/


#ifndef LOG_H
#define LOG_H

#include <iostream>

using namespace std;

#include "expression.h"

class Log : public Expression{
public:
    // Constructors.
    Log();  // Default.
    Log(const Expression& E, const double c1,const double c2, const int b);
    Log(Log& L);    //Copy constructor
    ~Log(); //Destructor

    // Operators.
    Log& operator=(const Log &L);    // För assignment operatorn som vi inte vet om den ska finnas med.
    double operator() (double d) const; // Calculate.

    // Functions.
    void display(ostream& os) const;
    Log* clone() const; // Clone function.

protected:
    double coef1, coef2;
    int base;
    Expression *expression;
};

#endif
