
#ifndef BANK_H
#define BANK_H

#include "Account.h"

class Bank {
private:
    Account** accounts;
    int count;
    int capacity;

    void resize();

public:
    Bank();
    Bank(const Bank&) = delete;
    Bank& operator=(const Bank&) = delete;
    ~Bank();

    Account* createAccount(const Customer& customer,const std::string& pin,Money openingBalance);

    Account* findAccount(int accountNumber) const;

    bool transfer(int fromAccountNumber,int toAccountNumber,const Money& amount,int dayOfYear);

    int getAccountCount() const;
};

#endif
