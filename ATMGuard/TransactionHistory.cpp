
#include "TransactionHistory.h"
#include <iostream>

//Constructor
TransactionHistory::TransactionHistory() {
    capacity = 2;
    count = 0;
    records = new Transaction[capacity];
}

//Starting a new record
void TransactionHistory::resize() {
    int newCapacity = capacity * 2;

    Transaction* newRecords = new Transaction[newCapacity];

    for (int i = 0; i < count; i++) {
        newRecords[i] = records[i];
    }

    delete[] records;

    records = newRecords;
    capacity = newCapacity;
}

//Adding a new transaction to Transaction history
void TransactionHistory::addTransaction(
    const Transaction& transaction) {

    if (count == capacity) {
        resize();
    }

    records[count] = transaction;
    count++;
}

//Displaying Transaction History

void TransactionHistory::displayHistory() const {
    if (count == 0) {
        std::cout << "No transactions found.\n";
        return;
    }

    std::cout << "\n--- Transaction History ---\n";

    for (int i = 0; i < count; i++) {
        std::cout << "S.No.: " << i + 1 << " | ";
        records[i].display();
    }
}


int TransactionHistory::getCount() const {
    return count;
}

//Copy Constructor to copy from one history to other
TransactionHistory::TransactionHistory(const TransactionHistory& other) {

    count = other.count;
    capacity = other.capacity;
    records = new Transaction[capacity];

    for (int i = 0; i < count; i++) {
        records[i] = other.records[i];
    }
}

//Operator = overloading
TransactionHistory& TransactionHistory::operator=(const TransactionHistory& other) {
    
    //if same return 
    if (this == &other) {
        return *this;
    }

    Transaction* newRecords = new Transaction[other.capacity];

    for (int i = 0; i < other.count; i++) {
        newRecords[i] = other.records[i];
    }

    delete[] records;

    records = newRecords;
    count = other.count;
    capacity = other.capacity;

    return *this;
}

//Destructor
TransactionHistory::~TransactionHistory() {
    delete[] records;
}
