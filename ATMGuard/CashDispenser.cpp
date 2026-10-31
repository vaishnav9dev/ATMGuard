
#include "CashDispenser.h"
#include <iostream>

//Denominations available 
CashDispenser::CashDispenser() {
    denominations[0] = 500;
    denominations[1] = 200;
    denominations[2] = 100;

    notesAvailable[0] = 20;
    notesAvailable[1] = 20;
    notesAvailable[2] = 50;
}

bool CashDispenser::findNoteCombination(const Money& amount, int notesToUse[]) const {

    long long paise = amount.getPaise();

    // All available notes are multiples of Rs. 100.
    if (paise <= 0 || paise % 10000 != 0) {
        return false;
    }

    long long remainingRupees = paise / 100;

    // Search possible combinations using Rs. 500 notes.
    int max500 = static_cast<int>(remainingRupees / 500 < notesAvailable[0] ? remainingRupees / 500 : notesAvailable[0]);

    for (int n500 = max500; n500 >= 0; n500--) {
        long long after500 = remainingRupees - 500LL * n500;

        int max200 = static_cast<int>(after500 / 200 < notesAvailable[1] ? after500 / 200 : notesAvailable[1]);

        for (int n200 = max200; n200 >= 0; n200--) {
            long long after200 = after500 - 200LL * n200;

            if (after200 % 100 != 0) {
                continue;
            }

            long long n100 = after200 / 100;

            if (n100 <= notesAvailable[2]) {
                notesToUse[0] = n500;
                notesToUse[1] = n200;
                notesToUse[2] = static_cast<int>(n100);
                return true;
            }
        }
    }

    return false;
}

bool CashDispenser::canDispense(const Money& amount) const {
    int notesToUse[DENOMINATION_COUNT] = {};
    return findNoteCombination(amount, notesToUse);
}

bool CashDispenser::dispense(const Money& amount) {
    int notesToUse[DENOMINATION_COUNT] = {};

    if (!findNoteCombination(amount, notesToUse)) {
        std::cout << "ATM cannot dispense this amount.\n";
        return false;
    }

    // Update inventory only after finding a complete combination.
    for (int i = 0; i < DENOMINATION_COUNT; i++) {
        notesAvailable[i] -= notesToUse[i];
    }

    std::cout << "Cash dispensed:\n";

    for (int i = 0; i < DENOMINATION_COUNT; i++) {
        if (notesToUse[i] > 0) {
            std::cout << "Rs. " << denominations[i]
                      << " x " << notesToUse[i] << " notes\n";
        }
    }

    return true;
}

void CashDispenser::displayInventory() const {
    std::cout << "\n--- ATM Cash Inventory ---\n";

    for (int i = 0; i < DENOMINATION_COUNT; i++) {
        std::cout << "Rs. " << denominations[i]
                  << " notes: " << notesAvailable[i] << '\n';
    }

    std::cout << "Total cash: " << getTotalCash() << '\n';
}

Money CashDispenser::getTotalCash() const {
    long long totalPaise = 0;

    for (int i = 0; i < DENOMINATION_COUNT; i++) {
        totalPaise += static_cast<long long>(denominations[i])
                      * notesAvailable[i] * 100;
    }

    return Money(totalPaise);
}
