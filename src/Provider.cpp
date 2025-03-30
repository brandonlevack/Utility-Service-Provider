#include "Provider.h"
#include <iostream>

Provider::Provider(std::string name) {
    this->name = name;
    address = "Undeclared";
    phoneNumber = "Undeclared";
}

Provider::Provider(std::string name, std::string address, std::string phoneNumber, std::vector<Service> services) {
    this->name = name;
    this->address = address;
    this->phoneNumber = phoneNumber;
    this->services = services;
}

std::string Provider::getName() const {                    // getters
    return name;
}

std::string Provider::getAddress() const {
    return address;
}

std::string Provider::getPhoneNumber() const {
    return phoneNumber;
}

std::vector<Service> Provider::getServices() const {
    return services;
}

void Provider::setName(std::string newName){                // setters
    name = newName;
}

void Provider::setAddress(std::string newAddress){
    address = newAddress;
}

void Provider::setPhoneNumber(std::string newNumber){
    phoneNumber = newNumber;
}

void Provider::addService(Service s){
    services.push_back(s);
}

std::ostream& operator<<(std::ostream&os, const Provider& provider){
    os << "Provider(Name: " << provider.getName() << ", Address: " << provider.getAddress() << ", Phone Number: " << provider.getPhoneNumber() <<std::endl;
    os << "Services: " << std::endl;
    for (Service s : provider.getServices()){
        os << '\t' << s;
    }
    return os;
}