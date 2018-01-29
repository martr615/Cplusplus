#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include <iostream>
#include <iterator>

using namespace std;
// Declaring.
typedef map<string, int> theMap;
typedef pair<string, int> thePair;  // To use when displaying.
const string punctuations = ".,!?:\"();";   // Used when removing punctuations.

// Function declarations.
bool removePunctuations(char c);
bool sortVector(const thePair p1, const thePair p2);

// Sort the vector. Used when sorting by frequency.
bool sortVector(const thePair p1, const thePair p2){
    return (p1.second > p2.second);
}

// Removes unwanted punctuations.
bool removePunctuations(char c){
    // If we have reached the end of "punctuations", return true. It means no weird chars were found.
    return ( (find(punctuations.begin(), punctuations.end(), c)) == punctuations.end() );

}

// Overloading the outstream to display pairs.
namespace std{
    ostream& operator<<(ostream& os, const thePair& p1){
        os << left << setw (20) << p1.first << p1.second << endl;
        return os;
    }
}


int main(){
    // Declare the variables.
    theMap mapWords;    // Create the map.
    string word = "";
    int counter = 0;    // Count total
    ifstream is("H:/TNG033/2015/lab4/uppgift1/uppgift1.txt");    // Set up the input and output streams.
    ofstream os("H:/TNG033/2015/lab4/uppgift1/output.txt");

    // Error message.
    if(!is){
        cout << "Data file not found!!" << endl;
        return 0;
    }

    // Read the words.
    while(is >> word){
        transform(word.begin(), word.end(), word.begin(), ::tolower); //Transform all to lowercase ::tolower

        string newWord; // Will store the new word here.
        newWord.reserve(word.size());   // Allocate space for it.
                                                                                       // back_inserter är för vi sätter en char i taget, därför vill vi sätta den längst bak.
        copy_if(word.begin(), word.end(), back_inserter(newWord), removePunctuations); // Copy only if "removePunctuations" returns true.

        mapWords[newWord]++;  // Insert the newWord at it's place (key) in the map. Add one to the frequency there.
        counter++;  // Add to the "total nr of words"-counter.
    }

    // Display the first information.
    os << "Number of words in the file = " << counter << endl;
    int nrUniqueWords = distance(mapWords.begin(), mapWords.end()); // Counts how many elements in the map.
    os << "Number unique  words in the file = " << nrUniqueWords << endl;

    // Display the map alphabetically.
    os << endl << "Frequency table sorted alphabetically ..." << endl << endl;
    copy(mapWords.begin(), mapWords.end(), ostream_iterator<thePair>(os));

    // Creating a new vector sorted by frequency.
    vector<thePair> frequency(mapWords.size());  // Empty vector of type pair.
    copy(mapWords.begin(), mapWords.end(), frequency.begin());  // Copy the mapWords vector.
    sort(frequency.begin(), frequency.end(), sortVector);    // Sort it.

    // Display the map by frequency.
    os << endl << "Frequency table sorted by frequence ..." << endl << endl;
    copy(frequency.begin(), frequency.end(), ostream_iterator<thePair>(os));   // Display the table sorted by frequency.

    return 0;
}
