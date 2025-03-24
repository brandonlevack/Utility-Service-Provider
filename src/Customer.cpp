#include "Customer.h"
#include <iostream>

Customer::Customer(std::string name, std::string address) {     // constructor
    this->name = name;
    this->address = address;
}

std::string Customer::getName() const {                         // getters
    return name;
}

std::string Customer::getAddress() const {
    return address;
}

std::vector<Service> Customer::getServices() const {
    return services;
}

std::deque<Bill> Customer::getBills() const {
    return bills;
}

void Customer::setName(std::string name){                       // setters
    this->name = name;
}

void Customer::setAddress(std::string address){
    this->address = address;
}

void Customer::addService(Service service){                     // add service to the vector of services
    services.push_back(service);
}

void Customer::addBill(Bill bill){                              // add current bill to the front of the deque record
    bills.push_front(bill);
}

void Customer::billCustomer(){
    Bill bill(services);                                        // create a new bill with a reference to our list of services
    bill.calculateTotal();                                      // calculate the total of the bill, reset the unitsUsed for each service
    Customer::addBill(bill);                                    // add the bill as our most recent bill for the customer
}

std::ostream& operator<<(std::ostream&os, const Customer& customer){
    os << "Name: " << customer.getName() << " Address: " <<customer.getAddress() << std::endl;
    os << "Services: " << std::endl;
    for (Service s : customer.getServices()){
        os << '\t' << s;
    }
    os << std::endl << "Bills: " << std::endl;
    for (Bill b : customer.getBills()){
        os << '\t' << b;
    }
    return os;
}