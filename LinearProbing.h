//
// Created by aidan on 11/19/2021.
//

#ifndef ROCKCLIMB_LINEARPROBING_H
#define ROCKCLIMB_LINEARPROBING_H

#include <functional>
#include <string>
#include <vector>
using std::function, std::string, std::vector;

#include <optional>
using std::optional;
using std::nullopt;
using std::make_optional;
#include <cmath>

template<typename Hashable>
class NonLinearProbing {
private:
    enum state {EMPTY, FILLED, REMOVED};
    struct hashItem {
        state status;
        Hashable item;
    };
    unsigned long tableSize;
    vector<hashItem> table;
    function<string(Hashable)> getKey;
    unsigned long numItems;

    // Hash function
    unsigned long hornerHash(string key) {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return hashVal % tableSize;
    }

    // Hash function
    unsigned long hornerHash2(string key) {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 40 + letter;
        }
        return hashVal % tableSize;
    }

    // Find the next prime number
    int nextPrime(int n) {
        if (n % 2 == 0) {
            ++n;
        }
        bool prime = false;
        while (!prime) {
            prime = true;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    prime = false;
                }
            }
            n += 2;
        }
        return (n-2);
    }

    void rehash() {
        vector<hashItem> oldTable = table;
        tableSize = nextPrime(tableSize * 2);
        table.clear();
        table.resize(tableSize);
        numItems = 0;
        for (int i = 0; i < oldTable.size(); ++i) {
            if (oldTable[i].status == FILLED) {
                insert(oldTable[i].item);
            }
        }
    }

public:
    // Constructor
    NonLinearProbing(unsigned long tableSize, function<string(Hashable)> getKey) {
        this->tableSize = nextPrime(tableSize);
        this->getKey = getKey;
        table.resize(this->tableSize);
        numItems = 0;
    }

    // Insert
    void insert(Hashable item) {
        // get a key from the item
        string key = getKey(item);
        // only insert if the key is not already in the table
        if (find(key)) {
            // the key is already in the table. No duplicates allowed.
            return;
        }
        // hash the key into an index
        unsigned long index = hornerHash(key);
        // find an index where we can insert
        int x = 1;
        while (table[index].status == FILLED) {
            // gotta probe
            index = (index+(x*x))%tableSize;
            x++;
        }
        ++numItems;
        table[index].item = item;
        table[index].status = FILLED;
        if (numItems > tableSize / 2) {
            rehash();
        }
    }

    // Insert
    void insert2(Hashable item) {
        // get a key from the item
        string key = getKey(item);
        // only insert if the key is not already in the table
        if (find(key)) {
            // the key is already in the table. No duplicates allowed.
            return;
        }
        // hash the key into an index
        unsigned long index2 = hornerHash2(key);
        // find an index where we can insert
        int x = 1;
        while (table[index2].status == FILLED) {
            // gotta probe
            index2 = (index2+(x*x))%tableSize;
            x++;
        }
        ++numItems;
        table[index2].item = item;
        table[index2].status = FILLED;
        if (numItems > tableSize / 2) {
            rehash();
        }
    }

    int reads = 0;
    int avg = 0;
    int TOTAL = 1000;
    // Find
    optional<Hashable> find(string key) {
        // hash the key into an index
        unsigned long index = hornerHash(key);
        int x = 1;
        while (table[index].status != EMPTY) {
            // Check if the value at the index has a key that matches the parameter
            reads++;
            if (table[index].status == FILLED && getKey(table[index].item) == key) {
                // Found the item
                return table[index].item;
            }
            // gotta probe
            index = (index+(x*x))%tableSize;
            x++;
        }
//        std::cout<<"reads"<<endl;
        std::cout<<reads<<endl;
        avg = reads/TOTAL;
//        std::cout<<"average"<<endl;
//        std::cout<<avg<<endl;
        // Did not find the item
        return nullopt;
    }

    // Remove
    bool remove(string key) {
        // hash the key into an index
        unsigned long index = hornerHash(key);
        int x = 1;
        while (table[index].status != EMPTY) {
            // Check if the value at the index has a key that matches the parameter
            if (table[index].status == FILLED && getKey(table[index].item) == key) {
                // Found the item. Remove it.
                table[index].status = REMOVED;
                table[index].item = Hashable();
                return true;
            }
            // gotta probe
            index = (index+(x*x))%tableSize;
            x++;
        }
        // Did not find the item
        return false;
    }
};

#endif //ROCKCLIMB_LINEARPROBING_H
