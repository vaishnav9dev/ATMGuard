#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    //Data members
    //Customer details
    int customerId;
    std::string name;
    std::string phoneNumber;

public:
    //Constructor
    Customer(int id, const std::string& customerName,const std::string& phone);

    //memeber functions
    int getCustomerId() const;
    std::string getName() const;

    void displayCustomerDetails() const;
};

#endif
