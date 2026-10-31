
#include "Bank.h"
#include <iostream>
#include <limits>

Bank::Bank() {
    count = 0;
    capacity = 2;
    accounts = new Account*[capacity]{};
}

void Bank::resize() {
    int newCapacity = capacity * 2;
    Account** newAccounts = new Account*[newCapacity]{};

    for (int i = 0; i < count; i++) {
        newAccounts[i] = accounts[i];
    }

    delete[] accounts;
    accounts = newAccounts;
    capacity = newCapacity;
}

Bank::~Bank() {
    for (int i = 0; i < count; i++) {
        delete accounts[i];
    }

    delete[] accounts;
}

Account* Bank::createAccount(const Customer& customer,const std::string& pin,Money openingBalance) {
    if (openingBalance.getPaise() < 0) {
        std::cout << "Opening balance cannot be negative.\n";
        return nullptr;
    }

    if (count == capacity) {
        resize();
    }

    //Dynamic memory allocation
    Account* newAccount =new Account(customer, pin, openingBalance);

    accounts[count] = newAccount;
    count++;

    return newAccount;
}

Account* Bank::findAccount(int accountNumber) const {
    for (int i = 0; i < count; i++) {
        if (accounts[i]->getAccountNumber() == accountNumber) {
            return accounts[i];
        }
    }

    return nullptr;
}

int Bank::getAccountCount() const {
    return count;
}


bool Bank::transfer(int fromAccountNumber, int toAccountNumber,
                    const Money& amount, int dayOfYear) {

    if (fromAccountNumber == toAccountNumber) {
        std::cout << "Cannot transfer to the same account.\n";
        return false;
    }

    Account* sender = findAccount(fromAccountNumber);
    Account* receiver = findAccount(toAccountNumber);

    if (sender == nullptr || receiver == nullptr) {
        std::cout << "Source or destination account not found.\n";
        return false;
    }

    long long paise = amount.getPaise();

    if (paise <= 0) {
        std::cout << "Transfer amount must be positive.\n";
        return false;
    }

    // Check that the receiver's balance will not overflow.
    long long receiverBalance = receiver->getBalance().getPaise();

    if (receiverBalance >
        std::numeric_limits<long long>::max() - paise) {
        std::cout << "Destination balance would overflow.\n";
        return false;
    }

    // Withdraw from the sender and record the recipient's account number.
    if (!sender->withdraw(amount, dayOfYear, "Transfer Sent",toAccountNumber)) {
        std::cout << "Transfer failed.\n";
        return false;
    }

    // Deposit into the receiver and record the sender's account number.
    if (!receiver->deposit(amount, "Transfer Received",fromAccountNumber)) {
        std::cout << "Unexpected transfer error.\n";
        return false;
    }

    std::cout << "Transfer successful.\n";
    return true;
}
