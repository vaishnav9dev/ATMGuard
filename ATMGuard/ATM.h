//Final main one ATM
#ifndef ATM_H
#define ATM_H

#include "Bank.h"
#include "CashDispenser.h"

//Class composition
class ATM {
private:
    Bank& bank;
    CashDispenser dispenser;
    Account* currentAccount;

    void adminLogin();
    void adminMenu();

    void login();
    void logout();
    void showMenu();

    void checkBalance();
    void depositMoney();
    void withdrawCash();
    void transferMoney();
    void showHistory();
    void changePIN();

public:
    //prevents accidental type conversions
    explicit ATM(Bank& bankReference);
    void run();
};

#endif
