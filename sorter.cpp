/**********************************************************
* Erin Yilmaz
* Homework 5
* Comp 15
* sorter.cpp
*
* This file contains main and checks command line arguments. It calls the
* functions from "sortAlgs.h" and sends the sorted result to the specified
* output location (cout or output file)
*********************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>

#include "sortAlgs.h"

using namespace std;

bool check_args(int argc, char *argv[]);
void interactive(vector<int> &numbers);
void automatic(vector<int> &numbers, string filename);
void call_sorter(vector<int> &numbers, string sortAlg);
void coutput(vector<int> &numbers);
void outfileOutput(vector<int> &numbers, int argc, char *argv[]);
string name_file(size_t numElem, int argc, char *argv[]);


int main(int argc, char *argv[]) {
    if (!check_args(argc, argv))
        exit(1);
    vector<int> numbers;
    if (argc == 3)
        interactive(numbers);
    else
        automatic(numbers, argv[3]);
    if (numbers.size() == 0)
        return 0;
    if (numbers.size() > 1)
        call_sorter(numbers, argv[1]);
    if (strcmp(argv[2], "--print") == 0)
        coutput(numbers);
    else
        outfileOutput(numbers, argc, argv);
    return 0;
}

// Function: outfileOutput
// Parameters: saves the sorted list to a file
// Returns: void
// Does: iterates through the vector and prints the sorted list to a file that
// it creates
void outfileOutput(vector<int> &numbers, int argc, char *argv[]) {
    ofstream outfile;
    outfile.open(name_file(numbers.size() - 1, argc, argv));
    if (!outfile || !outfile.is_open()) {
        cerr << "Error opening outfile\n";
        return;
    }
    if (argc == 3) {
        for (size_t i = 0; i < numbers.size(); i++)
            outfile << numbers.at(i) << endl;
    }
    else {
        for (size_t i = 0; i < numbers.size() - 1; i++)
            outfile << numbers.at(i) << endl;
    }
    outfile.close();
}

// Function: Name file
// Parameters: creates the name of the file the list will be printed to
// Returns: the filename
// Does: finds and concatenates the list origin, sorting algorithm number, and
// number of elements that were sorted
string name_file(size_t numElem, int argc, char *argv[]) {
    string ListOrigin, SortAlg, NumElements;
    if (argc == 3) 
        ListOrigin = "cin";
    else 
        ListOrigin = argv[3];
    if (strcmp(argv[1], "-s1") == 0)
        SortAlg = "1";
    else if (strcmp(argv[1], "-s2") == 0)
        SortAlg = "2";
    else
        SortAlg = "3";
    if (argc != 3)
        NumElements = to_string(numElem);
    else NumElements = to_string(numElem + 1);
    return ListOrigin + "_" + SortAlg + "_" + NumElements + "_sorted.txt";
}


// Function: Coutput
// Parameters: prints the sorted list to cout
// Returns: void
// Does: iterates through the vector and prints the sorted list to terminal
void coutput(vector<int> &numbers) {
    for (size_t i = 0; i < numbers.size(); i++)
        cout << numbers.at(i) << endl;
}

// Function: Automatic
// Parameters: the vector of unsorted numbers as a reference and the name of
// the file to read in from
// Returns: void
// Does: reads the numbers to be sorted from an input file and fills the vector
void automatic(vector<int> &numbers, string filename) {
    ifstream infile;
    infile.open(filename);
    if (! infile.is_open()) {
        cerr << "Error opening input file.\n";
        return;
    }
    int numtoadd;
    while (! infile.eof()) {
        infile >> numtoadd;
        numbers.push_back(numtoadd);
    }
    infile.close();
}


// Function: Interactive
// Parameters: the vector of unsorted numbers as a reference
// Returns: void
// Does: reads the numbers to be sorted from cin and fills the vector
void interactive(vector<int> &numbers) {
    int num;
    cin >> num;
    while (!cin.fail()) {
        numbers.push_back(num);
        cin >> num;
    }
}

// Function: Call sorter
// Parameters: calls the appropriate sorting function from sortAlgs.h
// Returns: void
// Does: calls the sorting algorithm specified on the command line
void call_sorter(vector<int> &numbers, string sortAlg) {
    if (sortAlg == "-s1")
        insertionSort(numbers);
    else if (sortAlg == "-s2")
        radixSort(numbers);
    else
        shellSort(numbers);
    return;
}


// Function: Check_args
// Parameters: the number of command line arguments and the array containing
// them
// Returns: true if arguments meet requirements, false otherwise
// Does: checks that main received the correct number of valid arguments
bool check_args(int argc, char *argv[]) {
    bool correctArgs = true;
    if (argc != 4 && argc != 3)
        correctArgs = false;
    else if (strcmp(argv[1], "-s1") != 0 && strcmp(argv[1], "-s2") != 0 && 
        strcmp(argv[1], "-s3")) {
        correctArgs = false;
    }
    else if (strcmp(argv[2],"--print") != 0 && strcmp(argv[2], "--save") != 0)
        correctArgs = false;
    if (correctArgs == false) {
        cerr << "Usage: sorter sortAlg outputMode [fileName]\n";
        cerr << "       where: sortAlg is -s1 -s2 or -s3\n";
        cerr << "       and outputMode is --print or --save\n";
        return false;
    }
    return true;
}
