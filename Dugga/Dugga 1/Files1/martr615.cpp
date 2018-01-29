/*****************************************************************************
* TNG033: Dugga 1                                                            *
* Name and LiU id: Martin Tran (martr615)                                    *
* Personal Number: 930201-5615                                               *
* ****************************************************************************/

#include <iostream>
#include <string> //access string
#include <sstream> //istringstream

using namespace std;

/****************************************
* Class Data_Vector                     *
*****************************************/

//Sequence of labeled data elements
class Data_Vector
{
public:

        //constructors
        Data_Vector(); //default constructor
        Data_Vector(double* v, string* l, int n); //v = values, l = labels, n = size
        Data_Vector(const Data_Vector& d); //copy constructor

        //destructor
        ~Data_Vector();

        //function definition
        bool isEmpty() const ; //check if Data vector is empty
        int newSize(const Data_Vector& rhp) const; //return new size for d1+d2 operations
        Data_Vector slice(const string word) const; //Return data elements associated with the given label

        //overloading operators
        const Data_Vector& operator=(const Data_Vector& d); //assignment operator=
        const Data_Vector& operator+=(const Data_Vector& rhp); //Assignment operator+=
        const Data_Vector operator+(const Data_Vector& rhp) const; //overload operator+
        double& operator[](const string word) const; //subscript operator that return a double associated with the correct label

        /* AIDA VILL ATT MAN SKRIVER SÅHÄR ANNARS FÅR MAN FEL
        double operator[](const string& word) const;
        */

        //product of a Data_Vector
        Data_Vector operator*(const double k) const; //dv*k
        friend Data_Vector operator*(const double k, const Data_Vector& d); //k*dv

        //stream insertion operator "<<"
        friend ostream& operator<<(ostream &os, const Data_Vector& D);

private:
        double *value;
        string *label;
        int n_size;

};

/****************************************
* Implementation of class Data_Vector   *
*****************************************/

//default constructor
Data_Vector::Data_Vector()
{
    n_size = 0;
    value = nullptr;
    label = nullptr;
}


//overload constructor
Data_Vector::Data_Vector(double* v, string* l, int n)
{
    n_size = n;
    value = nullptr;
    label = nullptr;

    if(n) //if n is not zero
    {
        //allocate space for the array that stores values respective labels
        value = new double[n_size];
        label = new string[n_size];

        //initialize the vectors value and label
        for(int i = 0; i < n_size; i++)
        {
            value[i] = v[i];
            label[i] = l[i];
        }
    }
}
//copy constructor
//is needed to allocate memory or it will be leaks
Data_Vector::Data_Vector(const Data_Vector& d)
{
    n_size = d.n_size;
    value = nullptr;
    label = nullptr;

    if(n_size)
    {
        //allocate space for the double array and string array
        value = new double[n_size];
        label = new string[n_size];

        //copy the values and labels
        for(int i = 0; i< n_size; i++)
        {
            value[i] = d.value[i];
            label[i] = d.label[i];
        }
    }
}

//Destructor
Data_Vector::~Data_Vector()
{
    //remove the dynamically allocated memory
    delete [] value;
    delete [] label;
}

//test if data_vector has zero data elements
bool Data_Vector::isEmpty() const
{
    Data_Vector temp(*this);

    if(temp.n_size == 0)
    {
        return true;
    }

    return false;
}

int Data_Vector::newSize(const Data_Vector& rhp) const
{
    //n_size is this and rhp is rhp sent in from operator parameter
    int _size = n_size + rhp.n_size; //the sum of size for the data vectors
    int n_common = 0;
    int new_nSize = 0;


    for(int i = 0; i < n_size; i++) //loop through lhp (*this)
    {
        for(int j = 0; j < rhp.n_size; j++) //compare lhp with rhp
        {
            if(label[i] == rhp.label[j]) //if same word
            {
                n_common++; //iterate when they have the same label
            }
        }
    }

    new_nSize = _size - n_common; //unique labels

    return new_nSize;
}

//assignment operator
const Data_Vector& Data_Vector::operator=(const Data_Vector& d)
{
    //d is dv2 since dv2 = right half plane (if we consider phase 2)
    //*this is dv4 since it left half plane
    //dv4 and dv2 is already an object
    //we need to deallocate space from dv4 before we assign it to dv2

    n_size = d.n_size;
    delete [] value;  //deallocate from dv4 since it wont be needed anymore
    delete [] label; //deallocate from dv4 since it wont be needed anymore

    value = new double[n_size];
    label = new string[n_size];

    for(int i = 0; i<n_size; i++)
    {
        value[i] = d.value[i];
        label[i] = d.label[i];
    }

    return *this;
}

//overload subscript operator
//Since i'm returning a double, increment should work fine in main
//hence dv4["Pressure"]++; works without writing a operator++ for postfix
//And since posfix operator++ was not mentioned on the dugga task I assume this is ok.
double& Data_Vector::operator[](const string word) const
{
    int counter = 0; //To find the corresponding place of label with its data element

    //n_size is taken from *this, same with label and value
    for(int i = 0; i<n_size; i++)
    {
        if(label[i] == word)
        {
            break;
        }
        counter++;
    }

    return value[counter];
}

//overloading operator+
const Data_Vector Data_Vector::operator+(const Data_Vector& rhp) const
{
    int new_nSize = newSize(rhp); //call function newSize to find unique labels corresponding to the two data vectors
    int counter = 0;

    Data_Vector newDataVector; //newDataVector is default object of data_vector

    newDataVector.n_size = new_nSize;
    //allocate space for the new data vector
    newDataVector.value = new double[new_nSize];
    newDataVector.label = new string[new_nSize];

    //we want to loop through lhp first since we want to add the labels on
    //the left half plane into the new Data_Vector according to the Dugga task.
    for(int i = 0; i < n_size; i++)
    {
        bool isRepeated = false;
        newDataVector.label[i] = label[i]; //assign lhp:s label to the new Data_Vector

        for(int j = 0; j < rhp.n_size; j++) //first spot on lhp loop through rhp
        {
            if(label[i] == rhp.label[j]) //if lhp:s label is the same as rhp:s label add the value
            {
                newDataVector.value[i] = value[i] + rhp.value[j]; //add if same label
                isRepeated = true;
            }
        }

        if(isRepeated == false){ //init value without adding anything extra if not same label
            newDataVector.value[i] = value[i];
        }
    }

    //loop through the remaining labels and add to the new data vector
    for(int i = 0; i < rhp.n_size; i++)
    {
        bool isRepeat = false;

        for(int j = 0; j < n_size; j++)
        {
            if(rhp.label[i] == label[j]) //do nothing if same label since it has already been added
            {
                isRepeat = true;
            }
        }

        if(isRepeat == false) //only add unique label and its respective value
        {
            //save it in the position where it last ended and increment for every loop
            newDataVector.value[n_size+counter] = rhp.value[i];
            newDataVector.label[n_size+counter] = rhp.label[i];
            counter++;
        }
    }

    return newDataVector;
}

//operator+=
const Data_Vector& Data_Vector::operator+=(const Data_Vector& rhp)
{
    //dv4 is *this in case 4
    *this = *this + rhp; //make use of operator+ so it wont be repetitive code
    return *this;
}


//function slice
Data_Vector Data_Vector::slice(const string word) const
{

    istringstream iss(word);
    string theWord;
    int nr_size = 0;


    //The sentence that slice function receive is limited to n_size white spaces.
    //for longer sentences replace n_size with a larger value.
    //Allocate space for the temporary initialized arrays of string and double to save
    //the corresponding words in the sentence that match the labels in the data vector
    string* tempWords = new string[n_size];
    double* tempValues = new double[n_size];

    //iss split the string into words by separating ws
    while(iss>>theWord)
    {
        for(int i = 0; i<n_size; i++)
        {
           if(theWord == label[i]) //if theWord is a word on the vector
            {
                tempWords[nr_size] = label[i]; //assign the word
                tempValues[nr_size] = value[i]; //assign the value
                nr_size++;  //iterate for every found word
            }
        }
    }

    //initialize new data vector
    Data_Vector newDataVector;

    newDataVector.n_size = nr_size; //the size is according to found matches
    //allocate space for the double array and string array
    newDataVector.value = new double[nr_size];
    newDataVector.label = new string[nr_size];

    //assign data element associated with the given label
    //for the new Data_Vector
    for(int i = 0; i<nr_size; i++)
    {
        newDataVector.label[i] = tempWords[i];
        newDataVector.value[i] = tempValues[i];
    }

    //remove the dynamically allocated memory for the temporary pointers
    //that are not needed anymore.
    delete [] tempWords;
    delete [] tempValues;

    return newDataVector;
}

//product, dv*k
Data_Vector Data_Vector::operator*(const double k) const
{
    //if an empty dv the loop wont start
    //hence an empty dv is returned
    for(int i = 0; i<n_size; i++)
    {
        value[i] *= k;
    }

    return *this;
}

//product, k*dv
Data_Vector operator*(const double k, const Data_Vector& d)
{
    //if d is empty data_vector then the loop wont start
    //hence an empty dv is returned
    for(int i = 0; i < d.n_size; i++)
    {
        d.value[i] = d.value[i] * k;
    }

    return d;
}

//overload output operator to display
ostream& operator<<(ostream&os, const Data_Vector& D)
{

    if(D.n_size == 0)
    {
        os<<"<:>";
        return os;
    }

    os << "<";

    //loop to the next to last spot because we want to end with ">"
    for(int i = 0; i< D.n_size-1; i++)
    {
        os << D.label[i] << ":" << D.value[i] << ", ";
    }

    //display the last spot and end with ">"
    os << D.label[D.n_size-1] << ":" << D.value[D.n_size-1] << ">";

    return os;
}


/*******************************
* MAIN: deliver unmodified     *
********************************/

int main()
{
    /*************************************
    * TEST PHASE 0                       *
    * Constructor, operator<<, isEmpty   *
    **************************************/
    cout << "\nTEST PHASE 0: Constructor, operator<<, and isEmpty \n" << endl;

    string labels1[] = { "Temperature", "Height", "Weight", "Pressure"};
    string labels3[] = { "Temperature", "Age", "Pressure", "Duration"};

    double values1[] = { 38, 2.70, 50, 12.2 };
    double values2[] = { 10, 2, 0.5, 0 };
    double values3[] = { 10, 1.5, 0.5, 120 };

    Data_Vector dv0; //empty data vector
    Data_Vector dv1(values1, labels1, 4);
    Data_Vector dv2(values2, labels1, 4);
    Data_Vector dv3(values3, labels3, 4);
    Data_Vector dv4(values3, labels3, 1);

    cout << "DV0 = " << dv0 << endl;
    cout << "DV1 = " << dv1 << endl;
    cout << "DV2 = " << dv2 << endl;
    cout << "DV3 = " << dv3 << endl;
    cout << "DV4 = " << dv4 << endl;

    if (dv0.isEmpty())
        cout << "\nData vector DV0 is empty!!" << endl;

    /*************************************
    * TEST PHASE 1                       *
    * Copy constructor                   *
    **************************************/
    cout << "\nTEST PHASE 1: copy constructor\n" << endl;

    const Data_Vector dv5(dv3);

    cout << "DV5 = " << dv5 << endl;

    /*************************************
    * TEST PHASE 2                       *
    * Assignment operator                *
    **************************************/
    cout << "\nTEST PHASE 2: operator=\n" << endl;

    dv4 = dv2;

    cout << "DV2 = " << dv2 << endl;
    cout << "DV4 = " << dv4 << endl;

    /*************************************
    * TEST PHASE 3                       *
    * Subscript operator: operator[]     *
    **************************************/
    cout << "\nTEST PHASE 3: operator[]\n" << endl;

    dv4["Pressure"]++;

    cout << "DV4 = " << dv4 << endl;

    if (dv5["Age"] < 4)
        cout << "dv5 Age < 4" << endl;

    /*************************************
    * TEST PHASE 4                       *
    * operator+ and +=                   *
    **************************************/
    cout << "\nTEST PHASE 4: + and +=\n" << endl;

    dv4 = dv1 + dv2 + dv0;

    cout << "DV4 = " << dv4 << endl;
    cout << "DV1+DV3 = " << dv1+dv3 << endl;
    cout << "DV3+DV1 = " << dv3+dv1 << endl;

    dv4 += (dv5+dv1); //same as dv3+dv1

    cout << "DV4 = " << dv4 << endl;

    /*************************************
    * TEST PHASE 5                       *
    * slice                              *
    **************************************/
    cout << "\nTEST PHASE 5: slice\n" << endl;

    cout << dv4.slice("Height Age Weight") << endl;

    dv4 = dv5.slice("Speed Color"); //empty data vector

    cout << "DV4 = " << dv4 << endl;

    cout << dv4.slice("Color") << endl; //empty data vector

    /*************************************
    * TEST PHASE 6                       *
    * operator*                          *
    **************************************/
    cout << "\nTEST PHASE 6: operator*\n" << endl;

    cout << "2*DV4 = " << 2 * dv4 << endl;

    dv4 = dv5 * 2;

    cout << "DV4 = " << dv4 << endl;

    cout << "\nBye ..." << endl;

    return 0;
}

