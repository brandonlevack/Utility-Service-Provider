#include "Bill.h"
#include <iostream>

Bill::Bill(std::vector<Service>& s) : services(s) {                 // initialize services by reference s
    status = "Unpaid";                                              // default status of every bill
    total = 0.0;                                                    // default subtotal of every bill
}

void Bill::calculateTotal(){                                        // calculate bills total using formula highlighted in Service.h
    for (Service s : services){
        total += s.getFlatRate() + (s.getVariableRate() * s.getUnitsUsed());
        s.reset();
    }
}

std::string Bill::getStatus() const {
    return status;
}

double Bill::getTotal() const {
    return total;
}

std::ostream& operator<<(std::ostream&os, const Bill& bill){
    os << "Status: " << bill.getStatus() << " Subtotal: " << bill.getTotal() << std::endl;
    return os;
}