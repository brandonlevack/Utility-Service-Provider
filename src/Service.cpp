#include "Service.h"
#include <iostream>

Service::Service(std::string super, std::string sub, double flat, double var){                     // constructor
    superCategory = super;
    subCategory = sub;
    flatRate = flat;
    variableRate = var;
}

std::string Service::getSuperCategory() const {                                 // getters
    return superCategory;
}

std::string Service::getSubCategory() const {
    return subCategory;
}

double Service::getFlatRate() const {
    return flatRate;
}

double Service::getVariableRate() const {
    return variableRate;
}

void Service::setSuperCategory(std::string super){                              // setters
    superCategory = super;
}

void Service::setSubCategory(std::string sub){
    subCategory = sub;
}

void Service::setFlatRate(double flat){
    flatRate = flat;
}

void Service::setVariableRate(double var){
    variableRate = var;
}

std::ostream& operator<<(std::ostream&os, const Service& service){
    os << "Class: " << service.getSuperCategory() << " Sub-Class: " << service.getSubCategory() << " @ $" << service.getFlatRate() << " monthly plus $" << service.getVariableRate() << "/unit." << std::endl;
    return os;
}