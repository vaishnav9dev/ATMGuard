//include Money class via header file
#include "Money.h"

//constructor
Money::Money(long long p) {
    paise = p;
}

//Private data member via member function of class
long long Money::getPaise() const {
    return paise;
}

//+= operator overloading
Money& Money::operator+=(const Money& other) {
    paise += other.paise;
    //this pointer
    return *this;
}

//-= operator overloading
Money& Money::operator-=(const Money& other) {
    paise -= other.paise;
    //this pointer
    return *this;
}

//cout overloading
bool Money::operator==(const Money& other) const {
    return paise == other.paise;
}

std::ostream& operator<<(std::ostream& out,const Money& money) {

    out << "Rs. " << money.paise / 100 << ".";

    long long remainder = money.paise % 100;

    if (remainder < 10) {
        out << "0";
    }

    out << remainder;
    return out;
}
