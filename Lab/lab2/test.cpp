/******************************************************
* Test program for the expressions hierarchy          *
* Author: Aida Nordman                                *
* TNG033: Lab 3                                       *
*******************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;

#include "polynomial.h"
#include "logarithm.h"


/**************************************************
* main(): incremental tests of lab 3              *
* Do NOT MODIFY                                   *
***************************************************/

int main(){
    /*****************************************************
    * TEST PHASE 0                                       *
    * Polynomial: constructors and operator<<            *
    ******************************************************/
    cout << "TEST PHASE 0\n";

    //coeficients of polynomials
    double v1[4] = {2.2, 4.4, 2.0, 5.0};
    double v2[3] = {2.2, 4.4, 2.0};

    const Polynomial p1(3, v1); //create a polynomial of degree 3
    const Polynomial p2(2, v2); //create a polynomial of degree 2

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;

    Polynomial p3(6.6);
    Polynomial p4(p1); //copy constructor

    cout << "p3 = " << p3 << endl;
    cout << "p4 = " << p4 << endl;

    /*****************************************************
    * TEST PHASE 1                                       *
    * Polynomial: operator=                              *
    ******************************************************/
    cout << "\nTEST PHASE 1\n";

    p4 = p4; //self-assignement
    cout << "p4 = " << p4 << endl;

    //coeficients of polynomials
    double v3[3] = {-1, 0, 1};
    Polynomial p5(2, v3);

    p3 = p4 = p5;

    cout << "p3 = " << p3 << endl;
    cout << "p4 = " << p4 << endl;
    cout << "p5 = " << p5 << endl;

    /*****************************************************
    * TEST PHASE 2                                       *
    * Polynomial: operator()                             *
    ******************************************************/
    cout << "\nTEST PHASE 2\n";

    cout << "p5(1) = " << p5(1) << endl;
    cout << "p1(3.3) = " << p1(3.3) << endl;

    /*****************************************************
    * TEST PHASE 3                                       *
    * Polynomial: isRoot                                 *
    ******************************************************/
    cout << "\nTEST PHASE 3\n";

    if (p5.isRoot(1))
        cout << "One is a root of " << p5 << endl;
    else
        cout << "One is a not root of " << p5 << endl;

    /*****************************************************
    * TEST PHASE 4                                       *
    * Polynomial: operator[]                             *
    ******************************************************/
    cout << "\nTEST PHASE 4\n";

    p4[2] = 8;  // Vill ersätta den 3:e positionen med en 8 som koefficient. HAR REDAN ETT VÄRDE INNAN 8an sätts, rensa den?
    cout << "p4 = " << p4 << endl;

    if ( fabs(p4[1]) < EPSILON ) //compare a double with zero
        cout << "Coefficient 1 of p4 is zero!\n";

    cout << "Coefficient zero of p1: " << p1[0] << endl;

    /*****************************************************
    * TEST PHASE 5                                       *
    * Polynomial: P1+P2                                  *
    ******************************************************/
    cout << "\nTEST PHASE 5\n";

    p4 = p1 + p2;
    cout << "p4 = " << p4 << endl << endl;

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p3 = " << p3 << endl;
    cout << "p1 + p3 + p2 = " << p1 + p3 + p2 << endl;

    //p1 + p2 = p4; //it should not compile
    //cout << "fel grejs = " <<p2 << endl;


    /*****************************************************
    * TEST PHASE 6                                       *
    * Polynomial: const+P and P+const                    *
    ******************************************************/
    cout << "\nTEST PHASE 6\n";

    p4 = 2.0 + p4;
    cout << "p4 = " << p4 << endl << endl;

    p4 = 0 + p4 + 3.3;
    cout << "p4 = " << p4 << endl << endl;

    /*****************************************************
    * TEST PHASE 7                                       *
    * Logarithm: constructors and operator<<             *
    ******************************************************/
    cout << "\nTEST PHASE 7\n";

    Log l0; //default constructor
    Log l1(p3+2, 2, 3, 10);
    Log l2(l1); //copy constructor

    cout << "l0 = " << l0 << endl;
    cout << "l1 = " << l1 << endl;
    cout << "l2 = " << l2 << endl;

    /*****************************************************
    * TEST PHASE 8                                       *
    * Logarithm: assignment operator                     *
    ******************************************************/
    cout << "\nTEST PHASE 8\n";

    Log l3(p4, 1, 1 , 2);

    l2 = l0 = l3;   // HÄr kanske vi har memory leaks? För vi har ingen assignment operator.

    //test that memory is not shared between expressions
    p4[0] = 2;

    cout << "p4 = " << p4 << endl;
    cout << "l0 = " << l0 << endl;
    cout << "l2 = " << l2 << endl;
    cout << "l3 = " << l3 << endl;

    /*****************************************************
    * TEST PHASE 9                                       *
    * Logarithm: operator()                              *
    ******************************************************/
    cout << "\nTEST PHASE 9\n";

    cout << "l1(1) = " << l1(1) << endl;
    cout << "l3(1) = " << l3(1) << endl;

    /*****************************************************
    * TEST PHASE 10                                      *
    * Logarithm: isRoot                                  *
    ******************************************************/
    cout << "\nTEST PHASE 10\n";

    const Log l4;

    if (l4.isRoot(1))
        cout << "One is a root of " << l4 << endl;
    else
        cout << "One is not a root of " << l4 << endl;


    /*****************************************************
    * TEST PHASE 11                                      *
    * Expressions: dynamic binding                       *
    ******************************************************/
    cout << "\nTEST PHASE 11\n";

    Polynomial p6(p4);
    Polynomial p7(p2);

    Expression *E[4] = {&p6, &l1, &p7, &l0};

    cout << "** evaluate " << endl;
    for(int i = 0; i < 4; i++)
    {
        cout << "(" << *E[i] << ")"
             << "(1) = " << (*E[i])(1) << endl;
    }

    cout << "\n** isRoot " << endl;
    for(int i = 0; i < 4; i++)
    {
        if (E[i]->isRoot(1))
            cout << "1 is a root of " << *E[i] << endl;
        else
            cout << "1 is not a root of " << *E[i] << endl;
    }


    return 0;
}
