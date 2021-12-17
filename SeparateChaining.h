//
// Created by aidan on 11/19/2021.
//

#ifndef ROCKCLIMB_SEPARATECHAINING_H
#define ROCKCLIMB_SEPARATECHAINING_H


#include <functional>
#include <string>
#include <vector>
using std::function, std::string, std::vector;

#include <optional>
using std::optional;
using std::nullopt;
using std::make_optional;


template<typename Hashable>
class SeparateChaining {
private:
    unsigned long tableSize;
    vector<vector<Hashable>> table;
    function<string(Hashable)> getKey;

    // Hash function
    unsigned long hornerHash(string key) {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return hashVal % tableSize;
    }

    unsigned long hornerHash2(string key2) {
        unsigned long hashVal = 0;
        for (char letter : key2) {
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

public:
    // Constructor
    SeparateChaining(unsigned long tableSize, function<string(Hashable)> getKey) {
        this->tableSize = nextPrime(tableSize);
        this->getKey = getKey;
        table.resize(this->tableSize);

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

        // store the item at the index
        table[index].push_back(item);

    }

    void insert2(Hashable item) {
        // get a key from the item
        string key = getKey(item);
        // only insert if the key is not already in the table
        if (find(key)) {
            // the key is already in the table. No duplicates allowed.
            return;
        }
        // hash the key into an index
        unsigned long index = hornerHash2(key);

        // store the item at the index
        table[index].push_back(item);

    }

    int reads = 0;
    int avg = 0;
    int TOTAL = 1000;
    // Find
    optional<Hashable> find(string key) {
        // hash the key into an index
        unsigned long index = hornerHash(key);
        // Check if the vector at the index has the item we're looking for
        for (int i = 0; i < table[index].size(); ++i) {
            reads++;
            //reads
            if (getKey(table[index][i]) == key) {
                // Found the
                return table[index][i];
            }
        }
//        std::cout << "reads" << endl;
        std::cout << reads << endl;
        avg = reads/TOTAL;

//        std::cout << "average" << endl;
//        std::cout << avg << endl;
        return nullopt;
    }


    // Remove
    bool remove(string key) {
        // hash the key into an index
        unsigned long index = hornerHash(key);
        // Check if the vector at the index has the item we're looking for
        for (int i = 0; i < table[index].size(); ++i) {
            if (getKey(table[index][i]) == key) {
                // Found the item. Remove it.
                table[index].erase(table[index].begin() + i);
                return table[index][i];
            }
        }
        return false;
    }
};

#endif //ROCKCLIMB_SEPARATECHAINING_H
