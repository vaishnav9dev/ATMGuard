
#include "ATM.h"

#include <iostream>
#include <cctype>
#include <limits>
#include <ctime>

namespace {
    
    bool readAmount(Money& amount) {
        long long rupees;
        char extra;

        std::cout << "Enter amount in whole rupees: ";

        if (!(std::cin >> rupees)) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid amount. Enter a whole number.\n";
            return false;
        }

        if (std::cin.get(extra) && extra != '\n') {
            // Allow trailing spaces, but reject other characters.
            if (!std::isspace(static_cast<unsigned char>(extra))) {
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid amount. Enter a whole number.\n";
                return false;
            }

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (rupees <= 0 ||
            rupees > std::numeric_limits<long long>::max() / 100) {
            std::cout << "Amount must be positive and valid.\n";
            return false;
        }

        amount = Money(rupees * 100);
        return true;
    }


    int currentDayOfYear() {
        std::time_t now = std::time(nullptr);
        std::tm* local = std::localtime(&now);

        if (local == nullptr) {
            return 1;
        }

        return local->tm_yday + 1;
    }

    void clearInputLine() {
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

ATM::ATM(Bank& bankReference)
    : bank(bankReference),
      dispenser(),
      currentAccount(nullptr) {
}



void ATM::adminLogin() {
    std::string enteredPIN;

    std::cout << "Enter administrator PIN: ";
    std::cin >> enteredPIN;

    const std::string adminPIN = "ADMIN123";

    if (enteredPIN == adminPIN) {
        std::cout << "Administrator authentication successful.\n";
        adminMenu();
    } else {
        std::cout << "Invalid administrator PIN. Access denied.\n";
    }
}

void ATM::adminMenu() {
    int choice;

    while (true) {
        std::cout << "\n========== ATM Admin ==========\n";
        std::cout << "1. View ATM cash inventory\n";
        std::cout << "0. Logout from administrator menu\n";
        std::cout << "Choose an option: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            clearInputLine();
            std::cout << "Invalid input. Enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                dispenser.displayInventory();
                break;

            case 0:
                std::cout << "Administrator logged out.\n";
                return;

            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }
}


void ATM::login() {
    if (currentAccount != nullptr) {
        std::cout << "You are already logged in.\n";
        return;
    }

    int accountNumber;
    std::string enteredPin;

    std::cout << "Enter account number: ";

    if (!(std::cin >> accountNumber)) {
        std::cin.clear();
        clearInputLine();
        std::cout << "Invalid account number.\n";
        return;
    }

    Account* account = bank.findAccount(accountNumber);

    if (account == nullptr) {
        std::cout << "Account not found.\n";
        return;
    }

    std::cout << "Enter 4-digit PIN: ";
    std::cin >> enteredPin;

    if (account->verifyPIN(enteredPin)) {
        currentAccount = account;

        std::cout << "Welcome, "
                  << currentAccount->getCustomerName()
                  << "!\n";
    }
}


void ATM::logout() {
    if (currentAccount == nullptr) {
        std::cout << "No active session.\n";
        return;
    }

    std::cout << "Goodbye, "
              << currentAccount->getCustomerName() << "!\n";

    currentAccount = nullptr;
}

void ATM::checkBalance() {
    if (currentAccount == nullptr) {
        std::cout << "Please log in first.\n";
        return;
    }

    std::cout << "Available balance: "
              << currentAccount->getBalance() << '\n';
}

void ATM::depositMoney() {
    if (currentAccount == nullptr) {
        std::cout << "Please log in first.\n";
        return;
    }

    Money amount;

    if (readAmount(amount)) {
        currentAccount->deposit(amount);
    }
}

void ATM::withdrawCash() {
    if (currentAccount == nullptr) {
        std::cout << "Please log in first.\n";
        return;
    }

    Money amount;

    if (!readAmount(amount)) {
        return;
    }

    // Check cash availability before touching the account balance.
    if (!dispenser.canDispense(amount)) {
        std::cout << "ATM cannot dispense that amount.\n";
        return;
    }

    // If the account rejects the withdrawal, no cash is dispensed.
    if (!currentAccount->withdraw(amount, currentDayOfYear())) {
        return;
    }

    // The dispenser was checked immediately before the withdrawal.
    if (!dispenser.dispense(amount)) {
        std::cout << "Unexpected dispenser failure. "
                  << "Contact the bank.\n";
        return;
    }

    std::cout << "Please collect your cash.\n";
}

void ATM::transferMoney() {
    if (currentAccount == nullptr) {
        std::cout << "Please log in first.\n";
        return;
    }

    int destinationNumber;

    std::cout << "Enter destination account number: ";

    if (!(std::cin >> destinationNumber)) {
        std::cin.clear();
        clearInputLine();
        std::cout << "Invalid account number.\n";
        return;
    }

    Money amount;

    if (!readAmount(amount)) {
        return;
    }

    bank.transfer(
        currentAccount->getAccountNumber(),
        destinationNumber,
        amount,
        currentDayOfYear());
}

void ATM::showHistory() {
    if (currentAccount == nullptr) {
        std::cout << "Please log in first.\n";
        return;
    }

    currentAccount->displayTransactionHistory();
}

void ATM::changePIN() {
    if (currentAccount == nullptr) {
        std::cout << "Please log in first.\n";
        return;
    }

    std::string oldPin;
    std::string newPin;

    std::cout << "Enter current PIN: ";
    std::cin >> oldPin;

    std::cout << "Enter new 4-digit PIN: ";
    std::cin >> newPin;

    if (currentAccount->changePIN(oldPin, newPin)) {
        std::cout << "PIN changed successfully.\n";
    } else {
        std::cout << "PIN change failed. Check your current PIN "
                     "and ensure the new PIN is valid and different.\n";
    }
}


void ATM::showMenu() {
    std::cout << "\n========== ATM ==========\n";

    if (currentAccount == nullptr) {
        std::cout << "1. Login\n";
        std::cout << "2. Administrator Login\n";
        std::cout << "0. Exit\n";
    } else {
        std::cout << "Logged in as: "<< currentAccount->getCustomerName() << '\n';
        std::cout << "1. Check balance\n";
        std::cout << "2. Deposit money\n";
        std::cout << "3. Withdraw cash\n";
        std::cout << "4. Transfer money\n";
        std::cout << "5. Transaction history\n";
        std::cout << "6. Change PIN\n";
        std::cout << "7. Logout\n";
        std::cout << "0. Exit\n";
    }

    std::cout << "Choose an option: ";
}

void ATM::run() {
    bool running = true;

    while (running) {
        showMenu();

        int choice;

        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                break;
            }

            std::cin.clear();
            clearInputLine();
            std::cout << "Please enter a valid menu number.\n";
            continue;
        }

        if (currentAccount == nullptr) {
            switch (choice) {

                case 2:
                    adminLogin();
                    break;
                case 1:
                    login();
                    break;

                case 0:
                    running = false;
                    break;

                default:
                    std::cout << "Invalid option. Please log in first.\n";
            }
        } else {
            switch (choice) {
                case 1:
                    checkBalance();
                    break;

                case 2:
                    depositMoney();
                    break;

                case 3:
                    withdrawCash();
                    break;

                case 4:
                    transferMoney();
                    break;

                case 5:
                    showHistory();
                    break;

                case 6:
                    changePIN();
                    break;

                case 7:
                    logout();
                    break;

                case 0:
                    logout();
                    running = false;
                    break;

                default:
                    std::cout << "Invalid option. Try again.\n";
            }
        }
    }

    std::cout << "ATMGuard closed. Thank you!\n";
}
