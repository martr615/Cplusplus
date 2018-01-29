#ifndef SET_H
#define SET_H

#include <iostream>

using namespace std;

#include "node.h"

class Set
{
public:

    //Default constructor
    Set ();

    //Constructor creating a set
    //from n integers in a non-sorted array a
    Set (int a[], int n);

    //copy constructor
    Set (const Set& b);

    //destructor
    ~Set ();

    //Assignment operator
    const Set& operator=(const Set& b);

    bool empty () const; //Test if set is empty
    int cardinality() const; //Return number of elements in the set
    bool member (int x) const; //Test if x is an element of the set


    //Overloaded operators
    // A new set is returned
    Set operator+ (const Set& b) const; //Set union
    Set operator* (const Set& b) const; //Set intersection
    Set operator- (const Set& b) const; //Set difference
    Set operator+(int x) const; //set union with set {x}
    Set operator-(int x) const; //set difference with set {x}

    //Overloaded comparison operators
    bool operator<=(const Set& b) const;
    bool operator==(const Set& b) const;
    bool operator<(const Set& b) const;


private:
    Node *head; //points to the first node
    //Note: first node is a dummy node of the list

    friend ostream& operator<< (ostream& os, const Set& b);

    /* Auxiliarly functions */

    void insert(int value); //insert a new value in a sorted list,
    //do not insert repeated values

    void del(int value);   //delete value from the list, if it exists
};


#endif
