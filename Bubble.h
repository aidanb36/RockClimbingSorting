# RockClimbingSorting
This C++ project takes the 1000 top rated rock climbing routes across the United States and sorts and manages the data using data structures and algorithms.
//
// Created by aidan on 11/4/2021.
//

#ifndef ROCKCLIMB_BUBBLE_H
#define ROCKCLIMB_BUBBLE_H
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

template<typename Comparable>
void printVec(const vector<Comparable> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i != 0) {
            cout << ", ";
        }
        cout << v[i];
    }
    cout << endl;
}

template<typename Comparable>
void bubbleSort(vector<Comparable> vec) {
    bool haveSwapped = true;
    int maxIndex = vec.size();
    int reads = 0;
    int writes  = 0;
    Comparable temp;
    while (haveSwapped) {
        haveSwapped = false;
        for (int i = 0; i + 1 < maxIndex; ++i) {
            // Compare items at indices i and i+1 and swap if necessary
            if (vec[i] > vec[i+1]) {
                reads++;
                reads++;
                temp = vec[i];
                reads++;
                writes++;
                vec[i] = vec[i+1];
                writes++;
                vec[i+1] = temp;
                reads++;
                writes++;
                // Update haveSwapped
                haveSwapped = true;
            }
        }
        // Update maxIndex
        --maxIndex;

    }
    std::cout<<reads<<"  "<<writes<<endl;
}

//int main() {
//    vector<int> numbers = {3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
//    printVec(numbers);
//    bubbleSort(numbers);
//    return 0;
//}
#endif //ROCKCLIMB_BUBBLE_H
