/**********************************************************
* Erin Yilmaz
* Homework 5
* Comp 15
* sortAlgs.cpp
*
* Contains the function definitions (implementation) for the
* sorts declared in "sortAlgs.h." Also contains definitions for
* private helper functions
*********************************************************/
#include <vector>
#include <iostream>
#include <cmath>

#include "sortAlgs.h"

using namespace std;


// Function: isSorted
// Parameters: a reference to a vector of numbers
// Returns: true if the numbers are sorted in ascending order
// Does: iterates through the vector and checks if each element is at most the
// same value as the value after it
bool isSorted(vector<int> &numbers) {
    for (unsigned i = 0; i < numbers.size() - 2; i++) {
        if (numbers.at(i) > numbers.at(i + 1))
            return false;
    }
    return true;
}

// Function: countDigits
// Parameters: an integers
// Returns: the number of digits in the integer
// Does: counts the number of digits in the parameter
int countDigits(int max) {
    if (max == 0) 
        return 1;
    int count = 0;
    while (max != 0) { 
        max = max / 10; 
        ++count; 
    } 
    return count; 
}

// Function: insertionSort
// Parameters: a reference to a vector of numbers
// Returns: void
// Does: sorts the numbers in the vector in place 
void insertionSort(vector<int> &numbers) {
    int currIndex = 1;
    for (unsigned divider = 1; divider < numbers.size(); divider++) {
        currIndex = divider;
        for (int temp = numbers.at(currIndex); currIndex >= 1 && temp < 
            numbers.at(currIndex - 1); currIndex--) {
            numbers.at(currIndex) = numbers.at(currIndex - 1);
            numbers.at(currIndex - 1) = temp;
        }
    }
}


// Function: emptyBins
// Parameters: a reference to a vector of numbers and the vectors of bins for
// each digit
// Returns: void
// Does: removes the numbers from the bins and puts them back into the numbers
// vector
void emptyBins(vector<int> &binZero, vector<int> &binOne, vector<int> &binTwo,
    vector<int> &binThree, vector<int> &binFour, vector<int> &binFive, 
    vector<int> &binSix, vector<int> &binSeven, vector<int> &binEight,
    vector<int> &binNine, vector<int> &numbers) {
    while (! binZero.empty()) {
        numbers.insert(numbers.end(), binZero.at(0));
        binZero.erase(binZero.begin());
    }
    while (! binOne.empty()) {
        numbers.insert(numbers.end(), binOne.at(0));
        binOne.erase(binOne.begin());
    }
    while (! binTwo.empty()) {
        numbers.insert(numbers.end(), binTwo.at(0));
        binTwo.erase(binTwo.begin());
    }
    while (! binThree.empty()) {
        numbers.insert(numbers.end(), binThree.at(0));
        binThree.erase(binThree.begin());
    }
    while (! binFour.empty()) {
        numbers.insert(numbers.end(), binFour.at(0));
        binFour.erase(binFour.begin());
    }
    while (! binFive.empty()) {
        numbers.insert(numbers.end(), binFive.at(0));
        binFive.erase(binFive.begin());
    }
    while (! binSix.empty()) {
        numbers.insert(numbers.end(), binSix.at(0));
        binSix.erase(binSix.begin());
    }
    while (! binSeven.empty()) {
        numbers.insert(numbers.end(), binSeven.at(0));
        binSeven.erase(binSeven.begin());
    }
    while (! binEight.empty()) {
        numbers.insert(numbers.end(), binEight.at(0));
        binEight.erase(binEight.begin());
    }
    while (! binNine.empty()) {
        numbers.insert(numbers.end(), binNine.at(0));
        binNine.erase(binNine.begin());
    }
}

// Function: fillBins
// Parameters: a reference to a vector of numbers and the vectors of bins for
// each digit, the digit to be inserted, and an empty spot in the numbers array
// Returns: void
// Does: puts the appropriate digit in the appropriate bin
void fillBins(vector<int> &binZero, vector<int> &binOne, vector<int> &binTwo,
    vector<int> &binThree, vector<int> &binFour, vector<int> &binFive, 
    vector<int> &binSix, vector<int> &binSeven, vector<int> &binEight,
    vector<int> &binNine, vector<int> &numbers, int digit, int i) {
    if (digit == 0)
        binZero.push_back(numbers.at(i));
    else if (digit == 1)
        binOne.push_back(numbers.at(i));
    else if (digit == 2)
        binTwo.push_back(numbers.at(i));
    else if (digit == 3)
        binThree.push_back(numbers.at(i));
    else if (digit == 4)
        binFour.push_back(numbers.at(i));
    else if (digit == 5)
        binFive.push_back(numbers.at(i));
    else if (digit == 6)
        binSix.push_back(numbers.at(i));
    else if (digit == 7)
        binSeven.push_back(numbers.at(i));
    else if (digit == 8)
        binEight.push_back(numbers.at(i));
    else
        binNine.push_back(numbers.at(i));
}

// Function: radixSort
// Parameters: a reference to a vector of numbers
// Returns: void
// Does: sorts the numbers with radix sort
void radixSort(vector<int> &numbers) {
    vector<int> binZero, binOne, binTwo, binThree, binFour, binFive, binSix;
    vector<int> binSeven, binEight, binNine;
    int digit, max, maxDigits;
    max = numbers.at(0);
    maxDigits = 1;
    //gets the last digit and puts the number in the appropriate bin
    //finds the maximum number to be sorted and calculates its number of digits
    //in maxDigits. This is the number of times we will have to do this 
    //bin sorting process/loop
    for (int digitPlace = 1; digitPlace <= maxDigits; ++digitPlace) {
        for (unsigned i = 0; i < numbers.size(); i++) {
            int oldDigitPlace = digitPlace;
            int truncateNum = numbers.at(i);
            while (digitPlace != 0) {
                digit = truncateNum % 10;
                truncateNum = truncateNum / 10;
                digitPlace--;
            }
            digitPlace = oldDigitPlace;
            if (numbers.at(i) > max)
                max = numbers.at(i);
            fillBins(binZero, binOne, binTwo, binThree, binFour, binFive,
            binSix, binSeven, binEight, binNine, numbers, digit, i);
        }
        maxDigits = countDigits(max);
        numbers.clear();
        emptyBins(binZero, binOne, binTwo, binThree, binFour, binFive, binSix,
        binSeven, binEight, binNine, numbers);
    }
}

// Function: assign_gap
// Parameters: a positive number
// Returns: the new gap
// Does: returns half of the parameter if it is even, and 1 + half if it is odd
size_t assign_gap(size_t num) {
    if (num % 2 == 0)
        return num / 2;
    return (num / 2) + 1;
}


// Function: shellSort
// Parameters: a reference to a vector of numbers
// Returns: void
// Does: sorts the vector with shell sort
void shellSort(vector<int> &numbers) {
    int temp, j;
    size_t gap = assign_gap(numbers.size());
    while (gap > 0) {
        for (size_t i = 0; i < numbers.size() - gap; ++i) {
            if (numbers.at(gap + i) < numbers.at(i)) {
                temp = numbers.at(i);
                numbers.at(i) = numbers.at(gap + i);
                numbers.at(gap + i) = temp;
                if (i != 0 && gap == 1) {
                    j = i;
                    while (numbers.at(j) < numbers.at(j - 1)) {
                        temp = numbers.at(j);
                        numbers.at(j) = numbers.at(j - 1);
                        numbers.at(j - 1) = temp;
                        j--; }
                }
            }
        }
        if (gap == 1)
            return;
        gap = assign_gap(gap);
    }
}
