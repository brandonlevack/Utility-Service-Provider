#ifndef CLASSBILL_H
#define CLASSBILL_H

#include <string>
#include <vector>

#include "Service.h"

class Bill {                                // PASS BY REFERENCE HERE
    private:
        std::string status;                         // paid or unpaid
        double total;                               // subtotal of the bill

        std::vector<Service>& services;              // vector of services containing price and usage information for each service used
    public:
        Bill(std::vector<Service>& s);        // constructor; SERVICES IS PASSED BY REFERENCE

        void calculateTotal();

        std::string getStatus() const;

        double getTotal() const;

        friend std::ostream& operator<<(std::ostream&os, const Bill& bill);

};

#endif