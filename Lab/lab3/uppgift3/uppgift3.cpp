#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <set>  // Set sorterar automatiskt vid insert, ignorerar dubletter.

using namespace std;

// Declare.
typedef set<string> anagrams;
typedef map<string, anagrams> anagramMap;
typedef pair<string, anagrams> thePair;

bool sortBySize(const thePair p1, const thePair p2);

// Sort the vector by size.
bool sortBySize(const thePair p1, const thePair p2){
    return ( p1.second.size() > p2.second.size() );
}

// Overloading the out stream to display pairs.
namespace std{
    ostream& operator<<(ostream& os, const thePair &p){
        int nrWords = p.second.size();

        // Display the pairs with the iterator.
        copy(p.second.begin(), p.second.end(), ostream_iterator<string> (os, " "));
        os << " --> " << nrWords << " words." << endl;

        return os;
    }
}



int main(){
    // Declare the variables.
    anagramMap subjects;
    string word = "";
    int counter = 0;
    ifstream is("H:/TNG033/2015/lab4/uppgift3/uppgift3_kort.txt");
    ofstream os("H:/TNG033/2015/lab4/uppgift3/output.txt");

    // Display error message.
    if(!is){
        cout << "Data file not found!!" << endl;
        return 0;
    }

    // Read the words.
    while(is >> word){
        transform(word.begin(), word.end(), word.begin(), ::tolower); // Transform all to lower case.

        string sortedWord = word; // Copy the string.
        sort(sortedWord.begin(), sortedWord.end()); // Sort the new string alphabetically.

        // Insert the word at the index (key) for the sorted string "sortedWord".
        subjects[sortedWord].insert(word);  // Bytte från vektor till set här, så istället för "pushback" är det "insert" nu.
        counter++;
    }

    // Display first general information.
    os << "Number of words = " << counter << endl;
    os << endl << "--ANAGRAMS--" << endl;

    // Create, copy and sort the vector to display.
    vector<thePair> sortedVector(subjects.size());
    copy(subjects.begin(), subjects.end(), sortedVector.begin());
    sort(sortedVector.begin(), sortedVector.end(), sortBySize);

    // Display the vector "sortedVector".
    copy(sortedVector.begin(), sortedVector.end(), ostream_iterator<thePair>(os));

    return 0;
}
