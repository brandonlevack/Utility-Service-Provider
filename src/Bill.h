#ifndef CLASSBILL_H
#define CLASSBILL_H

#include <string>
#include <vector>

#include "Service.h"

class Bill {                                // PASS BY REFERENCE HERE
    private:
        std::string status;                         // paid or unpaid
        double total;                               // subtotal of the bill

        int billId;
        int serviceId;

        std::string issueDate;
        std::string dueDate;

        std::vector<Service> services;              // vector of services containing price and usage information for each service used
    public:
        Bill(std::vector<Service>& s);        // constructor; SERVICES IS PASSED BY REFERENCE

        void calculateTotal();

        std::string getStatus() const;

        double getTotal() const;

        int getServiceId() const;

        int getBillId() const;

        void setBillId(int id);

        void setServiceId(int id);

        void setStatus(std::string s);

        std::string getIssueDate() const;

        std::string getDueDate() const;

        void setIssueDate(std::string date);

        void setDueDate(std::string date);

        std::vector<Service> getServices();

        friend std::ostream& operator<<(std::ostream&os, const Bill& bill);

};

#endif
