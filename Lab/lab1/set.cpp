#include "set.h"

//Default constructor
Set::Set (){
    head = new Node(0, nullptr);
}

//Constructor creating a set
//from n integers in a non-sorted array a
Set::Set (int a[], int n){

    head = new Node(0, nullptr); //Vi skapar en tom lista.

    for(int i = 0; i < n; i++){
        Node *temp = head;

        // Går alltid vidare tills värdet är större än det som står i a[i], sorterar alltså där, lägger
        // största värdet sist.
			while(temp->next != nullptr && temp->next->value < a[i]){ //
            temp = temp->next; // Flytta temp till nästa nod.
        }
        Node* newNode = new Node(a[i], nullptr);
        newNode->next = temp->next; // Pekar om till där temp är, där högsta värdet alltså ska sättas in. Kopplar ihop noderna där fram
        temp->next = newNode;       // Kopplar ihop noderna där bak.
    }
}

//copy constructor
Set::Set (const Set &source){
   //Add code
   head = new Node(0, nullptr);

   //Behövs 2 tempnodes för att kopiera.
   Node *tempSource = source.head->next;    // Den som ska kopieras.
   Node *tempCopy = head;   // Vandringsnoden

   while(tempSource != nullptr){
        Node *newNode = new Node(tempSource->value, nullptr);
        tempCopy->next = newNode;
        tempCopy = newNode;         //Vandringsnoden

        tempSource = tempSource->next;
   }
}

//Destructor: deallocate all nodes
Set::~Set (){

    Node *temp = head->next;
    Node *prev = head;

    while(prev != nullptr){
        temp = prev->next;
        delete prev;
        // Iterera.
        prev = temp;
    }
}

//Test if set is empty
bool Set::empty () const{
    if(head->next == nullptr){
        return true;
    }
    return false;
}

//Return number of elements in the set
int Set::cardinality() const{
    int counter = 0;

    Node *temp = head->next;

    while(temp != nullptr){
        counter++;
        temp = temp->next;
    }
    return counter;
}

//Test if x is an element of the set
bool Set::member (int x) const{
    Node *temp = head->next;

    while(temp != nullptr){
        if(temp->value == x){ // Om hittar värdet returnera true.
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Subset, alltså att alla tal från den högra listan finns i den vänstra som man jämför med.
bool Set:: operator<=(const Set& b) const{ // Kollar om den vänstra är subset av den högra.

    Node *temp = head->next; // Vänstra listan.

    while(temp != nullptr) {
        if(!b.member(temp->value)){ // Om värden från vänstra inte finns i högra listan.
            return false;
        }
        temp = temp->next;
    }
    return true;
}


bool Set:: operator==(const Set& b) const{
    if(*this <= b && b <= *this){   // Om de är subset av varandra så är dem lika.
        return true;
    }
    return false;
}

bool Set:: operator<(const Set& b)  const{
    //Add code
    if(*this <= b && !(b == *this)){ // Subset och inte samma.
        return true;
    }
    return false;
}


//Set union
//Repeated values are not allowed
Set Set::operator+ (const Set& b) const{

    Node *temp = b.head->next; // högra listan.
    Node *tempSource = head->next; // vänstra listan.
    Set c;  // Nya listan med unionen.

    // Sätter allt från den vänstra listan temp in i nya listan c.
    while(tempSource != nullptr){
        Node *sortCheck = c.head;

        while(sortCheck->next != nullptr && sortCheck->next->value < tempSource->value) {
            sortCheck = sortCheck->next;
        }
        Node* newNode = new Node(tempSource->value, nullptr);
        newNode->next = sortCheck->next;
        sortCheck->next = newNode;
        tempSource = tempSource->next;
    }

    // Sätt in värden från högra listan in till nya listan c.
    while(temp != nullptr){

        // Lägg till den om siffran inte redan finns i c.
        if(!member(temp->value)){
            Node *sortCheck = c.head;

            while(sortCheck->next != nullptr && sortCheck->next->value < temp->value) {
                sortCheck = sortCheck->next;
            }
            Node* newNode = new Node(temp->value, nullptr);
            newNode->next = sortCheck->next;
            sortCheck->next = newNode;
        }
        temp = temp->next;
    }

    return c;
}

//Set intersection
Set Set::operator* (const Set& b) const{    // Kolla vilket value som finns i båda listorna, lägg det i en ny lista.

    Node *temp = b.head->next;
    Set c;

    while(temp != nullptr){
        if(member(temp->value)){
            Node *newNode = new Node(temp->value, nullptr);
            newNode->next = c.head->next;
            c.head->next = newNode;
        }
        temp = temp->next;
    }
    return c;
}

//Set difference
Set Set::operator- (const Set& b) const{ // b är högra listan.

    Node *source = head->next; // Vänstra listan.
    Set c;

    while(source != nullptr){

        if(!b.member(source->value)){ // Kolla om värden från vänstra listan finns i den högra.
            Node *temp = c.head;

            while(temp->next != nullptr && temp->next->value < source->value) {
                temp = temp->next;
            }

            Node* newNode = new Node(source->value, nullptr); // Lägger in vänstra listans värden.
            newNode->next = temp->next;
            temp->next = newNode;
        }
        source = source->next;
    }

    return c;
}

//set union with set {x}
Set Set::operator+(int x) const{

//    if(this->member(x)) {   // Kollar om x redan finns i listan.
//        return *this;
//    }

    Set c(*this);
    if(this->member(x)){
        return c;
    }

//******sort**************
    Node *temp = c.head;

    while(temp->next != NULL && temp->next->value < x) {
        temp = temp->next;
    }

    Node* newNode = new Node(x, NULL);
    newNode->next = temp->next;
    temp->next = newNode;
//******sort**************

    return c; //to be deleted
}

//set difference with set {x}
Set Set::operator-(int x) const{
    // Om inte finns i vänstra listan, ignorera talet. Som tex 99999 i vårt fall.
    if(!this->member(x)) {
        return *this;
    }

    Node *temp = head->next;
    Node *prev = head;

    while(temp != nullptr) {
        // När x hittats, flytta pointers och deallokera minne.
        if(temp->value == x){
            prev->next = temp->next; // Pekar om till noden efter den som tas bort.
            delete(temp);
            break;
        }

        temp = temp->next;
        prev = prev->next;
    }
    return *this; //to be deleted
}

//Assignment operator
const Set& Set::operator=(const Set &s){

    // Om de är samma, så gör inget.
    if(&s == this){
        return *this;
    }

    Node *temp = s.head->next; // Högra listan

    if(!s.empty()){
        Node *prevOld = head->next;
        Node *tempOld;

        while(prevOld != nullptr){
            tempOld = prevOld->next;
            delete prevOld;
            // Iterera.
            prevOld = tempOld;
        }
    }

    //head = new Node(0, nullptr); // Skapa ny lista(dummy node).
    Node *newTemp = head;

    while(temp != nullptr){
        Node *newNode = new Node(temp->value, nullptr);
        newTemp->next = newNode;

        newTemp = newNode; //vandrar ett steg nyskapade listan.
        temp = temp->next; //vandrar ett steg i s-listan.
    }
    return *this; //to be deleted
}

ostream& operator<< (ostream& os, const Set& theSet){
    if(theSet.empty()){
        cout << "The set is empty!";
    }
    else{
        Node *temp = theSet.head->next;

        while(temp != nullptr){
            cout << temp->value << " ";

            temp = temp->next;
        }
    }

    return os;
}

