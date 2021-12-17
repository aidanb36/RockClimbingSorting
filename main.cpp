//Aidan Brown
//CS 124
//Main for rock climbing route finder

#include <vector>
#include <iostream>
#include "project.h"
#include <iosfwd>
#include <algorithm>
#include "Selection.h"
//#include <algorithm>
//#include "Bubble2.h"
#include "SeparateChaining.h"
#include "LinearProbing.h"


string getNewKey(Climbing value) {
    return value.getLocation();
}

string getNewKey2(Climbing value2) {
    return value2.getRoute();
}

string intToString(int value) {
    return to_string(value);
}
//main
int main() {
    //create climbing vector
    std::vector<Climbing> destinations;
    //file name
    std::string fn = "../climbing2.csv";
    //using the file, use destinations vector to get size and values
    if (loadFromFile(fn, destinations)) {
        //use size to get the number of lines
        std::cout << destinations.size()
                  << " records read from file" << std::endl;
        //get the first pitch value, to show I can get the first
        int firstId = destinations.front().getPitches();
        std::cout << "The first number of pitches read was " << firstId << std::endl;
        //get last pitch value to show I can get the last value
        std::cout << "The last number of pitches read was " << destinations.at(999).getPitches() << std::endl;
    }

        //othewise, something went wrong
    else {
        std::cout << "Something went wrong" << std::endl;
    }


    //calculation for total number of pitches
    int count = 0;
    for (int i = 0; i < 1000; ++i) {
        //calculation on the vector
        int num = destinations.at(i).getPitches();
        count += num;
    }
    std::cout << "The average number of pitches is: " << count / 1000.0 << std::endl;

    //this prints the total number of pitches, the total of all 1000 routes
    std::cout << "The total number of pitches: " << count << std::endl;
    //keep in mind, a pitch is approximately 65 meters
    //using that, we can calculate how long, in meters, this combines too
    int meters = count * 65;
    //for miles, we can just divide the meters by 1609-
    std::cout << "In total, all these pitches accumulate to: " << meters << " meters... or " << meters / 1609
              << " miles" << endl;


    //each of these will be a hash table with separate chaining
    std::cout << "CHAINING" << endl;
    std::cout << "one" << endl;
    unsigned long tableSize = destinations.size();
    SeparateChaining<Climbing> hashSepChain(tableSize, getNewKey);
    for (int i = 0; i < destinations.size(); i++) {
        hashSepChain.insert(destinations.at(i));
    }
    std::cout << "two" << endl;

    //different size (+100)
    unsigned long tableSize1 = destinations.size() + 100;
    SeparateChaining<Climbing> hashSepChain1(tableSize1, getNewKey);
    for (int i = 0; i < destinations.size(); i++) {
        hashSepChain1.insert(destinations.at(i));
    }
    std::cout << "three" << endl;
    unsigned long tableSize2 = destinations.size() + 200;
    SeparateChaining<Climbing> hashSepChain2(tableSize2, getNewKey);
    for (int i = 0; i < destinations.size(); i++) {
        hashSepChain2.insert(destinations.at(i));
    }
    std::cout << "four" << endl;

    unsigned long tableSize3 = destinations.size() + 300;
    SeparateChaining<Climbing> hashSepChain3(tableSize3, getNewKey);
    for (int i = 0; i < destinations.size(); i++) {
        hashSepChain3.insert(destinations.at(i));
    }
    std::cout << "five" << endl;

    unsigned long tableSize4 = destinations.size() + 400;
    SeparateChaining<Climbing> hashSepChain4(tableSize4, getNewKey);
    for (int i = 0; i < destinations.size(); i++) {
        hashSepChain4.insert(destinations.at(i));
    }
    std::cout << "------" << endl;
    std::cout << "nonLin Probing" << endl;


    std::cout << "one " << endl;
    //linear
    NonLinearProbing<Climbing> hashLinPro(tableSize, getNewKey);
    for (int i = 0; i < destinations.size(); i++) {
        hashLinPro.insert(destinations.at(i));
    }
    std::cout << "two" << endl;

    NonLinearProbing<Climbing> hashLinPro1(tableSize1, getNewKey);
    for (int i = 0; i < destinations.size(); i++) {
        hashLinPro1.insert(destinations.at(i));
    }
    std::cout << "three" << endl;

    NonLinearProbing<Climbing> hashLinPro2(tableSize2, getNewKey);
    for (int i = 0; i < destinations.size(); i++) {
        hashLinPro2.insert(destinations.at(i));
    }
    std::cout << "four" << endl;

    NonLinearProbing<Climbing> hashLinPro3(tableSize3, getNewKey);
    for (int i = 0; i < destinations.size(); i++) {
        hashLinPro3.insert(destinations.at(i));
    }
    std::cout << "five" << endl;

    NonLinearProbing<Climbing> hashLinPro4(tableSize4, getNewKey);
    for (int i = 0; i < destinations.size(); i++) {
        hashLinPro4.insert(destinations.at(i));
    }
    std::cout << "done" << endl;


//with different hash functions
    std::cout<<"different hash Separate"<<endl;
    unsigned long tableSizeNew = destinations.size()+300;
    SeparateChaining<Climbing> hashSepChainNew(tableSizeNew, getNewKey);
    for (int i = 0; i < destinations.size(); i++) {
        hashSepChainNew.insert2(destinations.at(i));
    }

    std::cout<<"different hash nonLin"<<endl;

    NonLinearProbing<Climbing> hashLinProNew(tableSizeNew+100, getNewKey);
    for (int i = 0; i < destinations.size(); i++) {
        hashLinProNew.insert2(destinations.at(i));
    }

std::cout<<"different keys Separate"<<endl;
//with different getKeys
    unsigned long tableSizeNew2 = destinations.size()+300;
    SeparateChaining<Climbing> hashSepChainNew2(tableSizeNew2, getNewKey2);
    for (int i = 0; i < destinations.size(); i++) {
        hashSepChainNew2.insert(destinations.at(i));
    }
    std::cout<<"different keys nonLin"<<endl;

    NonLinearProbing<Climbing> hashLinProNew2(tableSizeNew2+100, getNewKey2);
    for (int i = 0; i < destinations.size(); i++) {
        hashLinProNew2.insert(destinations.at(i));
    }

    std::cout<<"different both Separate"<<endl;

//with both different
    unsigned long tableSizeNew3 = destinations.size()+300;
    SeparateChaining<Climbing> hashSepChainNew3(tableSizeNew3, getNewKey2);
    for (int i = 0; i < destinations.size(); i++) {
        hashSepChainNew3.insert2(destinations.at(i));
    }
    std::cout<<"different both nonLin"<<endl;

    NonLinearProbing<Climbing> hashLinProNew3(tableSizeNew3+100, getNewKey2);
    for (int i = 0; i < destinations.size(); i++) {
        hashLinProNew3.insert2(destinations.at(i));
    }
}



//    //print the layout of the header, because of the length of my data, i'm just using arrows to show the order
//    //and layout of the data beneath...one->two->three, like that
//    std::cout << std::endl;
//
//    std::cout << std::right
//              << std::setw(6) << "Route->"
//              << std::setw(6) << "Location->"
//              << std::setw(6) << "Stars->"
//              << std::setw(6) << "Rating->"
//              << std::setw(6) << "Pitches"
//              << std::right
//              << std::endl;


/** These are for the climbing objects (destinations)
 * I decided to just use ints for the following 100,200,....1000
 * for ease of randomization, but it does work for the objects as well.
 */
//    bubbleSort(destinations);
//    selectionSort(destinations);
//    heapSort(destinations);
//    twoSort(destinations);
//    quickSortStableRec(destinations);


//
//    //random vector size 100
//    std::srand(unsigned(std::time(nullptr)));
//    std::vector<int> v100(100);
//    std::generate(v100.begin(), v100.end(), std::rand);
//    //bubble
//    bubbleSort(v100);
//    //selection
//    selectionSort(v100);
//    //heap
//    heapSort(v100);
//    //twosort
//    twoSort(v100);
//    //quick
//    std::cout<<"-------"<<endl;
//    quickSortStableRec(v100);
//    std::cout<<"-------"<<endl;
//
//   //repeat the same process as above for all 10
//    std::vector<int> v200(200);
//    std::generate(v200.begin(), v200.end(), std::rand);
//    bubbleSort(v200);
//    selectionSort(v200);
//    heapSort(v200);
//    twoSort(v200);
//    std::cout<<"-------"<<endl;
//    quickSortStableRec(v200);
//    std::cout<<"-------"<<endl;
//
//
//
//
//    std::vector<int> v300(300);
//    std::generate(v300.begin(), v300.end(), std::rand);
//    bubbleSort(v300);
//    selectionSort(v300);
//    heapSort(v300);
//    twoSort(v300);
//    std::cout<<"-------"<<endl;
//    quickSortStableRec(v300);
//    std::cout<<"-------"<<endl;
//
//
//    std::vector<int> v400(400);
//    std::generate(v400.begin(), v400.end(), std::rand);
//    bubbleSort(v400);
//    selectionSort(v400);
//    heapSort(v400);
//    twoSort(v400);
//    std::cout<<"-------"<<endl;
//
//    quickSortStableRec(v400);
//    std::cout<<"-------"<<endl;
//
//
//    std::vector<int> v500(500);
//    std::generate(v500.begin(), v500.end(), std::rand);
//    bubbleSort(v500);
//    selectionSort(v500);
//    heapSort(v500);
//    twoSort(v500);
//    std::cout<<"-------"<<endl;
//
//    quickSortStableRec(v500);
//    std::cout<<"-------"<<endl;
//
//    std::vector<int> v600(600);
//    std::generate(v600.begin(), v600.end(), std::rand);
//    bubbleSort(v600);
//    selectionSort(v600);
//    heapSort(v600);
//    twoSort(v600);
//    std::cout<<"-------"<<endl;
//
//    quickSortStableRec(v600);
//    std::cout<<"-------"<<endl;
//
//    std::vector<int> v700(700);
//    std::generate(v700.begin(), v700.end(), std::rand);
//    bubbleSort(v700);
//    selectionSort(v700);
//    heapSort(v700);
//    twoSort(v700);
//    std::cout<<"-------"<<endl;
//
//    quickSortStableRec(v700);
//    std::cout<<"-------"<<endl;
//
//    std::vector<int> v800(800);
//    std::generate(v800.begin(), v800.end(), std::rand);
//    bubbleSort(v800);
//    selectionSort(v800);
//    heapSort(v800);
//    twoSort(v800);
//    std::cout<<"-------"<<endl;
//
//    quickSortStableRec(v800);
//    std::cout<<"-------"<<endl;
//
//
//    std::vector<int> v900(900);
//    std::generate(v900.begin(), v900.end(), std::rand);
//    bubbleSort(v900);
//    selectionSort(v900);
//    heapSort(v900);
//    twoSort(v900);
//    std::cout<<"-------"<<endl;
//
//    quickSortStableRec(v900);
//    std::cout<<"-------"<<endl;
//
//
//
//    std::vector<int> v1000(1000);
//    std::generate(v1000.begin(), v1000.end(), std::rand);
//    bubbleSort(v1000);
//    selectionSort(v1000);
//    heapSort(v1000);
//    twoSort(v1000);
//    std::cout<<"-------"<<endl;
//
//    quickSortStableRec(v1000);
//    std::cout<<"-------"<<endl;













