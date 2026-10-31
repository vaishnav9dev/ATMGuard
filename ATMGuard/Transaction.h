
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Money.h"

class Transaction {
private:
    int transactionId;
    std::string type;
    Money amount;
    int relatedAccountNumber;

public:
    // Constructor with default arguments
    Transaction(
        int id = 0,
        const std::string& transactionType = "Unknown",
        const Money& transactionAmount = Money(),
        int relatedAccount = -1
    );

    int getTransactionId() const;
    std::string getType() const;
    Money getAmount() const;
    int getRelatedAccountNumber() const;

    void display() const;
};

#endif
