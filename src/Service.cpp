#include "Service.h"
#include <iostream>

Service::Service(std::string super, std::string sub, double flat, double var){                     // constructor
    superCategory = super;
    subCategory = sub;
    flatRate = flat;
    variableRate = var;
    unitsUsed = 0;
}

std::string Service::getSuperCategory() const {                                 // getters
    return superCategory;
}

std::string Service::getSubCategory() const {
    return subCategory;
}

std::string Service::getProviderName() const {
    return providerName;
}

double Service::getFlatRate() const {
    return flatRate;
}

double Service::getVariableRate() const {
    return variableRate;
}

double Service::getUnitsUsed() const {
    return unitsUsed;
}

int Service::getServiceId() const {
    return serviceId;
}

void Service::setSuperCategory(std::string super){                              // setters
    superCategory = super;
}

void Service::setSubCategory(std::string sub){
    subCategory = sub;
}

void Service::setProviderName(std::string name){
    providerName = name;
}

void Service::setFlatRate(double flat){
    flatRate = flat;
}

void Service::setVariableRate(double var){
    variableRate = var;
}

void Service::setUnitsUsed(double val){
    unitsUsed = val;
}

void Service::setServiceId(int id){
    serviceId = id;
}

void Service::reset(){
    Service temp = *this;
    temp.history.clear();

    history.push_front(temp); // Store the cleaned copy
    unitsUsed = 0;
}

std::ostream& operator<<(std::ostream&os, const Service& service){
    os << "Class: " << service.getSuperCategory() << " Sub-Class: " << service.getSubCategory() << " @ $" << service.getFlatRate() << " monthly plus $" << service.getVariableRate() << "/unit." << " ID = " << service.getServiceId() << std::endl;
    return os;
}
