/*********************************************************
* Class Log member functions implementation              *
* TNG033: Lab 3                                          *
**********************************************************/

#include "math.h"
#include "logarithm.h"
#include "polynomial.h"

// _________________________ CONSTRUCTORS ___________________________

// Default constructor.
Log::Log(){
    coef1 = 0.0;
    coef2 = 1.0;
    base = 2;
    double c[2] = {0, 1};
    expression = new Polynomial(1,c);   // New polynomial with degree 1. Expression is log_2(x)
}

// Constructor to create a logarithm with given input.
Log::Log(const Expression& E, const double c1,const double c2, const int b){
    coef1 = c1;
    coef2 = c2;
    base = b;
    expression = E.clone();
}

//  Constructor to clone the given Log.
Log::Log(Log& L){

    coef1 = L.coef1;
    coef2 = L.coef2;
    base = L.base;
    expression = L.expression->clone();
}

// Destructor.
Log::~Log(){
    //cout << "f�re delete expression" << endl; // Debug minnesluckor
    delete expression;    // Beh�vs inte f�r heap error? (Attempt to free memory already freed)
    //cout << "efter delete expression" << endl; // Debug minnesluckor
}

// Assignment operator. // Beh�vs en assignment operator? F�r vi f�r r�tt �nd� i output. Och koden funkar inte.

Log& Log::operator=(const Log &L){
    // Om de �r olika s� kopiera bara.
    if(this != &L){
        delete expression; // F�r har redan v�rden som skrivs �ver eller? Kanske inte f�r clone skapar en ny ju. Men expressions skrivs ju �ver tror jag?
        coef1 = L.coef1;
        coef2 = L.coef2;
        base = L.base;
        expression = L.expression->clone();
    }
    return *this;
}

// _________________________ OPERATORS ___________________________

double Log::operator()(double x) const{
    double sum = 0;
    // Delas p� log(base) f�r logaritmregel, kolla blocket.
    sum = coef2 *( log10( (*expression)(x) ) / log10(base) ) + coef1;
    return sum;
}

void Log::display(ostream& os) const{
    if(coef1 == 0){
        os << coef2 << " * Log_" << base << "( " << *expression << " )";
    }
    else{
        os << coef1 << " + " << coef2 << " * Log_" << base << "( " << *expression << " )";
    }
}

// ___________________________ FUNCTIONS _____________________________

Log *Log::clone() const{
    Log *newLog = new Log(*this->expression, this->coef1, this->coef2, this->base);
    return newLog;
}




