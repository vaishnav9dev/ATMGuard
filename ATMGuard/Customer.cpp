//include Customer class via .h header file
#include "Customer.h"
#include <iostream>

//Constructor
Customer::Customer(int id,const std::string& customerName,const std::string& phone) {

    customerId = id;
    name = customerName;
    phoneNumber = phone;
}

//Memeber function for accesing private data customer Id
int Customer::getCustomerId() const {
    return customerId;
}

//Memeber function for accesing private data customer Name
std::string Customer::getName() const {
    return name;
}

//Displaying private datamembers like customer details via memeber functions of class
void Customer::displayCustomerDetails() const {
    std::cout << "Customer ID: " << customerId << '\n';
    std::cout << "Customer Name: " << name << '\n';
}
