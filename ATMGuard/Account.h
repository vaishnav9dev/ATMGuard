
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "Customer.h"
#include "Money.h"
#include "TransactionHistory.h"
//Class Composition
class Account {
private:
    int accountNumber;
    //Customer,Money classes in Account class 
    Customer customer;
    Money balance;

    std::string pin;
    bool locked;
    int failedAttempts;

    Money dailyWithdrawn;
    int withdrawalDay;

    //TransactionHistory class in Account Class
    //Class composition
    TransactionHistory history;

    static int nextAccountNumber;
    static int nextTransactionId;

    void recordTransaction(const std::string& type,const Money& amount,int relatedAccountNumber=-1);

public:
    //Constructor
    //customer details and initial pin passes as const to maintain security
    Account(const Customer& customer,const std::string& initialPin,Money openingBalance);

    //All are made constant functions
    int getAccountNumber() const;
    std::string getCustomerName() const;
    Money getBalance() const;
    bool isLocked() const;

    //Verification
    bool verifyPIN(const std::string& enteredPin);
    //Changing pin
    bool changePIN(const std::string& oldPin,const std::string& newPin);

    //Deposit
    
    bool deposit(const Money& amount,const std::string& transactionType = "Deposit",int relatedAccountNumber=-1);

    //Withdraw
    
    bool withdraw(const Money& amount,int dayOfYear,const std::string& transactionType = "Withdrawal",int relatedAccountNumber=-1);

    //Transaction History
    void displayTransactionHistory() const;
};

#endif
