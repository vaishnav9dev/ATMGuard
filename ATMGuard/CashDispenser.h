
#ifndef CASH_DISPENSER_H
#define CASH_DISPENSER_H

#include "Money.h"

class CashDispenser {
private:
    static const int DENOMINATION_COUNT = 3;

    int denominations[DENOMINATION_COUNT];
    int notesAvailable[DENOMINATION_COUNT];

    bool findNoteCombination(const Money& amount,int notesToUse[]) const;

public:
    CashDispenser();

    bool canDispense(const Money& amount) const;
    bool dispense(const Money& amount);

    void displayInventory() const;
    //Class composition
    Money getTotalCash() const;
};

#endif
