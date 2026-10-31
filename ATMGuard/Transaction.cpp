
#include "Transaction.h"
#include <iostream>

// Constructor
Transaction::Transaction(
    int id,
    const std::string& transactionType,
    const Money& transactionAmount,
    int relatedAccount
)
    : transactionId(id),
      type(transactionType),
      amount(transactionAmount),
      relatedAccountNumber(relatedAccount) {
}

// Member function definitions

int Transaction::getTransactionId() const {
    return transactionId;
}

std::string Transaction::getType() const {
    return type;
}

Money Transaction::getAmount() const {
    return amount;
}

int Transaction::getRelatedAccountNumber() const {
    return relatedAccountNumber;
}

void Transaction::display() const {
    std::cout << "Transaction ID: " << transactionId
              << " | Type: " << type
              << " | Amount: " << amount;

    if (relatedAccountNumber != -1) {
        if (type == "Transfer Sent") {
            std::cout << " | Recipient Account: "
                      << relatedAccountNumber;
        }
        else if (type == "Transfer Received") {
            std::cout << " | Sender Account: "
                      << relatedAccountNumber;
        }
    }

    std::cout << '\n';
}
