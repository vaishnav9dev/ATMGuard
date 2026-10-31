#ifndef MONEY_H
#define MONEY_H

#include <iostream>

class Money {
private:
    long long paise;

    //Memeber function
public:
    //Constructor (user-defined & parametrized)
    Money(long long p = 0);

    //Memeber function accessing private data member
    long long getPaise() const;

    //Operator Overloading += and -=
    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);

    //Equality checker overloading
    bool operator==(const Money& other) const;

    //ostream overloading for cout and cascading
    friend std::ostream& operator<<(std::ostream& out,const Money& money);
};

#endif
