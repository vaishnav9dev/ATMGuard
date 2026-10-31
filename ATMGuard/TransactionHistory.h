
#ifndef TRANSACTION_HISTORY_H
#define TRANSACTION_HISTORY_H

//Benifit of using class Transaction via Transaction.h header file 
//Without redeclaring helping reusability
#include "Transaction.h"

class TransactionHistory {
private:
    Transaction* records;
    int count;
    int capacity;

    void resize();

public:
    //Constructor
    TransactionHistory();
    //Copy Constructor
    TransactionHistory(const TransactionHistory& other);

    //Operator Overloading  =
    TransactionHistory& operator=(const TransactionHistory& other);

    //Destructor
    ~TransactionHistory();

    void addTransaction(const Transaction& transaction);
    void displayHistory() const;
    int getCount() const;
};

#endif
