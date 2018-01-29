#ifndef NODE_H
#define NODE_H

//DO NOT MODIFY

#include <iostream>

using namespace std;

class Set;

class Node
{
    public:
       Node (int, Node*);  // Constructor

    private:
       int value;
       Node* next;

       friend ostream& operator<< (ostream &os, const Set &theSet);
       friend class Set;
};

#endif


