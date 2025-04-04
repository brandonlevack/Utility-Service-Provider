#include "Provider.h"
#include <iostream>

Provider::Provider(std::string name) {
    this->name = name;
    phoneNumber = "Undeclared";
}

Provider::Provider(std::string name, std::string phoneNumber, std::vector<Service> services) {
    this->name = name;
    this->phoneNumber = phoneNumber;
    this->services = services;
}

std::string Provider::getName() const {                    // getters
    return name;
}

std::string Provider::getAddress() const {
    return Provider::getStreetAddress() + ", " + Provider::getCity() + ", " + Provider::getProvince() + ", " + Provider::getPostalCode() + ", " + Provider::getCountry();
}

std::string Provider::getStreetAddress() const {
    return streetAddress;
}

std::string Provider::getCity() const {
    return city;
}

std::string Provider::getProvince() const {
    return province;
}

std::string Provider::getPostalCode() const {
    return postalCode;
}

std::string Provider::getCountry() const {
    return country;
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

void Provider::setStreetAddress(std::string ad){
    streetAddress = ad;
}

void Provider::setCity(std::string c){
    city = c;
}

void Provider::setProvince(std::string p){
    province = p;
}

void Provider::setPostalCode(std::string p){
    postalCode = p;
}

void Provider::setCountry(std::string c){
    country = c;
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