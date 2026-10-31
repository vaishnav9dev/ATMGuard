
#include <iostream>
#include "ATM.h"

int main() {
    Bank bank;

    Customer rahul(101, "Rahul", "9876543210");
    Customer priya(102, "Priya", "9123456780");

    Account* account1 =
        bank.createAccount(rahul, "1234", Money(500000));

    Account* account2 =
        bank.createAccount(priya, "5678", Money(800000));

    if (account1 == nullptr || account2 == nullptr) {
        std::cout << "Failed to initialize sample accounts.\n";
        return 1;
    }

    ATM atm(bank);
    atm.run();

    return 0;
}
