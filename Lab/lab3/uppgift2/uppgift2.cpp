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
// Declare.
typedef vector<string> anagrams;
typedef map<string, anagrams> anagramMap;
typedef pair<string, anagrams> thePair;

// Overload the ostream to display pairs.
namespace std{
    ostream& operator<<(ostream& os, const thePair &p){
        int nrWords = p.second.size();

        if(nrWords > 1){   // If the size is one, then the word only occurs once. Therefore don't display it.
            ostream_iterator<string> outputIterator(os, " ");   // Create the outstream iterator with space between each element.
            copy(p.second.begin(), p.second.end(), outputIterator); // Output the whole vector to show all anagrams.
            os << " --> " << nrWords << " words." << endl; // Display nr of words.
        }
        return os;
    }
}


int main(){
    // Declare the variables.
    anagramMap subjects;
    anagramMap::iterator it;
    string word = "";
    int counter = 0;
    ifstream is("H:/TNG033/2015/lab4/uppgift2/uppgift2_kort.txt"); // Create the in and out streams.
    ofstream os("H:/TNG033/2015/lab4/uppgift2/output.txt");

    // Display error message.
    if(!is){
        cout << "Data file not found!!" << endl;
        return 0;
    }

    // Read the words.
    while(is >> word){
        transform(word.begin(), word.end(), word.begin(), ::tolower); // Transform all to lower case.

        string sortWord = word; // Copy the string.
        sort(sortWord.begin(), sortWord.end()); // Sort the new string alphabetically.

        subjects[sortWord].push_back(word); // Push back/insert the word in the end of the vector.
        counter++;  // totalt hur många.
    }

    // Display the first general information.
    os << "Number of words = " << counter << endl;
    os << endl << "-- ANAGRAMS --" << endl;

    // Create the vector that we are going to display.
    vector<thePair> vectorDisplay(subjects.size());
    copy(subjects.begin(), subjects.end(), vectorDisplay.begin());  // Copy from the map to the vector "vectorDisplay".

    // Display the vector "vectorDisplay".
    copy(vectorDisplay.begin(), vectorDisplay.end(), ostream_iterator<thePair>(os));

    return 0;
}


