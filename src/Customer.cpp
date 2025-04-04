#include "Customer.h"
#include <iostream>

Customer::Customer() {}     // constructor

std::string Customer::getName() const {                         // getters
    return Customer::getFirstName() + " " + Customer::getLastName();
}

std::string Customer::getAccountNumber() const {
    return accNumber;
}

std::string Customer::getAddress() const {
    return Customer::getStreetAddress() + ", " + Customer::getCity() + ", " + Customer::getProvince() + ", " + Customer::getPostalCode() + ", " + Customer::getCountry();
}

std::string Customer::getFirstName() const {
    return firstName;
}

std::string Customer::getLastName() const {
    return lastName;
}

std::string Customer::getStreetAddress() const {
    return streetAddress;
}

std::string Customer::getCity() const {
    return city;
}

std::string Customer::getProvince() const {
    return province;
}

std::string Customer::getPostalCode() const {
    return postalCode;
}

std::string Customer::getCountry() const {
    return country;
}

std::vector<Service> Customer::getServices() const {
    return services;
}

std::deque<Bill> Customer::getBills() const {
    return bills;
}

void Customer::setFirstName(std::string name){                       // setters
    firstName = name;
}

void Customer::setLastName(std::string name){
    lastName = name;
}

void Customer::setAccountNumber(std::string acnum){
    accNumber = acnum;
}

void Customer::setStreetAddress(std::string ad){
    streetAddress = ad;
}

void Customer::setCity(std::string c){
    city = c;
}

void Customer::setProvince(std::string p){
    province = p;
}

void Customer::setPostalCode(std::string p){
    postalCode = p;
}

void Customer::setCountry(std::string c){
    country = c;
}

void Customer::addService(Service service){                     // add service to the vector of services
    services.push_back(service);
}

void Customer::addBill(Bill bill){                              // add current bill to the front of the deque record
    bills.push_front(bill);
}

void Customer::billCustomer(){
    Bill bill(services);
    bill.calculateTotal();
    addBill(bill);
    for (Service& s : services) {
        s.reset();
    }
}

Service& Customer::changeService(int index){
    return services[index];                                     // no out of index check, be cautions here
}

Bill& Customer::changeBill(int index){
    return bills[index];
}

int Customer::numServices(){
    int i=0;
    for (auto s : services){
        i++;
    }
    return i;
}

std::vector<Service>& Customer::getServicesByReference(){
    return services;
}

std::ostream& operator<<(std::ostream&os, const Customer& customer){
    os << "Customer:" << '\t';
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
