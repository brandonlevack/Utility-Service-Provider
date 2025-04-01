#include "Bill.h"
#include <iostream>

Bill::Bill(std::vector<Service>& s) : services(s) {                 // initialize services by reference s
    status = "Unpaid";                                              // default status of every bill
    total = 0.0;                                                    // default subtotal of every bill
}

void Bill::calculateTotal() {
    total = 0.0;
    for (const Service& s : services) {  // const reference
        total += s.getFlatRate() + (s.getVariableRate() * s.getUnitsUsed());
    }
}

std::string Bill::getStatus() const {
    return status;
}

double Bill::getTotal() const {
    return total;
}

int Bill::getBillId() const {
    return billId;
}

int Bill::getServiceId() const {
    return serviceId;
}

std::string Bill::getIssueDate() const {
    return issueDate;
}

std::string Bill::getDueDate() const {
    return dueDate;
}

void Bill::setBillId(int id){
    billId = id;
}

void Bill::setServiceId(int id){
    serviceId = id;
}

void Bill::setStatus(std::string s){
    status = s;
}

void Bill::setIssueDate(std::string date){
    issueDate = date;
}

void Bill::setDueDate(std::string date){
    dueDate = date;
}

std::vector<Service> Bill::getServices() {
    return services;
}

std::ostream& operator<<(std::ostream&os, const Bill& bill){
    os << "Status: " << bill.getStatus() << " Subtotal: " << bill.getTotal() << std::endl;
    return os;
}
