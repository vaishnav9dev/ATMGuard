
#include "Account.h"
#include <iostream>
#include <cctype>
#include <limits>

int Account::nextAccountNumber = 1001;
int Account::nextTransactionId = 1;

namespace {
    bool isValidPIN(const std::string& value) {
        if (value.length() != 4) {
            return false;
        }

        for (char ch : value) {
            if (!std::isdigit(static_cast<unsigned char>(ch))) {
                return false;
            }
        }

        return true;
    }
}

Account::Account(const Customer& customerDetails,
                 const std::string& initialPin,
                 Money openingBalance)
    : accountNumber(nextAccountNumber++),
      customer(customerDetails),
      balance(openingBalance.getPaise() >= 0
                  ? openingBalance : Money()),
      pin(isValidPIN(initialPin) ? initialPin : "0000"),
      locked(false),
      failedAttempts(0),
      dailyWithdrawn(0),
      withdrawalDay(-1),
      history() {
}

int Account::getAccountNumber() const {
    return accountNumber;
}

std::string Account::getCustomerName() const {
    return customer.getName();
}

Money Account::getBalance() const {
    return balance;
}

bool Account::isLocked() const {
    return locked;
}

//verification
bool Account::verifyPIN(const std::string& enteredPin) {
    if (locked) {
        std::cout << "Account is locked.\n";
        return false;
    }

    if (enteredPin == pin) {
        failedAttempts = 0;
        return true;
    }

    failedAttempts++;

    std::cout << "Incorrect PIN. Attempts remaining: "
              << 3 - failedAttempts << '\n';

    if (failedAttempts >= 3) {
        locked = true;
        std::cout << "Account locked after 3 incorrect attempts.\n";
    }

    return false;
}

bool Account::changePIN(const std::string& oldPin,const std::string& newPin) {

    if (locked || oldPin != pin || !isValidPIN(newPin)) {
        return false;
    }

    if (oldPin == newPin) {
        return false;
    }

    pin = newPin;
    return true;
}

void Account::recordTransaction(const std::string& type,const Money& amount,int relatedAccountNumber) {

    history.addTransaction(Transaction(nextTransactionId++, type, amount,relatedAccountNumber));
}


bool Account::deposit(const Money& amount,const std::string& transactionType,int relatedAccountNumber) {
    long long paise = amount.getPaise();

    if (paise <= 0) {
        std::cout << "Amount must be positive.\n";
        return false;
    }

    if (balance.getPaise() >
        std::numeric_limits<long long>::max() - paise) {
        std::cout << "Amount is too large.\n";
        return false;
    }

    balance += amount;
    recordTransaction(transactionType, amount,relatedAccountNumber);

    std::cout << transactionType << " successful. "
              << "New balance: " << balance << '\n';

    return true;
}

bool Account::withdraw(const Money& amount,int dayOfYear,const std::string& transactionType,int relatedAccountNumber) {

    const long long DAILY_LIMIT_PAISE = 2000000;

    long long paise = amount.getPaise();

    if (paise <= 0) {
        std::cout << "Amount must be positive.\n";
        return false;
    }

    if (dayOfYear < 1 || dayOfYear > 366) {
        std::cout << "Invalid day of year.\n";
        return false;
    }

    if (withdrawalDay != dayOfYear) {
        dailyWithdrawn = Money(0);
        withdrawalDay = dayOfYear;
    }

    if (paise > balance.getPaise()) {
        std::cout << "Insufficient balance.\n";
        return false;
    }

    long long alreadyWithdrawn = dailyWithdrawn.getPaise();

    if (alreadyWithdrawn > DAILY_LIMIT_PAISE ||
        paise > DAILY_LIMIT_PAISE - alreadyWithdrawn) {
        std::cout << "Daily withdrawal limit exceeded.\n";
        return false;
    }

    balance -= amount;
    dailyWithdrawn += amount;
    recordTransaction(transactionType, amount,relatedAccountNumber);

    std::cout << transactionType << " successful. "
              << "Remaining balance: " << balance << '\n';

    return true;
}


void Account::displayTransactionHistory() const {
    history.displayHistory();
}
