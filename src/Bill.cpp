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

std::vector<Service> Bill::getServices() {
    return services;
}

std::ostream& operator<<(std::ostream&os, const Bill& bill){
    os << "Status: " << bill.getStatus() << " Subtotal: " << bill.getTotal() << std::endl;
    return os;
}
